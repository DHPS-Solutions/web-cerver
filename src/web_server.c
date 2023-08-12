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

static void check_quit(void *arg)
{
	struct web_server_t *server = (struct web_server_t *)arg;

	while (getc(stdin) != 'q')
		;

	shutdown(server->socket, SHUT_RDWR);
	close(server->socket);
	LOG_INFO("Quitting...\n");

	server->running = false;
}

static void set_nonblocking(int socket)
{
	int flags = fcntl(socket, F_GETFL, 0);

	flags |= O_NONBLOCK;

	fcntl(socket, F_SETFL, flags);
}

static int serve_file(struct routes_t *routes, int socket, char *buffer)
{
	LOG_INFO("HTTP REQUEST");

	char *route = "";
	char *method = "";

	char *header = strtok(buffer, "\n");

	char *token = strtok(header, " ");

	int i = 0;

	while (token != NULL) {
		if (i == 0) {
			method = token;
		} else if (i == 1) {
			route = token;
		}

		token = strtok(NULL, " ");
		i++;
	}

	char template[100] = "";

	if (strcmp(route, "/favicon.ico") == 0)
		return -1;

	struct route_t *destination = route_find(routes, route);

	if (destination == NULL)
		strcat(template, "./static/404.html");
	else
		strcat(template, destination->value);

	FILE *file = fopen(template, "r");

	struct file_data_t *fd = read_file(file);

	if (fd == NULL) {
		LOG_ERR("Could not read file: %s", template);
		return -1;
	}

	fclose(file);

	char http_header[4096] = "HTTP/1.1 200 OK\r\n\r\n";
	strcat(http_header, fd->data);
	strcat(http_header, "\r\n\r\n");
	send(socket, http_header, sizeof(http_header), MSG_DONTWAIT);

	file_data_free(fd);

	LOG_INFO("SERVED: %s", template);

	return 0;
}

static void http_listen(void *arg)
{
	struct thread_data_t *data = (struct thread_data_t *)arg;

	int client_socket = data->connection;

	struct routes_t *routes = data->routes;
	char buffer[4096] = { 0 };
	size_t bytes_recv = 0;

	bytes_recv = recv(client_socket, buffer, 4096, 0);

	if (bytes_recv > 0) {
		LOG_INFO("Received %zu bytes", bytes_recv);
		serve_file(routes, client_socket, buffer);
	} else {
		LOG_ERR("Failed to receive data");
	}

	shutdown(client_socket, SHUT_RDWR);
	close(client_socket);

	free(arg);

	LOG_INFO("Closed connection to: %d", client_socket);
}

int web_server_init(struct web_server_t *server, int port, int connections, int threads, int q_size,
					int num_routes, ...)
{
	server->port = port;
	server->socket = socket(PF_INET, SOCK_STREAM, 0);
	if (server->socket < 0) {
		LOG_ERR("socket");
		return -1;
	}

#ifdef __APPLE__
	int optname = SO_REUSEADDR;
#else
	int optname = SO_REUSEADDR | 15;
#endif

	if (setsockopt(server->socket, SOL_SOCKET, optname, &(int){ 1 }, sizeof(int)) < 0) {
		LOG_ERR("setsockopt");
		return -1;
	}

	struct sockaddr_in address = { 0 };
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(server->socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
		LOG_ERR("bind");
		return -1;
	}

	if (listen(server->socket, 5) != 0) {
		LOG_ERR("listen");
		return -1;
	}

	server->connections = malloc(sizeof(struct connections_t));
	server->connections->connections = malloc(sizeof(int) * connections);
	server->connections->cap = connections;

	server->threadpool = malloc(sizeof(struct threadpool_t));
	threadpool_init(server->threadpool, threads, q_size);

	server->routes = malloc(sizeof(struct routes_t));
	routes_init(server->routes);

	va_list args;
	va_start(args, num_routes);

	for (int i = 0; i < num_routes; i++) {
		char *route = va_arg(args, char *);
		char *value = va_arg(args, char *);

		if (route == NULL || value == NULL)
			return -1;

		route_insert(server->routes, route_create(route, value));
	}

	va_end(args);

	return 0;
}

void free_web_server(struct web_server_t *server)
{
	routes_free(server->routes);
	free(server->routes);
	threadpool_free(server->threadpool);
	free(server->threadpool);
	free(server->connections);
}

static void close_connections(struct connections_t *connections)
{
	LOG_INFO("Closing connections");
	for (int i = 0; i < connections->cap; i++) {
		if (send(connections->connections[i], "Server shutting down", 20, MSG_NOSIGNAL) > 0) {
			shutdown(connections->connections[i], SHUT_RDWR);
			close(connections->connections[i]);
		}
	}
}

static void insert_connection(struct connections_t *connections, int connection)
{
	connections->index++;
	connections->index = connections->index % connections->cap;
	connections->connections[connections->index] = connection;
}

int web_server_run(struct web_server_t *server)
{
	int client_socket = -1;

	threadpool_start(server->threadpool);

	server->running = true;

	LOG_INFO("Server started, press 'q' to quit\n");

	submit_worker_task(server->threadpool, check_quit, (void *)server);

	set_nonblocking(server->socket);

	while (server->running) {
		client_socket = accept(server->socket, NULL, NULL);

		if (client_socket != -1) {
			insert_connection(server->connections, client_socket);

			LOG_INFO("HTTP client connected %d ", client_socket);

			struct thread_data_t *data =
				(struct thread_data_t *)malloc(sizeof(struct thread_data_t));
			data->connection = client_socket;
			data->routes = server->routes;
			data->running = &server->running;
			submit_worker_task(server->threadpool, http_listen, data);
			client_socket = -1;
		}
	}

	LOG_INFO("Shutting down http_server.");

	close_connections(server->connections);
	threadpool_stop(server->threadpool);
	free_web_server(server);
	return 0;
}
