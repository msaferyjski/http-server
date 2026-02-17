#include "server.h"

#include "../net/net.h"
#include "../http/http.h"
#include <stdio.h>
#include <stdlib.h>

void server_start(u16 port) {
    socket_t* server_socket = create_server_socket("0.0.0.0", port, NET_TCP);
    if(!server_socket) {
        fprintf(stderr, "Failed to create server");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port: %d\n", port);
    
    while(true) {
        socket_t* client_socket = accept_socket(server_socket);
        printf("Client connected\n");
        i8* buf = read_header(client_socket);
        printf("Read in header: %s", buf);
    }
}