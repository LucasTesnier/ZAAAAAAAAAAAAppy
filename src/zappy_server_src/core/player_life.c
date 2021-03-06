/*
** EPITECH PROJECT, 2022
** Project
** File description:
** player_life
*/

/// \file src/zappy_server_src/core/include/player_life.c

#include "scheduler/scheduler.h"
#include "server.h"
#include "entity/player.h"
#include "command_hold.h"
#include "rcodes.h"
#include "entity/tile.h"
#include <sys/queue.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

bool remove_player_from_team(player_t *player, server_data_t *serv)
{
    team_t *team = get_team_by_name(player->team, &serv->teams);

    if (!team)
        return false;
    remove_user_from_team(team, player->uuid);
    defeat_detection(serv, player->team);
    return true;
}

/// \brief Remove the died player from the scheduling
/// \param serv The server informations
/// \param entity The died entity
/// \param user The user information
static void remove_player_scheduling(server_data_t *serv,
entity_t *entity, player_list_t *user)
{
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
}

/// \brief Drop the entity inventory on the ground
/// \param serv The server information
/// \param entity The died entity
static void drop_player_inventory(server_data_t *serv, entity_t *entity)
{
    tile_t *tile = (tile_t *)get_tile(serv->map, entity->position.x,
    entity->position.y)->data;
    container_t *inventory = ((player_t *)entity->data)->inventory;

    if (tile == NULL)
        return;
    tile->inventory->linemate += inventory->linemate;
    tile->inventory->deraumere += inventory->deraumere;
    tile->inventory->sibur += inventory->sibur;
    tile->inventory->mendiane += inventory->mendiane;
    tile->inventory->phiras += inventory->phiras;
    tile->inventory->thystame += inventory->thystame;
}

/// \brief Remove a player from the game
/// \param serv The server informations
/// \param entity The entity to delete
static void remove_a_player(server_data_t *serv, entity_t *entity)
{
    player_list_t *user = find_player_list_by_uuid(serv,
    (player_t *)entity->data);

    send_unexpected_dead(serv, (player_t *)entity->data);
    user->disconnected = TO_LOGOUT;
    remove_player_scheduling(serv, entity, user);
    entity_diff_remove_entity(serv->modified_entities, entity);
    drop_player_inventory(serv, entity);
    remove_player_from_team((player_t *)entity->data, serv);
    TAILQ_REMOVE(&serv->entities->players, entity, entities);
    send_entities_list_info(serv);
}

/// \brief Update the life of all the players
/// \param self The scheduler object
/// \param serv The server information's
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
            ((player_t *) entity->data)->status = false;
            entity_diff_add_entity(serv->modified_entities, entity);
            remove_a_player(serv, entity);
        }
        entity = entity2;
    }
    self->clock = time(NULL);
}
