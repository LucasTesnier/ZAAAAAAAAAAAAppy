/*
** EPITECH PROJECT, 2022
** Project
** File description:
** join_command
*/

/// \file src/zappy_server_src/core/commands/join_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/entity.h"
#include "entity/player.h"
#include <stdlib.h>

/// \brief Create the response for the join function
/// \param serv The server informations
/// \param team The team informations
/// \return char* The newly created response
static char *join_resp(server_data_t *serv, team_t *team)
{
    char *res = malloc(sizeof(char) * 20);

    if (res == NULL)
        return NULL;
    res[0] = '\0';
    sprintf(res, "%i,%i,%i", serv->arguments->width, serv->arguments->height,
    team->max_members - team->current_members);
    return res;
}

/// \brief Create a new player entity
/// \param arg The function argument
/// \param player_entity The entity informations
/// \param serv The server informations
/// \return true When operation succeed
/// \return false When operation failed
static bool command_join_create_player_data(char *arg,
entity_t **player_entity, server_data_t *serv)
{
    player_t *player_data = NULL;

    *player_entity = create_entity(ENTITY_PLAYER_TYPE, (position_t){
        .x = rand() % serv->map->height,
        .y = rand() % serv->map->width
    });
    if (!player_entity)
        return false;
    if (!(player_data = create_player(arg)))
        return false;
    entity_set_data(*player_entity, player_data);
    return true;
}

bool command_join(char *arg, player_list_t *player, server_data_t *serv)
{
    team_t *tmp = NULL;
    entity_t *player_entity = NULL;
    char *res = NULL;

    if (!player->is_auth)
        return print_retcode(401, NULL, player->player_peer, false);
    if (!(tmp = get_team_by_name(arg, &serv->teams)))
        return print_retcode(312, arg, player->player_peer, false);
    if (tmp->current_members >= tmp->max_members)
        return print_retcode(313, arg, player->player_peer, false);
    tmp->current_members++;
    if (!command_join_create_player_data(arg, &player_entity, serv))
        return print_retcode(500, arg, player->player_peer, false);
    player->player_data = player_entity;
    entity_wrapper_add_player(serv->entities, player_entity);
    pop_message(player->player_peer);
    print_retcode(211, (res = join_resp(serv, tmp)),
    player->player_peer, true);
    free(res);
    return true;
}