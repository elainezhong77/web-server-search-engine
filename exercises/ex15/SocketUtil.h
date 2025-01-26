// Elaine Zhong, ezhong4@uw.edu

#ifndef _SOCKETUTIL_H_
#define _SOCKETUTIL_H_

#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>

// Do a DNS lookup on name and return a socket address
bool LookupName(char *name,
                unsigned short port,
                struct sockaddr_storage *ret_addr,
                size_t *ret_addrlen);

// Connect to the remote host and port (addr/addrlen)
// and return a connected socket
bool Connect(const struct sockaddr_storage &addr,
             const size_t &addrlen,
             int *ret_fd);

// Read a max of readlen bytes from the file descriptor fd
// into the buffer, and return the number of bytes read
int WrappedRead(int fd, unsigned char *buf, int readlen);


// Write writelen bytes to the file descriptor fd from
// the buffer
int WrappedWrite(int fd, unsigned char *buf, int writelen);

#endif  // _SOCKETUTIL_H_