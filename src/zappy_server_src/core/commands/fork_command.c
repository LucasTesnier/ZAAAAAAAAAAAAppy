/*
** EPITECH PROJECT, 2022
** Project
** File description:
** fork_command
*/

/// \file src/zappy_server_src/core/commands/fork_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"
#include "entity/eggs.h"

bool command_fork(char *arg, player_list_t *player, server_data_t *serv)
{
    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    if (!scheduler_schedule_event(serv->scheduler,
    ((player_t *)player->player_data->data)->uuid, 42))
        return false;
    player->scheduled_action = find_ai_command_end("/fork", NULL);
    if (player->scheduled_action == NULL)
        return false;
    return true;
}

/// \brief Handle the verification process for the fork hability
/// \param serv The server informations
/// \param player The player informations
/// \return true When operation succeed
/// \return false When operation failed
static bool fork_verification(server_data_t *serv, player_t *player)
{
    team_t *team = get_team_by_name(player->team, &serv->teams);
    entity_t *tmp = NULL;
    int eggs_number = 0;

    if (team == NULL)
        return false;
    TAILQ_FOREACH(tmp, &serv->entities->eggs, entities)
        if (!strcmp(player->team, ((egg_t *)tmp->data)->team_name))
            eggs_number++;
    dprintf(2, "Fork ask for the team %s, which allow to max %i player.\
    Have %i player and %i eggs in the game\n", player->team, team->max_members,
    team->current_members, eggs_number);
    if (team->max_members <= team->current_members + eggs_number)
        return false;
    return true;
}

bool command_fork_end(char *arg, player_list_t *player,
server_data_t *serv)
{
    entity_t *player_entity = NULL;
    player_t *player_data = NULL;

    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    player_entity = (entity_t *)player->player_data;
    player_data = (player_t *)player_entity->data;
    if (!fork_verification(serv, player_data)) {
        pop_message(player->player_peer);
        return print_retcode(317, NULL, player->player_peer, false);
    }
    entity_wrapper_create_egg(serv->entities,
    player_entity->position, player_data->team);
    send_entities_list_info(serv);
    pop_message(player->player_peer);
    return print_retcode(218, NULL, player->player_peer, true);
}