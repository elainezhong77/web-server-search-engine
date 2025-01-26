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

#include <stdio.h>       // for snprintf()
#include <unistd.h>      // for close(), fcntl()
#include <sys/types.h>   // for socket(), getaddrinfo(), etc.
#include <sys/socket.h>  // for socket(), getaddrinfo(), etc.
#include <arpa/inet.h>   // for inet_ntop()
#include <netdb.h>       // for getaddrinfo()
#include <errno.h>       // for errno, used by strerror()
#include <string.h>      // for memset, strerror()
#include <iostream>      // for std::cerr, etc.

#include "./ServerSocket.h"

extern "C" {
  #include "libhw1/CSE333.h"
}

namespace hw4 {

ServerSocket::ServerSocket(uint16_t port) {
  port_ = port;
  listen_sock_fd_ = -1;
}

ServerSocket::~ServerSocket() {
  // Close the listening socket if it's not zero.  The rest of this
  // class will make sure to zero out the socket if it is closed
  // elsewhere.
  if (listen_sock_fd_ != -1)
    close(listen_sock_fd_);
  listen_sock_fd_ = -1;
}

bool ServerSocket::BindAndListen(int ai_family, int* const listen_fd) {
  // Use "getaddrinfo," "socket," "bind," and "listen" to
  // create a listening socket on port port_.  Return the
  // listening socket through the output parameter "listen_fd"
  // and set the ServerSocket data member "listen_sock_fd_"

  // STEP 1:
	
  // Check if ai_family passed in is valid
  if (ai_family != AF_INET && ai_family != AF_INET6 && ai_family != AF_UNSPEC)
    return false;

	struct addrinfo addr;

  memset(&addr, 0, sizeof(struct addrinfo));

  // Set the values for addr 
  addr.ai_socktype = SOCK_STREAM;  
  addr.ai_family = ai_family;
  addr.ai_protocol = IPPROTO_TCP;  
  addr.ai_flags = AI_PASSIVE;  
  addr.ai_canonname = NULL;
  addr.ai_addr = NULL;
  addr.ai_next = NULL;

  struct addrinfo *result;
  std::string port = std::to_string(port_);

  // Get the address information
  if (getaddrinfo(NULL, port.c_str(), &addr, &result) != 0)
		return false;

  int ret_fd = -1;
  for (struct addrinfo *rp = result; rp != NULL; rp = rp->ai_next) {
    ret_fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

    if (ret_fd == -1)
      continue;  

    // Bind the socket to the address and port number 
    if (bind(ret_fd, rp->ai_addr, rp->ai_addrlen) == 0) {
      sock_family_ = rp->ai_family;
      break;
    }

    // Bind failed. Try the next address/port 
    close(ret_fd);
    ret_fd = -1;
  }

  // Free result
  freeaddrinfo(result);

  if (ret_fd == -1)
    return false;

	// Listen on the ret_fd
  if (listen(ret_fd, SOMAXCONN) != 0) {
		// Failed and close ret_fd
    close(ret_fd);
    return false;
  }

  listen_sock_fd_ = ret_fd;
  *listen_fd = ret_fd;

  return true;
}

bool ServerSocket::Accept(int* const accepted_fd,
                          std::string* const client_addr,
                          uint16_t* const client_port,
                          std::string* const client_dns_name,
                          std::string* const server_addr,
                          std::string* const server_dns_name) const {
  // Accept a new connection on the listening socket listen_sock_fd_.
  // (Block until a new connection arrives.)  Return the newly accepted
  // socket, as well as information about both ends of the new connection,
  // through the various output parameters.

  // STEP 2:
	int fd;
  struct sockaddr_storage addr_s;
  socklen_t addr_s_len = sizeof(addr_s);
  struct sockaddr *addr = reinterpret_cast<struct sockaddr *>(&addr_s);

	while (true) {
    fd = accept(listen_sock_fd_, addr, &addr_s_len);

    if (fd < 0) {
      if ((errno == EINTR) || (errno == EAGAIN)) 
        continue;
      std::cerr << "Failed to accept: " << strerror(errno) << std::endl;
      return false;
    }

		char hostname[1024];  
		// Get host name
  	getnameinfo(addr, sizeof(addr_s), hostname, 1024, nullptr, 0, 0);
  	*client_dns_name = std::string(hostname);
  	hostname[0] = '\0';
		
    if (addr->sa_family == AF_INET) {
    	// IPV4 address and port
    	char str[INET_ADDRSTRLEN];
    	struct sockaddr_in *in4 = reinterpret_cast<struct sockaddr_in *>(addr);
    	inet_ntop(AF_INET, &(in4->sin_addr), str, INET_ADDRSTRLEN);
    	*client_addr = std::string(str);
    	*client_port = ntohs(in4->sin_port);

    	struct sockaddr_in addr;
    	char addr_buf[INET_ADDRSTRLEN];
    	socklen_t addrlen = sizeof(addr);

    	getsockname(fd, (struct sockaddr *) &addr, &addrlen);
    	inet_ntop(AF_INET, &addr.sin_addr, addr_buf, INET_ADDRSTRLEN);
    	*server_addr = std::string(addr_buf);
    	// Get the dns name
    	getnameinfo((const struct sockaddr *) &addr,
      	addrlen, hostname, 1024, nullptr, 0, 0);
  	} else {
    	// IPV6 address and port
    	char str[INET6_ADDRSTRLEN];
    	struct sockaddr_in6 *in6 = reinterpret_cast<struct sockaddr_in6 *>(addr);
    	inet_ntop(AF_INET6, &(in6->sin6_addr), str, INET6_ADDRSTRLEN);
    	*client_addr = std::string(str);
    	*client_port = ntohs(in6->sin6_port);

    	struct sockaddr_in6 addr;
    	char addr_buf[INET6_ADDRSTRLEN];
    	socklen_t addrlen = sizeof(addr);

    	getsockname(fd, (struct sockaddr *) &addr, &addrlen);
    	inet_ntop(AF_INET6, &addr.sin6_addr, addr_buf, INET6_ADDRSTRLEN);
    	*server_addr = std::string(addr_buf);
    	// Get the dns name
    	getnameinfo((const struct sockaddr *) &addr,
      	addrlen, hostname, 1024, nullptr, 0, 0);
  	}

  	*server_dns_name = std::string(hostname);
		
  	break;
  }
	
	// Set the output value to fd
  *accepted_fd = fd;

  return true;
}

}  // namespace hw4
