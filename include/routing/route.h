#ifndef ROUTE_H
#define ROUTE_H

#include "binarytree.h"

struct routes_t {
    struct tree_t *base;
};

struct route_t {
    char *key;
    char *value;
};

void routes_init(struct routes_t *routes);

struct route_t *route_create(char *key, char *value);

void route_insert(struct routes_t *routes, struct route_t *route);

void route_remove(struct routes_t *routes, char *key);

struct route_t *route_find(struct routes_t *routes, char *key);

void route_free(void *route);

void routes_free(struct routes_t *routes);

#endif