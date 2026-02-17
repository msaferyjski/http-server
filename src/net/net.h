#ifndef NET_H
#define NET_H

#include "../prelude.h"

#include <netinet/in.h>
#include <sys/socket.h>

typedef enum {
    NET_TCP = 1,
    NET_UDP,
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

i32 bind_socket(socket_t* sock);
i32 listen_socket(socket_t* sock, i32 n);
socket_t* create_socket(net_family_t family, const char* addr, short port, net_prot_t prot);
i32 set_socket_opt(socket_t* sock, i32 opt, i32 optval);
socket_t* create_server_socket(const char* addr, short PORT, net_prot_t prot);
socket_t* accept_socket(socket_t* sock);
ssize_t read_socket(socket_t* sock, void* buf, size_t len);
ssize_t write_socket(socket_t* sock, void* buf, size_t len);

#endif