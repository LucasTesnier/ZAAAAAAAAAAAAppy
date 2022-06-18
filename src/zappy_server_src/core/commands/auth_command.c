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
        pop_message(player->player_peer);
        return send_start_info(serv);
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


