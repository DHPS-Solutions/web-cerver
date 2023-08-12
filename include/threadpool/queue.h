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

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <sys/types.h>

struct queue_t {
	void **items;
	size_t start;
	size_t end;
	size_t size;
	size_t max;
};

bool queue_init(struct queue_t *queue, const size_t size);
bool queue_free(struct queue_t *queue);

bool queue_empty(const struct queue_t *queue);
bool queue_full(const struct queue_t *queue);

bool queue_push(struct queue_t *queue, void *item);
void *queue_pop(struct queue_t *queue);
void *queue_get(const struct queue_t *queue);

#endif