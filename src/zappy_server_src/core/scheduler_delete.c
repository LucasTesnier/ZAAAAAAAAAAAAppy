/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** scheduler_delete
*/

#include "scheduler/scheduler.h"
#include <stdlib.h>
#include <sys/queue.h>

void scheduler_delete(scheduler_t *scheduler)
{
    scheduler_event_t *event = NULL;
    scheduler_event_t *tmp = NULL;

    if (!scheduler)
        return;
    event = TAILQ_FIRST(&scheduler->events);
    while (event != NULL) {
        tmp = TAILQ_NEXT(event, events);
        free(event);
        event = tmp;
    }
    free(scheduler);
}

void scheduler_remove_event(scheduler_t *self, uuid_t uuid)
{
    scheduler_event_t *event = NULL;
    scheduler_event_t *tmp = NULL;

    if (self == NULL)
        return;
    event = TAILQ_FIRST(&self->events);
    while (event != NULL) {
        tmp = TAILQ_NEXT(event, events);
        if (uuid_compare(event->id, uuid) == 0) {
            TAILQ_REMOVE(&self->events, event, events);
            free(event);
        }
        event = tmp;
    }
}