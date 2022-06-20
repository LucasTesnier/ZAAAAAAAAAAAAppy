/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** scheduler
*/

/// \file src/zappy_server_src/core/scheduler.c

#include "scheduler/scheduler.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

scheduler_t *create_scheduler(double freq)
{
    scheduler_t *scheduler = malloc(sizeof(scheduler_t));

    if (scheduler == NULL)
        return (NULL);
    scheduler->freq = freq;
    scheduler->clock = time(NULL);
    scheduler->ressource = time(NULL);
    TAILQ_INIT(&scheduler->events);
    return scheduler;
}

bool scheduler_has_event(scheduler_t *self, uuid_t uuid)
{
    scheduler_event_t *tmp = NULL;

    if (self == NULL)
        return false;
    TAILQ_FOREACH(tmp, &self->events, events)
        if (uuid_compare(tmp->id, uuid) == 0)
            return true;
    return false;
}

bool scheduler_schedule_event(scheduler_t *self, uuid_t uuid, int ticks)
{
    scheduler_event_t *new_event = NULL;

    if (!self)
        return false;
    if (scheduler_has_event(self, uuid))
        return false;
    if (!(new_event = malloc(sizeof(scheduler_event_t))))
        return false;
    uuid_copy(new_event->id, uuid);
    new_event->ticks = ticks;
    new_event->clock = time(NULL);
    TAILQ_INSERT_TAIL(&self->events, new_event, events);
    return true;
}

void scheduler_update(scheduler_t *self)
{
    scheduler_event_t *tmp = NULL;
    scheduler_event_t *tmp2 = NULL;
    time_t now = time(NULL);

    if (!self)
        return;
    tmp = TAILQ_FIRST(&self->events);
    while (tmp != NULL) {
        tmp2 = TAILQ_NEXT(tmp, events);
        if (floor((now - tmp->clock) * self->freq) > 0) {
            tmp->ticks -= floor((now - tmp->clock) * self->freq);
            tmp->clock = now;
        }
        if (tmp->ticks <= 0) {
            TAILQ_REMOVE(&self->events, tmp, events);
            free(tmp);
        }
        now = time(NULL);
        tmp = tmp2;
    }
}

struct timeval scheduler_get_smallest_timeout(scheduler_t *self)
{
    scheduler_event_t *tmp = NULL;
    time_t smallest = 10000000000;
    time_t tmp_time = 0;

    if (!self)
        return (struct timeval){.tv_sec = -1, .tv_usec = 0};
    TAILQ_FOREACH(tmp, &self->events, events) {
        tmp_time = tmp->ticks * (1 / self->freq);
        if (tmp_time < smallest)
            smallest = tmp_time;
    }
    tmp_time = time(NULL);
    if (smallest == 10000000000)
        return (struct timeval){.tv_sec =
        (20 - floor((tmp_time - self->ressource) * self->freq)) *
        (1 / self->freq), .tv_usec = 0};
    return (struct timeval){.tv_sec = smallest, .tv_usec = 0};
}
