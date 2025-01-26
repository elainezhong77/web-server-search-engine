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

// Feature test macro for strtok_r (c.f., Linux Programming Interface p. 63)
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "libhw1/CSE333.h"
#include "./CrawlFileTree.h"
#include "./DocTable.h"
#include "./MemIndex.h"

//////////////////////////////////////////////////////////////////////////////
// Helper function declarations, constants, etc
static void Usage(void);
// Print the filenames and its rank for the current query
// Returns nothing if the word or set of charcters is not found in any file
static void ProcessQueries(DocTable* doc_table, MemIndex* index,
                          char **query, int count);
// static int GetNextLine(FILE* f, char** ret_str);


//////////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char** argv) {
  if (argc != 2) {
    Usage();
  }

  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //
  //  - Crawl from a directory provided by argv[1] to produce and index
  //  - Prompt the user for a query and read the query from stdin, in a loop
  //  - Split a query into words (check out strtok_r)
  //  - Process a query against the index and print out the results
  //
  // When searchshell detects end-of-file on stdin (cntrl-D from the
  // keyboard), searchshell should free all dynamically allocated
  // memory and any other allocated resources and then exit.
  //
  // Note that you should make sure the fomatting of your
  // searchshell output exactly matches our solution binaries
  // to get full points on this part.
  DocTable *doc_table;
  MemIndex *index;

  if (!CrawlFileTree(argv[1], &doc_table, &index)) {
    printf("Crawl path '%s' failed \n", argv[1]);
    Usage();
  }

  char *line = (char *) malloc(sizeof(char) * 1024);
  char **query = (char **) malloc(sizeof(char *) * 256);

  printf("enter query:\n");
  while (fgets(line, 1024, stdin) != NULL) {
    for (int i = 0; line[i] != '\0'; i++) {
      line[i] = tolower(line[i]);
      if (line[i] == '\n') {
        line[i] = '\0';
      }
    }
    char *token = strtok_r(line, " ", &line);
    int count = 0;

    while (token != NULL) {
      query[count++] = token;
      token = strtok_r(NULL, " ", &line);
    }
    ProcessQueries(doc_table, index, query, count);
    printf("enter query:\n");
  }
  printf("shutting down...\n");
  free(query);

  DocTable_Free(doc_table);
  MemIndex_Free(index);

  return EXIT_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////////
// Helper function definitions

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative " \
          "path to a directory to build an index under.\n");
  exit(EXIT_FAILURE);
}

static void ProcessQueries(DocTable* doc_table, MemIndex* index,
                          char **query, int count) {
  LinkedList *list = MemIndex_Search(index, query, count);
  if (list == NULL) {
    return;
  }
  LLIterator *ll_it = LLIterator_Allocate(list);
  while (LLIterator_IsValid(ll_it)) {
    SearchResult *result;
    LLIterator_Get(ll_it, (LLPayload_t *) &result);

    printf("%s (%d) \n", DocTable_GetDocName(doc_table, result->doc_id),
                                            result->rank);
    LLIterator_Next(ll_it);
  }
  LLIterator_Free(ll_it);
  LinkedList_Free(list, &free);
}

/*
static int GetNextLine(FILE *f, char **ret_str) {
  return -1;  // you may want to change this
}
*/
