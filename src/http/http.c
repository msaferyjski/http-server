#include "http.h"

#include "../net/net.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <memory.h>

#define MAX_HEADER_SIZE 4048

i8* read_header(socket_t* client_sock) {
    if(!client_sock) 
        return NULL;

    i8* buf = malloc(MAX_HEADER_SIZE);
    if(!buf) {
        perror("http: read_header malloc");
        return NULL;
    }
    
    // TODO 
    // implement header parsing logic
    // read up to MAX_HEADER_SIZE
    // check last 4 bytes for crlf
    // ret buffer

    free(buf);
    return NULL;
}