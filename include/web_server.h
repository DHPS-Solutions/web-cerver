/*
 *  Copyright (C) 2023 Callum Gran
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <fileio/fileio.h>
#include <logger.h>
#include <routing/route.h>
#include <threadpool/threadpool.h>
#include <web_server.h>

struct web_server_t {
	int port;
	int socket;
	bool running;
	struct threadpool_t *threadpool;
	struct routes_t *routes;
	struct connections_t *connections;
};

struct connections_t {
	int *connections;
	int index;
	int cap;
};

struct thread_data_t {
	int connection;
	struct routes_t *routes;
	bool *running;
};


int web_server_init(struct web_server_t *server, int port, int connections, int threads, int q_size,
					int num_routes, ...);

int web_server_run(struct web_server_t *server);

#endif