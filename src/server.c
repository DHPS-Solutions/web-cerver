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

#include <fileio/fileio.h>
#include <logger.h>
#include <routing/route.h>
#include <threadpool/threadpool.h>
#include <web_server.h>

int main()
{
	struct web_server_t server;
	if (web_server_init(&server, 80, 10, 10, 20, 5, "/", "./static/index.html", "/home",
						"./static/index.html", "/about", "./static/about.html", "/contact",
						"./static/contact.html", "/styles.css", "./static/styles.css") != 0) {
		LOG_ERR("Failed to initialize web server\n");
		exit(1);
	}

	web_server_run(&server);

	return 0;
}