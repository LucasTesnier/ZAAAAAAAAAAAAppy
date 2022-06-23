/*
** EPITECH PROJECT, 2022
** Project
** File description:
** end_game_gestion
*/

/// \file src/zappy_server_src/core/end_game_gestion.c

#include "server.h"
#include "command_hold.h"
#include "team.h"
#include "entity/eggs.h"

/// \brief Cross all the player of a team and
/// tell if the given player is inside
/// \param list The list of the player inside the team
/// \param player The player information to analyze
/// \return true If the player is on the team
/// \return false If the player are not in the team
static bool is_a_player_from_the_team(uuid_t *list, player_t *player)
{
    for (int i = 0; i < 6; i++) {
        if (!uuid_compare(list[i], player->uuid))
            return true;
    }
    return false;
}

void victory_detection(server_data_t *serv, char *team_name)
{
    team_t *team = get_team_by_name(team_name, &serv->teams);
    entity_t *entity = NULL;
    player_t *player = NULL;

    if (team == NULL)
        return;
    if (team->current_members != 6)
        return;
    TAILQ_FOREACH(entity, &serv->entities->players, entities) {
        player = (player_t *)entity->data;
        if (!is_a_player_from_the_team(team->members_uuid, player))
            continue;
        if (player->level != 8)
            return;
    }
    send_team_win(serv, team_name);
}

void defeat_detection(server_data_t *serv, char *team_name)
{
    team_t *team = get_team_by_name(team_name, &serv->teams);
    int eggs_number = 0;
    entity_t *tmp = NULL;

    if (team == NULL)
        return;
    if (team->current_members != 0 || team->max_members != 0)
        return;
    TAILQ_FOREACH(tmp, &serv->entities->eggs, entities)
        if (!strcmp(team_name, ((egg_t *)tmp->data)->team_name))
            eggs_number++;
    if (eggs_number != 0)
        return;
    send_team_lose(serv, team_name);
}