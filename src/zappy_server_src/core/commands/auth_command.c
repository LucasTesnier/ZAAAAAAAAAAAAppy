/*
** EPITECH PROJECT, 2022
** Project
** File description:
** auth_command
*/

/// \file src/zappy_server_src/core/commands/auth_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/entity.h"
#include "entity/player.h"
#include <stdlib.h>

bool command_logout(char *arg, player_list_t *player, server_data_t *serv)
{
    char *type = NULL;

    player->disconnected = TO_LOGOUT;
    if (player->type == AI)
        type = "AI";
    if (player->type == GUI)
        type = "GUI";
    if (player->type == UNKNOWN)
        type = "UNKNOWN";
    (void) arg;
    (void) serv;
    pop_message(player->player_peer);
    return print_retcode(202, type, player->player_peer, true);
}

bool command_login(char *arg, player_list_t *player, server_data_t *serv)
{
    char *type = NULL;

    if (!strncmp(arg, "GUI", 3)) {
        player->type = GUI;
        type = "GUI";
    }
    if (!strncmp(arg, "AI", 2)) {
        player->type = AI;
        type = "AI";
    }
    if (player->type == UNKNOWN)
        return print_retcode(402, arg, player->player_peer, false);
    player->is_auth = true;
    (void) serv;
    pop_message(player->player_peer);
    return print_retcode(201, type, player->player_peer, true);
}

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
    return print_retcode(211, arg, player->player_peer, true);
}
