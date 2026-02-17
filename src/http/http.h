#ifndef HTTP_H
#define HTTP_H

#include "../prelude.h"
#include "../net/net.h"

i8* read_header(socket_t* client_sock);

#endif