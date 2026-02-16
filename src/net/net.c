#include "net.h"

#include "../prelude.h"

#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_UNTIL_READ 4000

socket_t* create_socket(const char* addr, short PORT, prot_t prot) {
    socket_t* sock = malloc(sizeof(socket_t));
    i32 socket_fd = socket(AF_INET, prot, 0);
    if(socket_fd < 0) {
        perror("net: socket");
        return NULL;
    }

    i32 opt = 1;
    if(setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("net: setsockopt");
        close(socket_fd);
        return NULL;
    }

    sock->socket_fd = socket_fd;
    sock->sockaddr.sin_family = AF_INET;
    sock->sockaddr.sin_port = htons(PORT);
    
    if( inet_pton(AF_INET, addr, &(sock->sockaddr.sin_addr.s_addr)) <= 0) {
        perror("net: inet_pton");
        return NULL;
    }

    if(bind(socket_fd, (struct sockaddr*)&(sock->sockaddr), sizeof(sock->sockaddr)) < 0) {
        perror("net: bind");
        return NULL;
    }

    if(listen(sock->socket_fd, 3) < 0 ) {
        perror("net: listen");
        return NULL;
    }

    return sock;
} 