# web-cerver
A simple web-server in C.

Implements the queue and binary-tree from dhps-lib. 

To run the server simply:

- Clone the repository
- cd to src
- gcc server.c web_server.c threadpool/threadpool.c threadpool/queue.c routing/route.c routing/binarytree.c fileio/fileio.c -lpthread
- ./a.out
