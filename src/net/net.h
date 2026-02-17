#ifndef NET_H
#define NET_H

#include "../prelude.h"

#include <netinet/in.h>
#include <sys/socket.h>

typedef enum {
    NET_TCP = 1,
    NET_UDP
} net_prot_t;

typedef enum {
    IPV4 = 2,
    IPV6 = 10,
} net_family_t;

typedef struct {
    int socket_fd;
    struct sockaddr_in sockaddr;
    net_prot_t type;
} socket_t;


socket_t* create_server_socket(const char* addr, short PORT, net_prot_t prot);
socket_t* accept_socket(socket_t* sock);
ssize_t read_socket(socket_t* sock, void* buf, size_t len);
ssize_t write_socket(socket_t* sock, void* buf, size_t len);

#endif