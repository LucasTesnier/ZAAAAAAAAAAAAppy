/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** client_utils
*/

/// \file src/zappy_ai_src/network/net_utils/client_utils.h

#include "client_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// \brief bind the srv socket to a file descriptor
/// \param server the server
/// \param port the port
/// \return true if the bind is successful, false otherwise
static bool connect_socket(client_net_server_t *srv, long port)
{
    srv->sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (srv->sock_fd < 0) {
        TEAMS_LOG("socket");
        return false;
    }
    srv->srv_addr.sin_family = AF_INET;
    srv->srv_addr.sin_port = htons(port);
    if (connect(srv->sock_fd,
        (struct sockaddr *)&srv->srv_addr,
        sizeof(srv->srv_addr)) < 0) {
        TEAMS_LOG("connect\n");
        return false;
    }
    return true;
}

client_net_server_t *create_net_server(const char *ip, long port)
{
    client_net_server_t *new_server;
    int pton_return = 0;

    if (!(new_server = malloc(sizeof(client_net_server_t))))
        return NULL;
    pton_return = inet_pton(AF_INET, ip, &new_server->srv_addr.sin_addr);
    if (pton_return <= 0) {
        TEAMS_LOG("inet_pton: Invalid ip address provided\n");
        return NULL;
    }
    if (!connect_socket(new_server, port)) {
        free(new_server);
        return NULL;
    }
    FD_ZERO(&new_server->read_fds);
    FD_ZERO(&new_server->write_fds);
    FD_ZERO(&new_server->err_fds);
    FD_SET(new_server->sock_fd, &new_server->read_fds);
    FD_SET(new_server->sock_fd, &new_server->write_fds);
    return new_server;
}
