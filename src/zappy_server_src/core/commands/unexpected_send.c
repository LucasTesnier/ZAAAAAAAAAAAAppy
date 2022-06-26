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

void send_unexpected_eject(int direction, server_data_t *serv, player_t *tmp,
position_t pos)
{
    char *dir = malloc(sizeof(char) * 2);

    if (dir == NULL)
        return;
    dir[0] = '\0';
    sprintf(dir, "%i", direction);
    for (size_t i = 0; i < serv->active_player_n; i++) {
        if (serv->active_players[i]->disconnected == CONNECTED &&
        serv->active_players[i]->type == AI && !uuid_compare(((player_t *)
        serv->active_players[i]->player_data->data)->uuid, tmp->uuid) &&
        serv->active_players[i]->player_data->position.x == pos.x &&
        serv->active_players[i]->player_data->position.y == pos.y) {
            print_retcode(602, dir, serv->active_players[i]->player_peer,
            true);
            free(dir);
            return;
        }
    }
    free(dir);
}

void send_unexpected_dead(server_data_t *serv, player_t *tmp)
{
    for (size_t i = 0; i < serv->active_player_n; i++) {
        if (serv->active_players[i]->disconnected == CONNECTED &&
        serv->active_players[i]->type == AI && !uuid_compare(((player_t *)
        serv->active_players[i]->player_data->data)->uuid, tmp->uuid)) {
            print_retcode(601, NULL, serv->active_players[i]->player_peer,
            true);
            return;
        }
    }
}

player_list_t *find_player_list_by_uuid(server_data_t *serv, player_t *tmp)
{
    for (size_t i = 0; i < serv->active_player_n; i++) {
        if (serv->active_players[i]->disconnected == CONNECTED &&
        serv->active_players[i]->type == AI && !uuid_compare(((player_t *)
        serv->active_players[i]->player_data->data)->uuid, tmp->uuid)) {
            return serv->active_players[i];
        }
    }
    return NULL;
}
