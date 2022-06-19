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

static void remove_a_player(server_data_t *serv, entity_t *entity)
{
    send_unexpected_dead(serv, (player_t *)entity->data);
    if (scheduler_has_event(serv->scheduler,
    ((player_t *)entity->data)->uuid)) {
        scheduler_remove_event(serv->scheduler,
        ((player_t *)entity->data)->uuid);
    }
    entity_wrapper_remove_entity(serv->entities, entity);
}

void scheduler_update_life(scheduler_t *self, server_data_t *serv)
{
    time_t now = time(NULL);
    entity_t *entity = NULL;
    entity_t *entity2 = NULL;
    int tick = floor((now - self->clock) * self->freq);

    if (!self || tick < 0)
        return;
    entity = TAILQ_FIRST(&serv->entities->players);
    while (entity != NULL) {
        entity2 = TAILQ_NEXT(entity, entities);
        ((player_t *)entity->data)->inventory->food -= tick;
        if (((player_t *)entity->data)->inventory->food <= 0) {
            // ((player_t *)entity->data)->inventory->food = 100000;
            // remove_a_player(serv, entity);
        }
        entity = entity2;
    }
    self->clock = time(NULL);
}