# web-cerver
A simple web-server in C.

Implements the queue and binary-tree from callib. ([https://github.com/callumgran/callib](https://github.com/callumgran/callib))

To run the server, first add your html/css/js files to the static folder.
Then add the filenames to the web_server_init function like shown below.
First route, then file.
E.g `"/", "./static/index.html"`
```c
int main()
{
	struct web_server_t server;
	if (web_server_init(&server, 80, 10, 10, 20, 5,
                                "/", "./static/index.html",
                                "/home", "./static/index.html",
                                "/about", "./static/about.html",
                                "/contact", "./static/contact.html",
                                "/styles.css", "./static/styles.css"
                      ) != 0) {
		LOG_ERR("Failed to initialize web server\n");
		exit(1);
	}

	web_server_run(&server);

	return 0;
}
```

To run the server after you have configured it, simply write `make` followed by `./server`.
