/*
 *  Copyright (C) 2022-2023 Callum Gran
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

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdbool.h>
#include <sys/types.h>

typedef int compare_fn_t(const void *, const void *);
typedef void free_fn_t(void *);

struct tree_node_t {
	void *data;
	free_fn_t *free_func;
	struct tree_node_t *left;
	struct tree_node_t *right;
	struct tree_node_t *parent;
};

struct tree_t {
	struct tree_node_t *root;
	compare_fn_t *cmp;
};

bool tree_init(struct tree_t *tree, compare_fn_t cmp);
bool tree_node_init(struct tree_node_t *node, void *data, free_fn_t *free_func);
bool tree_free(struct tree_t *tree);
void tree_node_free(struct tree_node_t *node);

bool tree_node_insert(struct tree_t *tree, struct tree_node_t *node);
bool tree_node_remove(struct tree_t *tree, const void *data);

struct tree_node_t *tree_search(struct tree_t *tree, const void *data);
size_t tree_find_height(const struct tree_t *tree);
size_t tree_node_find_height(const struct tree_node_t *node);

#endif