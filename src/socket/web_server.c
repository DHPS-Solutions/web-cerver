#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "web_server.h"

void init_server(struct server_t *server, int port)
{
    server->port = port;
    server->socket = socket(PF_INET, SOCK_STREAM, 0);
    if (server->socket < 0) {
        perror("socket");
        exit(1);
    }

    if (setsockopt(server->socket, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), &(int){1}, sizeof(int)) < 0) {
        perror("setsockopt");
        exit(1);
    }
    
    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    
    if (bind(server->socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(server->socket, 5) != 0) {
        perror("listen");
        exit(1);
    }
}