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

/// \brief Remove a plyer from his team
/// \param player The player informations
/// \param serv The server informations
/// \return true When operation succeed
/// \return false When operation failed
static bool remove_player_from_team(player_t *player, server_data_t *serv)
{
    team_t *team = get_team_by_name(player->team, &serv->teams);
    team_t *tmp = NULL;
    team_t *win = NULL;
    int end = 0;

    if (!team)
        return false;
    remove_user_from_team(team, player->uuid);
    if (team->current_members <= 0 && team->max_members <= 0)
        send_team_lose(serv, player->team);
    else
        return true;
    TAILQ_FOREACH(tmp, &serv->teams, teams)
        if (tmp->current_members > 0 || tmp->max_members > 0) {
            win = tmp;
            end++;
        }
    if (end == 1)
        send_team_win(serv, win->name);
    return false;
}

/// \brief Remove a player from the game
/// \param serv The server informations
/// \param entity The entity to delete
static void remove_a_player(server_data_t *serv, entity_t *entity)
{
    player_list_t *user = find_player_list_by_uuid(serv,
    (player_t *)entity->data);
    bool temp = false;

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
    temp = remove_player_from_team((player_t *)entity->data, serv);
    TAILQ_REMOVE(&serv->entities->players, entity, entities);
    if (temp)
        send_entities_list_info(serv);
}

/// \brief Update the life of all the players
/// \param self The scheduler object
/// \param serv The server informations
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
