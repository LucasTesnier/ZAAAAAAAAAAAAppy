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