/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** scheduler
*/

#include "scheduler/scheduler.h"
#include <stdlib.h>

scheduler_t *create_scheduler(double freq)
{
    scheduler_t *scheduler = malloc(sizeof(scheduler_t));

    if (scheduler == NULL)
        return (NULL);
    scheduler->freq = freq;
    scheduler->clock = time(NULL);
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
    TAILQ_INSERT_TAIL(&self->events, new_event, events);
    return true;
}

void scheduler_update(scheduler_t *self)
{
    scheduler_event_t *tmp = NULL;
    time_t now = time(NULL);

    if (!self)
        return;
    TAILQ_FOREACH(tmp, &self->events, events) {
        tmp->ticks -= (now - self->clock) * self->freq;
        if (tmp->ticks <= 0) {
            TAILQ_REMOVE(&self->events, tmp, events);
            free(tmp);
        }
        now = time(NULL);
    }
}
