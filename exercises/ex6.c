// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

/* 
 * Reads and prints bytes of a file one by one in reverse order.
 */
int main(int argc,  char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: ./ex6 <path>\n");
    return EXIT_FAILURE;
  }

  FILE *file = fopen(argv[1], "rb");

  if (file == NULL) {
    fprintf(stderr, "File could not be opened\n");
    return EXIT_FAILURE;
  }

  // Move the file pointer to the end of the file to determine its size
  fseek(file, 0, SEEK_END);
  int64_t size = ftell(file);

  char currChar;
  for (int i = size - 1; i >= 0; i--) {
    // Move the file pointer to the i-th byte from the beginning of the file
    fseek(file, i, SEEK_SET);
    // Read one byte at the current position
    fread(&currChar, sizeof(char), 1, file);
    printf("%c", currChar);
  }

  fclose(file);
  return EXIT_SUCCESS;
}
