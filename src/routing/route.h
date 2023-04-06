#ifndef ROUTE_H
#define ROUTE_H

#include "binarytree.h"

/* Structs */

/**
 * Struct used to represent a routes.
 * @param base first route in binary tree of routes.
*/
struct routes_t {
    struct tree_t *base;
};

/**
 * Struct used to represent a route.
 * @param key key of the route.
 * @param value value of the route.
*/
struct route_t {
    char *key;
    char *value;
};

/* Methods */

/**
 * Function used to initialize a routes.
 * @param routes routes to initialize.
 */
void init_routes(struct routes_t *routes);

/**
 * Function used to create a route.
 * @param key key of the route.
 * @param value value of the route.
 * @return route created.
*/
struct route_t *create_route(char *key, char *value);

/**
 * Function used to insert a route in a routes.
 * @param routes routes to insert the route to.
 * @param route route to insert.
*/
void insert_route(struct routes_t *routes, struct route_t *route);

/**
 * Function used to remove a route from a routes.
 * @param routes routes to remove the route from.
 * @param key key of the route to remove.
*/
void remove_route(struct routes_t *routes, char *key);

/**
 * Function used to find a route in a routes.
 * @param routes routes to find the route.
 * @param key key of the route to find.
 * @return route found.
*/
struct route_t *find_route(struct routes_t *routes, char *key);

/**
 * Function used to free a route.
 * @param route route to free.
*/
void free_route(void *route);

/**
 * Function used to free a routes.
 * @param routes routes to free.
*/
void free_routes(struct routes_t *routes);

#endif