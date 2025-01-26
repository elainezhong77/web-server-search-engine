// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Builds a full path and prints that path's file
int BuildPathAndPrint(char *dir, char *file);
// Prints out a file
int PrintFile(char *file);

/* 
 * Reads and prints bytes of a file one by one in reverse order.
 */
int main(int argc,  char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: ./ex7 <path>\n");
    return EXIT_FAILURE;
  }
  DIR *dirp = opendir(argv[1]);
  if (dirp == NULL) {
    fprintf(stderr, "Could not open directory\n");
    return EXIT_FAILURE;
  }

  struct dirent *entry;
  entry = readdir(dirp);
  while (entry != NULL) {
    char *file = entry->d_name;
    if (strcmp(file + strlen(file) - 4, ".txt") == 0) {
      BuildPathAndPrint(argv[1], file);
    }
    // Read the next entry in the directory
    entry = readdir(dirp);
  }
  closedir(dirp);
  return EXIT_SUCCESS;
}

int BuildPathAndPrint(char *dir, char *file) {
  if (file == NULL) {
    fprintf(stderr, "Could not open file\n");
    return EXIT_FAILURE;
  }
  // Allocate memory and build the full path
  uint16_t dir_length = strlen(dir) + strlen(file);
  char *file_path = (char *) malloc(sizeof(char) * (dir_length + 2));
  snprintf(file_path, dir_length + 2, "%s/%s", dir, file);

  PrintFile(file_path);
  free(file_path);
  return EXIT_SUCCESS;
}

int PrintFile(char *file) {
  int fd = open(file, O_RDONLY);
  if (fd == -1) {
    fprintf(stderr, "Could not open file\n");
    return EXIT_FAILURE;
  }
  char buffer[BUFFER_SIZE];
  int result;
  while (1) {
    result = read(fd, buffer, BUFFER_SIZE);
    if (result == 0) {
      break;
    }
    if (result == -1) {
      if (errno != EINTR && errno != EAGAIN) {
        perror("Read failed\n");
        return EXIT_FAILURE;
      }
      continue;
    }
    fwrite(buffer, 1, result, stdout);
  }
  close(fd);
  return EXIT_SUCCESS;
}
