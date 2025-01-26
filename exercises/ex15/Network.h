// Elaine Zhong, ezhong4@uw.edu

#ifndef _NETWORK_H_
#define _NETWORK_H_

// Connect to remote host
bool Connect(const struct sockaddr_storage &addr,
             const size_t &addrlen,
             int *ret_fd);

// Look up the IP address and port
bool LookupName(char *name,
                unsigned short port,
                struct sockaddr_storage *ret_addr,
                size_t *ret_addrlen);

#endif