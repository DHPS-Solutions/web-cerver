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

#include <threadpool/queue.h>

bool queue_init(struct queue_t *queue, const size_t size)
{
	if (queue == NULL)
		return false;

	if (size == 0)
		return false;

	queue->items = (void *)(malloc(size * sizeof(void *)));
	queue->max = size;
	queue->start = queue->end = queue->size = 0;

	return true;
}

bool queue_free(struct queue_t *queue)
{
	if (queue == NULL)
		return false;

	free(queue->items);

	return true;
}

bool queue_empty(const struct queue_t *queue)
{
	if (queue == NULL)
		return false;

	return !queue->size;
}

bool queue_full(const struct queue_t *queue)
{
	if (queue == NULL)
		return false;

	return queue->size == queue->max;
}

bool queue_push(struct queue_t *queue, void *item)
{
	if (queue == NULL || item == NULL)
		return false;

	if (queue_full(queue))
		return false;

	queue->items[queue->end] = item;
	queue->end = (queue->end + 1) % queue->max;
	++queue->size;
	return true;
}

void *queue_pop(struct queue_t *queue)
{
	if (queue == NULL)
		return NULL;

	if (queue_empty(queue))
		return NULL;

	void *element = queue->items[queue->start];
	queue->start = (queue->start + 1) % queue->max;
	queue->size--;
	return element;
}

void *queue_get(const struct queue_t *queue)
{
	if (queue == NULL)
		return NULL;

	if (queue_empty(queue))
		return NULL;

	return queue->items[queue->start];
}