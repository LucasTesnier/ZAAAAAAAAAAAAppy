/*
** EPITECH PROJECT, 2022
** Project
** File description:
** connectnbr_command
*/

/// \file src/zappy_server_src/core/commands/connectnbr_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"

/// \brief Get the connectnbr response
/// \param player The player informations
/// \param serv The server informations
/// \return char* The newly created response
static char *get_connectnbr_resp(player_t *player, server_data_t *serv)
{
    team_t *team = get_team_by_name(player->team, &serv->teams);
    char *res = malloc(sizeof(char) * 3);

    if (team == NULL || res == NULL)
        return NULL;
    res[0] = '\0';
    sprintf(res, "%i", team->max_members - team->current_members);
    return res;
}

bool command_connectnbr(char *arg, player_list_t *player,
server_data_t *serv __attribute__((unused)))
{
    entity_t *player_entity = NULL;
    player_t *player_data = NULL;
    char *res = NULL;

    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    player_entity = (entity_t *)player->player_data;
    player_data = (player_t *)player_entity->data;
    pop_message(player->player_peer);
    print_retcode(217, (res = get_connectnbr_resp(player_data, serv)),
    player->player_peer, true);
    free(res);
    return true;
}
