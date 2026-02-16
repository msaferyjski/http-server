#ifndef NET_H
#define NET_H

#include <netinet/in.h>
#include <sys/socket.h>

typedef struct {
    int socket_fd;
    struct sockaddr_in sockaddr;
} socket_t;

typedef enum {
    NET_TCP = 1,
    NET_UDP = 2
} prot_t;

#endif