#include "server/server.h"

#define PORT 8080

i32 main(void) {
    server_start(PORT);
    return 0;
}