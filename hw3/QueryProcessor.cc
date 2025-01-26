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

#include "./QueryProcessor.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <vector>

extern "C" {
  #include "./libhw1/CSE333.h"
}

using std::list;
using std::sort;
using std::string;
using std::vector;

namespace hw3 {

QueryProcessor::QueryProcessor(const list<string>& index_list, bool validate) {
  // Stash away a copy of the index list.
  index_list_ = index_list;
  array_len_ = index_list_.size();
  Verify333(array_len_ > 0);

  // Create the arrays of DocTableReader*'s. and IndexTableReader*'s.
  dtr_array_ = new DocTableReader* [array_len_];
  itr_array_ = new IndexTableReader* [array_len_];

  // Populate the arrays with heap-allocated DocTableReader and
  // IndexTableReader object instances.
  list<string>::const_iterator idx_iterator = index_list_.begin();
  for (int i = 0; i < array_len_; i++) {
    FileIndexReader fir(*idx_iterator, validate);
    dtr_array_[i] = fir.NewDocTableReader();
    itr_array_[i] = fir.NewIndexTableReader();
    idx_iterator++;
  }
}

QueryProcessor::~QueryProcessor() {
  // Delete the heap-allocated DocTableReader and IndexTableReader
  // object instances.
  Verify333(dtr_array_ != nullptr);
  Verify333(itr_array_ != nullptr);
  for (int i = 0; i < array_len_; i++) {
    delete dtr_array_[i];
    delete itr_array_[i];
  }

  // Delete the arrays of DocTableReader*'s and IndexTableReader*'s.
  delete[] dtr_array_;
  delete[] itr_array_;
  dtr_array_ = nullptr;
  itr_array_ = nullptr;
}

// This structure is used to store a index-file-specific query result.
typedef struct {
  DocID_t doc_id;  // The document ID within the index file.
  int     rank;    // The rank of the result so far.
} IdxQueryResult;

// Helper method to combine two lists
static list<DocIDElementHeader> CombineLists(const list<DocIDElementHeader> &l1, const list<DocIDElementHeader> &l2);

vector<QueryProcessor::QueryResult>
QueryProcessor::ProcessQuery(const vector<string>& query) const {
  Verify333(query.size() > 0);

  // STEP 1.
  // (the only step in this file)
  vector<QueryProcessor::QueryResult> final_result;

	for (int i = 0; i < array_len_; i++) {
		string first_word = query[0];
    IndexTableReader *index_table = itr_array_[i];
    DocTableReader *doc_table = dtr_array_[i];
		
    // Find the first word 
    DocIDTableReader *first_docid_table = index_table->LookupWord(first_word);

    // If nothing is found, continue to the next one
    if (first_docid_table == nullptr) {
      delete(first_docid_table);
      continue;
    }

  	list<DocIDElementHeader> docid_header_list = first_docid_table->GetDocIDList();

		for (__SIZE_TYPE__ j = 1; j < query.size(); j++) {

      string next_word = query[j];
			
      // Find the next word 
      DocIDTableReader *next_docid_table = index_table->LookupWord(next_word);
			
      // If nothing is found, break
      if (next_docid_table == nullptr) {
        docid_header_list.clear();
        delete(next_docid_table);
        break;
      }

			// Get the current word's list
    	list<DocIDElementHeader> next_docid_header_list = next_docid_table->GetDocIDList();

    	// Combine the two DocID Header lists
    	docid_header_list = CombineLists(docid_header_list, next_docid_header_list);
		
    	// free up the memory used
    	delete(next_docid_table);
		}

    if (docid_header_list.size() != 0) {
      // Initaiize iterator 
      list<DocIDElementHeader>::iterator it;

      for (auto it = docid_header_list.begin(); it != docid_header_list.end(); it++) {
        // Get the element 
        DocIDElementHeader elementHeader = *it;

        IdxQueryResult idx_query_result;
        idx_query_result.doc_id = elementHeader.doc_id;
        idx_query_result.rank = elementHeader.num_positions;
				
        QueryProcessor::QueryResult query_result;
				
        // Get the file name 
        int lookup_result = doc_table->LookupDocID(idx_query_result.doc_id, &query_result.document_name);
				
        // Check the lookup result
        Verify333(lookup_result == 1);
				
        // Set the query result rank 
        query_result.rank = idx_query_result.rank;
				
        // Add the query result to the final result
        final_result.push_back(query_result);
      }
    } else {
      delete(first_docid_table);
      continue;
    }
    delete(first_docid_table);
	}
  // Sort the final results.
  sort(final_result.begin(), final_result.end());
  return final_result;
}

static list<DocIDElementHeader> CombineLists(const list<DocIDElementHeader> &l1,
                      const list<DocIDElementHeader> &l2) {

  list<DocIDElementHeader> final_list;

  // Loop through the first list
  for (auto first_itr = l1.begin(); first_itr != l1.end(); first_itr++) {
    DocIDElementHeader first_doc_id = *first_itr;
    IdxQueryResult query_result;
    query_result.rank = first_doc_id.num_positions;
    query_result.doc_id = first_doc_id.doc_id;

    // Flag if find in second list
    int sec_is_present = 0;
		
    // Loop through the second list
    for (auto sec_itr = l2.begin(); sec_itr != l2.end(); sec_itr++) {
      DocIDElementHeader sec_doc_id = *sec_itr;
      // If found result, increment rank and break from loop
      if (sec_doc_id.doc_id == query_result.doc_id) {
        sec_is_present = 1;
        query_result.rank += sec_doc_id.num_positions;
        break;
      }
    }
    if (sec_is_present == 1) {
      final_list.push_back(DocIDElementHeader(query_result.doc_id, query_result.rank));
    }
  }
  return final_list;
}
}  // namespace hw3
