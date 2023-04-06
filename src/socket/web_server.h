#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/* Structs */

/**
 * Struct for a web server.
 * @param port The port to listen on.
 * @param socket The socket to listen on.
 */
struct server_t {
    int port;
    int socket;
};

/* Methods */

/**
 * Initialize a web server.
 * @param server The server to initialize.
 * @param port The port to listen on.
 */
void init_server(struct server_t *server, int port);

#endif