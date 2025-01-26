/*
 * Copyright ©2024 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Winter Quarter 2024 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <string>
#include <sstream>

#include "./FileReader.h"
#include "./HttpConnection.h"
#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpServer.h"
#include "./libhw3/QueryProcessor.h"

using std::cerr;
using std::cout;
using std::endl;
using std::list;
using std::map;
using std::string;
using std::stringstream;
using std::unique_ptr;

namespace hw4 {
///////////////////////////////////////////////////////////////////////////////
// Constants, internal helper functions
///////////////////////////////////////////////////////////////////////////////
static const char* kThreegleStr =
  "<html><head><title>333gle</title></head>\n"
  "<body>\n"
  "<center style=\"font-size:500%;\">\n"
  "<span style=\"position:relative;bottom:-0.33em;color:orange;\">3</span>"
    "<span style=\"color:red;\">3</span>"
    "<span style=\"color:gold;\">3</span>"
    "<span style=\"color:blue;\">g</span>"
    "<span style=\"color:green;\">l</span>"
    "<span style=\"color:red;\">e</span>\n"
  "</center>\n"
  "<p>\n"
  "<div style=\"height:20px;\"></div>\n"
  "<center>\n"
  "<form action=\"/query\" method=\"get\">\n"
  "<input type=\"text\" size=30 name=\"terms\" />\n"
  "<input type=\"submit\" value=\"Search\" />\n"
  "</form>\n"
  "</center><p>\n";

// static
const int HttpServer::kNumThreads = 100;

// This is the function that threads are dispatched into
// in order to process new client connections.
static void HttpServer_ThrFn(ThreadPool::Task* t);

// Given a request, produce a response.
static HttpResponse ProcessRequest(const HttpRequest& req,
                            const string& base_dir,
                            const list<string>& indices);

// Process a file request.
static HttpResponse ProcessFileRequest(const string& uri,
                                const string& base_dir);

// Process a query request.
static HttpResponse ProcessQueryRequest(const string& uri,
                                 const list<string>& indices);


///////////////////////////////////////////////////////////////////////////////
// HttpServer
///////////////////////////////////////////////////////////////////////////////
bool HttpServer::Run(void) {
  // Create the server listening socket.
  int listen_fd;
  cout << "  creating and binding the listening socket..." << endl;
  if (!socket_.BindAndListen(AF_INET6, &listen_fd)) {
    cerr << endl << "Couldn't bind to the listening socket." << endl;
    return false;
  }

  // Spin, accepting connections and dispatching them.  Use a
  // threadpool to dispatch connections into their own thread.
  cout << "  accepting connections..." << endl << endl;
  ThreadPool tp(kNumThreads);
  while (1) {
    HttpServerTask* hst = new HttpServerTask(HttpServer_ThrFn);
    hst->base_dir = static_file_dir_path_;
    hst->indices = &indices_;
    if (!socket_.Accept(&hst->client_fd,
                    &hst->c_addr,
                    &hst->c_port,
                    &hst->c_dns,
                    &hst->s_addr,
                    &hst->s_dns)) {
      // The accept failed for some reason, so quit out of the server.
      // (Will happen when kill command is used to shut down the server.)
      break;
    }
    // The accept succeeded; dispatch it.
    tp.Dispatch(hst);
  }
  return true;
}

static void HttpServer_ThrFn(ThreadPool::Task* t) {
  // Cast back our HttpServerTask structure with all of our new
  // client's information in it.
  unique_ptr<HttpServerTask> hst(static_cast<HttpServerTask*>(t));
  cout << "  client " << hst->c_dns << ":" << hst->c_port << " "
       << "(IP address " << hst->c_addr << ")" << " connected." << endl;

  // Read in the next request, process it, and write the response.

  // Use the HttpConnection class to read and process the next
  // request from our current client, then write out our response.  If
  // the client sends a "Connection: close\r\n" header, then shut down
  // the connection -- we're done.
  //
  // Hint: the client can make multiple requests on our single connection,
  // so we should keep the connection open between requests rather than
  // creating/destroying the same connection repeatedly.

  // STEP 1:
	bool done = false;

	// Make the connection
  HttpConnection host_connect(hst->client_fd);
  HttpRequest http_req;

  while (!done) {
    // Get next request
    if (!host_connect.GetNextRequest(&http_req)) {
      close(hst->client_fd);
      done = true;  
      break;
    }   

    // Close the connection if user requested
    if (http_req.GetHeaderValue("connection") == "close") {
      close(hst->client_fd);
      done = true;
      break;
    }   

    // Process the request
    HttpResponse http_res = ProcessRequest(http_req, hst->base_dir, 
                                          *hst->indices);

    // Close the connection if failed to write 
    if (!host_connect.WriteResponse(http_res)) {
      close(hst->client_fd);
      done = true;
      break;
    }   
  }
}

static HttpResponse ProcessRequest(const HttpRequest& req,
                            const string& base_dir,
                            const list<string>& indices) {
  // Is the user asking for a static file?
  if (req.uri().substr(0, 8) == "/static/") {
    return ProcessFileRequest(req.uri(), base_dir);
  }

  // The user must be asking for a query.
  return ProcessQueryRequest(req.uri(), indices);
}

static HttpResponse ProcessFileRequest(const string& uri,
                                const string& base_dir) {
  // The response we'll build up.
  HttpResponse ret;

  // Steps to follow:
  // 1. Use the URLParser class to figure out what file name
  //    the user is asking for. Note that we identify a request
  //    as a file request if the URI starts with '/static/'
  //
  // 2. Use the FileReader class to read the file into memory
  //
  // 3. Copy the file content into the ret.body
  //
  // 4. Depending on the file name suffix, set the response
  //    Content-type header as appropriate, e.g.,:
  //      --> for ".html" or ".htm", set to "text/html"
  //      --> for ".jpeg" or ".jpg", set to "image/jpeg"
  //      --> for ".png", set to "image/png"
  //      etc.
  //    You should support the file types mentioned above,
  //    as well as ".txt", ".js", ".css", ".xml", ".gif",
  //    and any other extensions to get bikeapalooza
  //    to match the solution server.
  //
  // be sure to set the response code, protocol, and message
  // in the HttpResponse as well.
  string file_name = "";

  // STEP 2:
	// Get file name by paring url
  URLParser url_parser;
  url_parser.Parse(uri);
	file_name = url_parser.path();

  // Remove the static part 
  file_name = file_name.replace(0, 8, "");
  FileReader file_reader(base_dir, file_name);

  string s;
  // Read file into memort
  if (file_reader.ReadFile(&s)) {
    // Append to response body
    ret.AppendToBody(s);
    string suffix;
    // Find the suffix in the file
    suffix = file_name.substr(file_name.rfind("."));
    // Set content type header according to suffix
    if (suffix == ".html" || suffix == ".htm") {
      ret.set_content_type("text/html");
    } else if (suffix == ".xml") {
        ret.set_content_type("text/xml");
    } else if (suffix == ".txt") {
        ret.set_content_type("text/plain");
    } else if (suffix == ".csv") {
        ret.set_content_type("text/csv");
		} else if (suffix == ".css") {
      ret.set_content_type("text/css");
    } else if (suffix == ".jpeg" || suffix == ".jpg") {
        ret.set_content_type("image/jpeg");
    } else if (suffix == ".png") {
        ret.set_content_type("image/png");
    } else if (suffix == ".gif") {
        ret.set_content_type("image/gif");
    } else if (suffix == ".mp4") {
        ret.set_content_type("video/mp4");
    } else if (suffix == ".tiff") {
      ret.set_content_type("image/tiff");
		}
		
		// Set up other response headers 
    ret.set_response_code(200);
    ret.set_protocol("HTTP/1.1");
    ret.set_message("OK");

    return ret;
  }

  // If you couldn't find the file, return an HTTP 404 error.
  ret.set_protocol("HTTP/1.1");
  ret.set_response_code(404);
  ret.set_message("Not Found");
  ret.AppendToBody("<html><body>Couldn't find file \""
                   + EscapeHtml(file_name)
                   + "\"</body></html>\n");
  return ret;
}

static HttpResponse ProcessQueryRequest(const string& uri,
                                 const list<string>& indices) {
  // The response we're building up.
  HttpResponse ret;

  // Your job here is to figure out how to present the user with
  // the same query interface as our solution_binaries/http333d server.
  // A couple of notes:
  //
  // 1. The 333gle logo and search box/button should be present on the site.
  //
  // 2. If the user had previously typed in a search query, you also need
  //    to display the search results.
  //
  // 3. you'll want to use the URLParser to parse the uri and extract
  //    search terms from a typed-in search query.  convert them
  //    to lower case.
  //
  // 4. Initialize and use hw3::QueryProcessor to process queries with the
  //    search indices.
  //
  // 5. With your results, try figuring out how to hyperlink results to file
  //    contents, like in solution_binaries/http333d. (Hint: Look into HTML
  //    tags!)

  // STEP 3:
	// Append to body for 333gle logo and search box and button
  ret.AppendToBody(kThreegleStr);

	string search = "query?terms=";
  URLParser url_parser;
  url_parser.Parse(uri);
  string str = url_parser.args()["terms"];
  boost::trim(str);
  boost::to_lower(str);
  std::vector<string> words;

  if (uri.find(search) != string::npos) {
    // Split query result 
    boost::split(words, str, boost::is_any_of(" "),
                boost::token_compress_on);
		
    // Create a query processor
    hw3::QueryProcessor query(indices, false);

    // Process query results
    std::vector<hw3::QueryProcessor::QueryResult> res =
    query.ProcessQuery(words);

    // Obtain escape characters 
    string escape = EscapeHtml(str);

    // If no results found 
    if (res.size() == 0) {
      ret.AppendToBody("<p><br>\r\n");
      ret.AppendToBody("No results found for <b>");
      ret.AppendToBody(escape);
      ret.AppendToBody("</b>\r\n");
      ret.AppendToBody("<p>\r\n\r\n");
    } else {  // Found some results 
      ret.AppendToBody("<p><br>\r\n");
      ret.AppendToBody(std::to_string(res.size()));
      ret.AppendToBody(" result");

      if (res.size() > 1) {
        ret.AppendToBody("s");
      }

			ret.AppendToBody(" ");
      ret.AppendToBody("found for <b>");
      ret.AppendToBody(escape);
      ret.AppendToBody("</b>\r\n");
      ret.AppendToBody("<p>\r\n\r\n");

      // Show the result
      ret.AppendToBody("</ul>\r\n");
      size_t i = 0;
      for (i = 0; i < res.size(); i++) {
        ret.AppendToBody(" <li> <a href=\"");
        if (res[i].document_name.substr(0, 7) != "http://") {
          ret.AppendToBody("/static/");
        }
          ret.AppendToBody(res[i].document_name);
          ret.AppendToBody("\">");
          string doc = res[i].document_name;
          ret.AppendToBody(EscapeHtml(doc));
          ret.AppendToBody("</a> [");
          int rank = res[i].rank;
          ret.AppendToBody(std::to_string(rank));
          ret.AppendToBody("]<br>\r\n");
      }

      ret.AppendToBody("</ul>\r\n");
    }
	}

	ret.AppendToBody("</body>\r\n");
  ret.AppendToBody("</html>\r\n");

	// Set protocol, response code, message
  ret.set_protocol("HTTP/1.1");
  ret.set_response_code(200);
  ret.set_message("OK");

  return ret;
}

}  // namespace hw4
