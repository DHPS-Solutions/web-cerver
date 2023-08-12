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

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <routing/binarytree.h>
#include <routing/route.h>

static int cmp(const void *a, const void *b)
{
	struct route_t *a_route = (struct route_t *)a;
	struct route_t *b_route = (struct route_t *)b;

	return strcmp(a_route->key, b_route->key);
}

char *strdup(const char *c)
{
	char *dup = malloc(strlen(c) + 1);

	if (dup != NULL)
		strcpy(dup, c);

	return dup;
}

void routes_init(struct routes_t *routes)
{
	routes->base = (struct tree_t *)malloc(sizeof(struct tree_t));
	tree_init(routes->base, cmp);
}

struct route_t *route_create(char *key, char *value)
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

void route_insert(struct routes_t *routes, struct route_t *route)
{
	struct tree_node_t *new_node = malloc(sizeof(struct tree_node_t));
	tree_node_init(new_node, route, route_free);
	tree_node_insert(routes->base, new_node);
}

struct route_t *route_find(struct routes_t *routes, char *key)
{
	struct route_t *route = route_create(key, NULL);
	struct tree_node_t *found_node = tree_search(routes->base, route);
	free(route);
	if (found_node == NULL)
		return NULL;

	return found_node->data;
}

void route_remove(struct routes_t *routes, char *key)
{
	struct route_t *route = route_create(key, NULL);
	tree_node_remove(routes->base, route);
	free(route);
}

void route_free(void *route)
{
	free(((struct route_t *)route)->key);
	free(((struct route_t *)route)->value);
	free(((struct route_t *)route));
}

void routes_free(struct routes_t *routes)
{
	tree_free(routes->base);
}