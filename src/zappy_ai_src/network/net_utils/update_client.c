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

/// \brief Utility function to detect if the server fd has been closed
/// \param server the remote server
/// \return true if the server fd has been closed, false otherwise
static bool check_for_disconnection(client_net_server_t *server)
{
    if (!(fcntl(server->sock_fd, F_GETFD) != -1 || errno != EBADF)) {
        server->connected = false;
        return (true);
    }
    return (false);
}

/// \brief Get the user input via getline
/// \param server the remote server
static void get_user_input(client_net_server_t *server)
{
    char *msg = NULL;
    ssize_t getline_size = 0;
    size_t msg_size = 0;

    if (!server->connected)
        return;
    getline_size = getline(&msg, &msg_size, stdin);
    if (getline_size == -1)
        return;
    set_output_buffer(server, msg);
    free(msg);
}

void update_client(client_net_server_t *server)
{
    if (check_for_disconnection(server))
        return;
    fill_fd_sets(server);
    if (select(FD_SETSIZE, &server->read_fds,
        &server->write_fds, NULL, NULL) == -1) {
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
    if (FD_ISSET(0, &server->read_fds))
        get_user_input(server);
}
