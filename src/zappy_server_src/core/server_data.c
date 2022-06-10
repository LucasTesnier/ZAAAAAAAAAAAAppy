/*
** EPITECH PROJECT, 2022
** Project
** File description:
** server_data
*/

/// \file src/zappy_server_src/core/server_data.c

#include "server.h"
#include "argument_handling.h"
#include <stdlib.h>

server_data_t *init_server_data(int ac, char **av)
{
    server_data_t *server_data = malloc(sizeof(server_data_t) * 1);
    int size_queue = 0;

    if (server_data == NULL)
        return NULL;
    if (!(server_data->arguments = argument_handling(ac, av)))
        return NULL;
    server_data->active_players = malloc(sizeof(player_list_t *) * 1);
    if (server_data->active_players == NULL)
        return NULL;
    server_data->active_players[0] = NULL;
    server_data->active_player_n = 0;
    for (int i = 0; server_data->arguments->team_list[i]; i++)
        size_queue += server_data->arguments->client_nb;
    server_data->server = create_new_server(server_data->arguments->port,
    size_queue);
    if (server_data->server == NULL)
        return NULL;
    server_data->server->state = true;
    return server_data;
}

bool server_add_player(server_data_t *server_data)
{
    player_list_t *new_player = malloc(sizeof(player_list_t) * 1);

    if (new_player == NULL)
        return FAILED;
    new_player->is_auth = false;
    new_player->disconnected = CONNECTED;
    new_player->type = UNKNOWN;
    new_player->player_peer =
    fetch_last_added_peer(server_data->server->network_server);
    server_data->active_players = realloc(server_data->active_players,
    sizeof(player_list_t *) * (server_data->active_player_n + 2));
    if (server_data->active_players == NULL)
        return FAILED;
    server_data->active_players[server_data->active_player_n] = new_player;
    server_data->active_player_n += 1;
    return SUCCESS;
}

void server_remove_player(server_data_t *server_data,
player_list_t *player_info)
{
    if (player_info->player_peer->pending_write == true)
        return;
    CIRCLEQ_REMOVE(&server_data->server->network_server->peers_head,
    player_info->player_peer, peers);
    close(player_info->player_peer->sock_fd);
    if (player_info->player_peer != NULL) {
        free(player_info->player_peer);
        player_info->player_peer = NULL;
    }
    player_info->disconnected = LOGOUT;
}

void remove_disconnected_player(server_data_t *server_data,
player_state_t comp)
{
    for (size_t i = 0; i < server_data->active_player_n; i++) {
        if (server_data->active_players[i]->disconnected == comp)
            server_remove_player(server_data, server_data->active_players[i]);
    }
}

void destroy_server_data(server_data_t *server_data)
{
    if (server_data == NULL)
        return;
    remove_disconnected_player(server_data, CONNECTED);
    for (size_t i = 0; i < server_data->active_player_n; i++)
        free(server_data->active_players[i]);
    free(server_data->active_players);
    destroy_zappy_server(server_data->server);
    argument_destroy(server_data->arguments);
    free(server_data);
}
