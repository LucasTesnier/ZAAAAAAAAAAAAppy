/*
** EPITECH PROJECT, 2022
** Project
** File description:
** unexpected_send
*/

/// \file src/zappy_server_src/core/commands/unexpected_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"

void send_unexpected_eject(enum player_orientation_e direction,
server_data_t *serv, player_t *tmp)
{
    char *dir = NULL;

    if (direction == NORTH)
        dir = "1";
    if (direction == EAST)
        dir = "2";
    if (direction == SOUTH)
        dir = "3";
    if (direction == WEST)
        dir = "4";
    for (size_t i = 0; i < serv->active_player_n; i++) {
        if (!uuid_compare(((player_t *)
        serv->active_players[i]->player_data->data)->uuid, tmp->uuid)) {
            print_retcode(602, dir, serv->active_players[i]->player_peer,
            true);
            return;
        }
    }
}