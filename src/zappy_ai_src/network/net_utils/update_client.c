/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** update_server
*/

/// \file src/zappy_ai_src/network/net_utils/update_client.c

#include "client_utils.h"
#include "internals.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

bool check_for_disconnection(client_net_server_t *server)
{
    if (!(fcntl(server->sock_fd, F_GETFD) != -1 || errno != EBADF)) {
        server->connected = false;
        return (true);
    }
    return (false);
}

void update_client(client_net_server_t *server)
{
    struct timeval time = {0, 1};

    if (check_for_disconnection(server))
        return;
    fill_fd_sets(server);
    if (select(FD_SETSIZE, &server->read_fds,
        &server->write_fds, NULL, &time) == -1) {
        ZAPPY_LOG("Internal Server Error: select\n");
        return;
    }
    if (FD_ISSET(server->sock_fd, &server->read_fds))
        server->pending_read = true;
    if (FD_ISSET(server->sock_fd, &server->write_fds)) {
        send_message(server);
        update_client(server);
    }
    if (FD_ISSET(server->sock_fd, &server->err_fds)) {
        ZAPPY_LOG("Internal Server Error: Failed to connect\n");
        server->connected = false;
    }
}
