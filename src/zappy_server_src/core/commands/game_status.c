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
    return print_retcode(703, "status{game:start}", peer, true);
}

bool send_team_win(server_data_t *serv, char *team_name)
{
    peer_t *peer = NULL;
    char *temp = malloc(sizeof(char) * (14 + strlen(team_name)));

    if (temp == NULL)
        return false;
    for (size_t i = 0; i < serv->active_player_n; i++)
        if (serv->active_players[i]->type == GUI) {
            peer = serv->active_players[i]->player_peer;
            break;
        }
    if (peer == NULL) {
        free(temp);
        dprintf(2, "No GUI client found.\n");
        return false;
    }
    temp[0] = '\0';
    sprintf(temp, "status{win:%s}", team_name);
    print_retcode(705, temp, peer, true);
    free(temp);
    return true;
}