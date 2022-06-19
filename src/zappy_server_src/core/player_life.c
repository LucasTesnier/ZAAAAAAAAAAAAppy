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
#include "rcodes.h"
#include <sys/queue.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

static void remove_a_player(server_data_t *serv, entity_t *entity)
{
    player_list_t *user = find_player_list_by_uuid(serv,
    (player_t *)entity->data);

    send_unexpected_dead(serv, (player_t *)entity->data);
    user->disconnected = TO_LOGOUT;
    if (user->scheduled_action) {
        free(user->scheduled_action);
        user->scheduled_action = NULL;
        pop_message(user->player_peer);
    }
    if (scheduler_has_event(serv->scheduler,
    ((player_t *)entity->data)->uuid)) {
        scheduler_remove_event(serv->scheduler,
        ((player_t *)entity->data)->uuid);
    }
    TAILQ_REMOVE(&serv->entities->players, entity, entities);
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
            remove_a_player(serv, entity);
        }
        entity = entity2;
    }
    self->clock = time(NULL);
}