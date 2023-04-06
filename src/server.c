#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <netinet/in.h>

#include "logger.h"
#include "fileio/fileio.h"
#include "web_server.h"
#include "routing/route.h"
#include "threadpool/threadpool.h"


int main()
{
    struct web_server_t server;
    if (init_web_server(&server, 8087, 10, 10, 20, 5,
                    "/", "./static/index.html",
                    "/home", "./static/index.html",
                    "/about", "./static/about.html",
                    "/contact", "./static/contact.html",
                    "/styles.css", "./static/styles.css"
                    ) != 0) {
        LOG_ERR("Failed to initialize web server\n");
        exit(1);
    }
    
    run_web_server(&server);

    return 0;
}