/*
** EPITECH PROJECT, 2022
** Project
** File description:
** game_status
*/

/// \file src/zappy_server_src/core/commands/game_status.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"

bool send_game_paused(server_data_t *serv)
{
    peer_t *peer = NULL;

    for (size_t i = 0; i < serv->active_player_n; i++) {
        if (serv->active_players[i]->type == GUI) {
            peer = serv->active_players[i]->player_peer;
            break;
        }
    }
    if (peer == NULL) {
        dprintf(2, "No GUI client found.\n");
        return false;
    }
    return print_retcode(702, "status{game:paused}", peer, true);
}

bool send_game_started(server_data_t *serv)
{
    peer_t *peer = NULL;

    for (size_t i = 0; i < serv->active_player_n; i++) {
        if (serv->active_players[i]->type == GUI) {
            peer = serv->active_players[i]->player_peer;
            break;
        }
    }
    if (peer == NULL) {
        dprintf(2, "No GUI client found.\n");
        return false;
    }
    return print_retcode(702, "status{game:start}", peer, true);
}