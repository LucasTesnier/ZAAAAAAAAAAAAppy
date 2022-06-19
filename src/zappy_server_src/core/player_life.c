/*
** EPITECH PROJECT, 2022
** Project
** File description:
** player_life
*/

/// \file src/zappy_server_src/core/scheduler.c

#include "scheduler/scheduler.h"
#include "server.h"
#include "entity/player.h"
#include "command_hold.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void scheduler_update_life(scheduler_t *self, server_data_t *serv)
{
    time_t now = time(NULL);
    entity_t *entity = NULL;
    entity_t *entity2 = NULL;
    int tick = floor((now - self->clock) * self->freq);

    if (!self)
        return;
    if (tick < 0)
        return;
    entity = TAILQ_FIRST(&serv->entities->players);
    while (entity != NULL) {
        entity2 = TAILQ_NEXT(entity, entities);
        ((player_t *)entity->data)->inventory->food -= tick;
        if (((player_t *)entity->data)->inventory->food <= 0) {
            send_unexpected_dead(serv, (player_t *)entity->data);
            entity_wrapper_remove_entity(serv->entities, entity);
        }
        entity = entity2;
    }
    self->clock = time(NULL);
}