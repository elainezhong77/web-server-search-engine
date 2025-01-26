// Elaine Zhong, ezhong4@uw.edu

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

#include "./Network.h"

#define BUFFER_SIZE 1024

void Usage(char *progname);
void HandleClient(int c_fd, struct sockaddr *addr, size_t addrlen,
                  int sock_family);

int main(int argc, char **argv) {
  // Expect the port number as a command line argument.
  if (argc != 2) {
    Usage(argv[0]);
  }

  int sock_family;
  int listen_fd = Listen(argv[1], &sock_family);
  if (listen_fd <= 0) {
    // We failed to bind/listen to a socket.  Quit with failure.
    std::cerr << "Couldn't bind to any addresses." << std::endl;
    return EXIT_FAILURE;
  }

  // Loop forever, accepting a connection from a client and doing
  // an echo trick to it.
  while (1) {
    struct sockaddr_storage caddr;
    socklen_t caddr_len = sizeof(caddr);
    int client_fd = accept(listen_fd,
                           reinterpret_cast<struct sockaddr *>(&caddr),
                           &caddr_len);
    if (client_fd < 0) {
      if ((errno == EINTR) || (errno == EAGAIN) || (errno == EWOULDBLOCK))
        continue;
      std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
      break;
    }

    HandleClient(client_fd,
                 reinterpret_cast<struct sockaddr *>(&caddr),
                 caddr_len,
                 sock_family);

    break;
  }

  // Close up shop.
  close(listen_fd);
  return EXIT_SUCCESS;
}

void Usage(char *progname) {
  std::cerr << "usage: " << progname << " port" << std::endl;
  exit(EXIT_FAILURE);
}

void HandleClient(int c_fd, struct sockaddr *addr, size_t addrlen,
                  int sock_family) {
  // Loop, reading data and echo'ing it back, until the client
  // closes the connection.
  char clientbuf[BUFFER_SIZE];
  while (1) {
    ssize_t res = read(c_fd, clientbuf, BUFFER_SIZE - 1);
    if (res == 0) {
      break;
    }

    if (res == -1) {
      if ((errno == EAGAIN) || (errno == EINTR)){
        continue;
      }
      std::cerr << " [Error on client socket: ";
      std::cerr << strerror(errno) << "]" << std::endl;
      break;
    }

    for (int i = 0; i < res; i++) {
      std::cout << clientbuf[i];
    }
  }

  close(c_fd);
}