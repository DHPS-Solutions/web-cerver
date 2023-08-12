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

#include <stdbool.h>
#include <stdlib.h>

#include <routing/binarytree.h>

bool tree_init(struct tree_t *tree, compare_fn_t cmp)
{
	if (tree == NULL)
		return false;

	tree->root = NULL;
	tree->cmp = cmp;

	return true;
}

bool tree_node_init(struct tree_node_t *node, void *data, free_fn_t *free_func)
{
	if (node == NULL)
		return false;

	if (data == NULL)
		return false;

	node->data = data;
	node->free_func = free_func;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;

	return true;
}

void tree_node_free(struct tree_node_t *node)
{
	if (node) {
		tree_node_free(node->left);
		tree_node_free(node->right);
		node->free_func(node->data);
		free(node);
	}
}

bool tree_free(struct tree_t *tree)
{
	if (tree == NULL)
		return false;

	tree_node_free(tree->root);

	return true;
}

bool tree_node_insert(struct tree_t *tree, struct tree_node_t *node)
{
	if (tree == NULL)
		return false;

	if (node == NULL)
		return false;

	if (!tree->root) {
		tree->root = node;
	} else {
		struct tree_node_t *current = tree->root;
		struct tree_node_t *parent = NULL;

		while (current) {
			parent = current;
			if (tree->cmp(node->data, current->data) < 0) {
				current = current->left;
			} else {
				current = current->right;
			}
		}

		if (tree->cmp(node->data, parent->data) < 0) {
			parent->left = node;
		} else {
			parent->right = node;
		}
		node->parent = parent;
	}

    return true;
}

struct tree_node_t *tree_search(struct tree_t *tree, const void *data)
{
	if (tree == NULL)
		return NULL;

	if (data == NULL)
		return NULL;

	struct tree_node_t *current = tree->root;
	while (current) {
		if (tree->cmp(data, current->data) < 0) {
			current = current->left;
		} else if (tree->cmp(current->data, data) < 0) {
			current = current->right;
		} else {
			return current;
		}
	}

	return NULL;
}

size_t tree_node_find_height(const struct tree_node_t *node)
{
	if (!node) {
		return 0;
	} else {
		int left_height = tree_node_find_height(node->left);
		int right_height = tree_node_find_height(node->right);
		if (left_height >= right_height)
			return left_height + 1;
		else
			return right_height + 1;
	}
}

size_t tree_find_height(const struct tree_t *tree_t)
{
	return tree_node_find_height(tree_t->root);
}

bool tree_node_remove(struct tree_t *tree, const void *data)
{
	if (tree == NULL)
		return false;

	if (data == NULL)
		return false;

	struct tree_node_t *current = tree_search(tree, data);

	if (!current)
		return false;

	if (!current->left && !current->right) {
		if (current == tree->root) {
			tree->root = NULL;
		} else {
			if (current->parent->left == current) {
				current->parent->left = NULL;
			} else {
				current->parent->right = NULL;
			}
		}
		tree_node_free(current);
	} else if (!current->left || !current->right) {
		struct tree_node_t *child = current->left ? current->left : current->right;
		if (current == tree->root) {
			tree->root = child;
		} else {
			if (current->parent->left == current) {
				current->parent->left = child;
			} else {
				current->parent->right = child;
			}
		}
		child->parent = current->parent;
		tree_node_free(current);
	} else {
		struct tree_node_t *successor = current->right;
		while (successor->left) {
			successor = successor->left;
		}
		current->data = successor->data;
		if (successor->parent->left == successor) {
			successor->parent->left = successor->right;
		} else {
			successor->parent->right = successor->right;
		}
		if (successor->right) {
			successor->right->parent = successor->parent;
		}
		tree_node_free(successor);
	}
	return true;
}