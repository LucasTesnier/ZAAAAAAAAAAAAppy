/*
** EPITECH PROJECT, 2022
** Project
** File description:
** server_run
*/

/// \file src/zappy_server_src/core/server_run.c

#include "server.h"
#include "fd_set_manage.h"
#include "command_hold.h"
#include <signal.h>

volatile bool *server_state = NULL;

/// \brief Catch the sigint signal
/// \param var Useless data
void sigint_handler(int var __attribute__((unused)))
{
    *server_state = false;
}

int server_run(int ac, char **av)
{

    server_data_t *server_data = init_server_data(ac, av);

    if (server_data == NULL)
        return FAILED;
    signal(SIGINT, sigint_handler);
    server_loop(server_data);
    destroy_server_data(server_data);
    return SUCCESS;
}

/// \brief Get the player list by peer object
/// \param server_data Server data info
/// \param peer Peer to match
/// \return player_list_t* player list matched, NULL otherwise
static player_list_t *get_player_list_by_peer(server_data_t *server_data,
peer_t *peer)
{
    for (size_t i = 0; i < server_data->active_player_n; i++)
        if (server_data->active_players[i]->player_peer == peer)
            return server_data->active_players[i];
    return NULL;
}

/// \brief Cross all the peer_t list and get pending read
/// \param server_data Server data
static void process_command_inspection(server_data_t *server_data)
{
    tcp_server_t *srv = server_data->server->network_server;
    peer_t *tmp = NULL;

    CIRCLEQ_FOREACH(tmp, &srv->peers_head, peers) {
        if (tmp->pending_read) {
            compute_command(fetch_message(tmp),
            get_player_list_by_peer(server_data, tmp), server_data);
        }
    }
}

void server_loop(server_data_t *server_data)
{
    tcp_server_t *network_server = server_data->server->network_server;

    server_fill_fd_sets(network_server);
    server_state = &server_data->server->state;
    while (server_data->server->state) {
        if (server_wait(network_server) == -1)
            break;
        if (server_manage_fd_update(network_server))
            server_add_player(server_data);
        process_command_inspection(server_data);
        remove_disconnected_player(server_data, TO_LOGOUT);
        server_fill_fd_sets(network_server);
    }
}