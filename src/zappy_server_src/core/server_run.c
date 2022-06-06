/*
** EPITECH PROJECT, 2022
** Project
** File description:
** server_run
*/

/// \file src/zappy_server_src/core/server_run.c

#include "server.h"
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
    server_data_t *server_data = init_server_data(atoi(av[1]));
    /// TO REFACTO WITH ARGS GESTION

    (void) ac;
    if (server_data == NULL)
        return FAILED;
    signal(SIGINT, sigint_handler);
    server_loop(server_data);
    destroy_server_data(server_data);
    return SUCCESS;
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
        //process_command_inspection(server_data);
        remove_disconnected_player(server_data, TO_LOGOUT);
        server_fill_fd_sets(network_server);
    }
}