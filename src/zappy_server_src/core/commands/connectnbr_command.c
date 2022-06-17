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

bool command_connectnbr(char *arg, player_list_t *player, server_data_t *serv)
{
    (void) serv;
    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    pop_message(player->player_peer);
    return print_retcode(216, "10", player->player_peer, true);
}
