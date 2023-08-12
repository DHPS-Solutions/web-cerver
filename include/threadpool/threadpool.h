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

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#include <threadpool/queue.h>

typedef void worker_thread_func(void *arg);

struct task_t {
    worker_thread_func *func;
    void *arg;
    int sleep_time;
};

struct condition_t {
    bool cond_predicate;
    pthread_mutex_t cond_lock;
    pthread_cond_t cond_variable;
};

struct threadpool_t {
    int max_threads;
    struct queue_t *task_queue;
    struct condition_t *cond_var;
    pthread_t *threads;
};

void threadpool_init(struct threadpool_t *threadpool, int max_threads, int queue_size);

void threadpool_free(struct threadpool_t *threadpool);

void threadpool_start(struct threadpool_t *threadpool);

bool submit_worker_task(struct threadpool_t *threadpool, worker_thread_func func, void *arg);

bool submit_worker_task_timeout(struct threadpool_t *threadpool, worker_thread_func func, void *arg, int timeout);

void threadpool_stop(struct threadpool_t *threadpool);

#endif