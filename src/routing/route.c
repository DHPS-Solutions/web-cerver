#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "binarytree.h"
#include "route.h"

static bool cmp(const void *a, const void *b)
{
    struct route_t *a_route = (struct route_t *)a;
    struct route_t *b_route = (struct route_t *)b;

    return (strcmp(a_route->key, b_route->key) > 0);
}

void init_routes(struct routes_t *routes)
{
    routes->base = (struct tree_t *)malloc(sizeof(struct tree_t));
    init_tree(routes->base);
}

struct route_t *create_route(char *key, char *value)
{
    struct route_t *new_route = (struct route_t *)malloc(sizeof(struct route_t));
    if (key != NULL)
        new_route->key = strdup(key);
    else
        new_route->key = NULL;
    if (value != NULL)
        new_route->value = strdup(value);
    else
        new_route->value = NULL;
    return new_route;
}

void insert_route(struct routes_t *routes, struct route_t *route)
{
    insert_tree_node(routes->base, route, cmp, free_route);
}

struct route_t *find_route(struct routes_t *routes, char *key)
{
    struct route_t *route = create_route(key, NULL);
    struct tree_node_t *found_node = find_tree_node(routes->base, route, cmp);
    free(route);
    if (found_node == NULL)
        return NULL;
    
    return found_node->data;
}

void remove_route(struct routes_t *routes, char *key)
{
    struct route_t *route = create_route(key, NULL);
    remove_tree_node(routes->base, route, cmp);
    free(route);
}

void free_route(void *route)
{
    free(((struct route_t *)route)->key);
    free(((struct route_t *)route)->value);
    free(((struct route_t *)route));
}

void free_routes(struct routes_t *routes)
{
    free_tree(routes->base);
    free(routes);
}