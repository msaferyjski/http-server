#include "../net/net.h"
#include <stdio.h>
#include <stdlib.h>

void start(i16 port) {
    socket_t* server_socket = create_server_socket("0.0.0.0", port, NET_TCP);
    if(!server_socket) {
        fprintf(stderr, "Failed to create server");
        exit(EXIT_FAILURE);
    }
    
    while(true) {

    }
}