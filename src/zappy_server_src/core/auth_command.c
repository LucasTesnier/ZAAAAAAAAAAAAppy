/*
** EPITECH PROJECT, 2022
** Project
** File description:
** auth_command
*/

/// \file src/zappy_server_src/core/auth_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"

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

bool command_join(char *arg, player_list_t *player, server_data_t *serv)
{
    team_t *tmp = NULL;

    if (!player->is_auth)
        return print_retcode(401, NULL, player->player_peer, false);
    if (!(tmp = get_team_by_name(arg, &serv->teams)))
        return print_retcode(312, arg, player->player_peer, false);
    if (tmp->current_members >= tmp->max_members)
        return print_retcode(313, arg, player->player_peer, false);
    tmp->current_members++;
    /// Create a new user and put it in the team
    /// return print_retcode(301, NULL, player->player_peer, false);
    return print_retcode(211, arg, player->player_peer, true);
}