// Elaine Zhong, ezhong4@uw.edu

#ifndef _NETWORK_H_
#define _NETWORK_H_

/*
 * Sets up a socket for listening on the specified port number.
 * Creates and configures the socket and binds it to the port. 
 * Marks it as a listening socket. Returns the file descriptor
 * of the listening socket.
 */
int Listen(char *portnum, int *sock_family);

#endif  // _NETWORK_H_