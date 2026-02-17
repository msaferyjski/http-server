#include "net.h"

#include "../prelude.h"

#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

i32 bind_socket(socket_t* sock) {
    if (!sock)
        return -1;

    return bind(sock->socket_fd, (struct sockaddr*)&(sock->sockaddr), sizeof(sock->sockaddr));
}

i32 listen_socket(socket_t* sock, i32 n) {
    if (!sock || sock->type == NET_UDP) 
        return -1;

    return listen(sock->socket_fd, n);
}

socket_t* create_socket(net_family_t family, const char* addr, u16 port, net_prot_t prot) {
    socket_t* sock = malloc(sizeof(socket_t));

    if (!sock) {
        perror("net: create_socket malloc");
        return NULL;
    }

    // translate str address to bin presentation
    if (inet_pton(family, addr, &(sock->sockaddr.sin_addr.s_addr)) <= 0) {
        free(sock);
        return NULL;
    }

    i32 socket_fd = socket(family, prot, 0);
    if (socket_fd == -1) {
        free(sock);
        return NULL;
    }

    sock->socket_fd = socket_fd;
    sock->sockaddr.sin_family = family;
    sock->sockaddr.sin_port = htons(port);
    sock->type = prot;
    return sock;
} 

void destroy_socket(socket_t* sock) {
    if (!sock) 
        return;
    close(sock->socket_fd);
    free(sock);
}

i32 set_socket_opt(socket_t* sock, i32 opt, i32 optval) {
    if (!sock) 
        return -1;
    
    return setsockopt(sock->socket_fd, SOL_SOCKET, opt, &optval, sizeof(optval));
}

socket_t* create_server_socket(const char* addr, u16 port, net_prot_t prot) {
    if (!addr)
        return NULL;

    socket_t* sock = create_socket(IPV4, addr, port, prot);
    if (!sock) {
        perror("net: create_socket");
        return NULL;
    }

    if (set_socket_opt(sock, SO_REUSEADDR, 1)) {
        perror("net: setsockopt");
        destroy_socket(sock);
        return NULL;
    }
 
    if (bind_socket(sock) == -1) {
        perror("net: bind");
        destroy_socket(sock);
        return NULL;
    }

    if (listen_socket(sock, 3) == -1 ) {
        perror("net: listen_socket");
        destroy_socket(sock);
        return NULL;
    }

    return sock;
} 

socket_t* accept_socket(socket_t* sock) {
    if (!sock)
        return NULL;

    socket_t* client_sock = malloc(sizeof(socket_t));
    socklen_t addr_len = sizeof(client_sock->sockaddr);
    i32 client_fd = accept(sock->socket_fd, (struct sockaddr*) &(client_sock->sockaddr), &addr_len);
    if (client_fd == -1) {
        perror("net: accept");
        free(client_sock);
        return NULL;
    }

    client_sock->socket_fd = client_fd;
    return client_sock;
}

ssize_t read_socket(socket_t* sock, void* buf, size_t len) {
    if (!sock || !buf)
        return -1;

    return recv(sock->socket_fd, buf, len, 0);
}

ssize_t write_socket(socket_t* sock, void* buf, size_t len) {
    if (!sock || !buf) 
        return -1;

    return send(sock->socket_fd, buf, len, 0);
}