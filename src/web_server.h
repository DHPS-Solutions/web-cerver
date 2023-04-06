#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>

#include "web_server.h"
#include "logger.h"
#include "fileio/fileio.h"
#include "routing/route.h"
#include "threadpool/threadpool.h"

/* Structs */

/**
 * Struct for a web server.
 * @param port The port to listen on.
 * @param socket The socket to listen on.
 */
struct web_server_t {
    int port;
    int socket;
    bool running;
    struct threadpool_t *threadpool;
    struct routes_t *routes;
    struct connections_t *connections;
};

/**
 * Struct for connections.
 * @param connections The connections.
 * @param index The current index of the connections.
 * @param cap The max amount of connections.
 */
struct connections_t {
    int *connections;
    int index;
    int cap;
};

/**
 * Struct for thread data.
 * @param connection The connection to the client.
 * @param routes The routes to serve.
 * @param running Whether the server is running.
 */
struct thread_data_t {
    int connection;
    struct routes_t *routes;
    bool *running;
};

/* Methods */

/**
 * Initialize a web server.
 * @param server The server to initialize.
 * @param port The port to listen on.
 * @return 0 on success, -1 on failure.
 */
int init_web_server(struct web_server_t *server, int port, int connections, int threads, int q_size, int num_routes, ...);

/**
 * Run a web server.
 * @param server The server to start.
 * @return 0 on success, -1 on failure.
 */
int run_web_server(struct web_server_t *server);

#endif