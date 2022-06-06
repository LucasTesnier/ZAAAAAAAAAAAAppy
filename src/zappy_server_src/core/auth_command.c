/*
** EPITECH PROJECT, 2022
** Project
** File description:
** auth_command
*/

/// \file src/zappy_server_src/core/auth_command.c

#include "command_hold.h"

bool command_logout(char *arg, player_list_t *player, server_data_t *serv)
{
    player->disconnected = TO_LOGOUT;
    printf("YEEEEP\n");
    (void) arg;
    (void) serv;
    return true;
}

bool command_login(char *arg, player_list_t *player, server_data_t *serv)
{
    if (!strncmp(arg, "GUI", 3))
        player->type = GUI;
    if (!strncmp(arg, "AI", 2))
        player->type = AI;
    if (player->type == UNKNOWN)
        return false;
    player->is_auth = true;
    (void) serv;
    return true;
}