/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** server_accept_new_client
*/

/// \file server/net_utils/fd_sets_manage/server_accept_new_client.c

#include "net_utils.h"

/// \brief accepts a new client and returns the new peer
/// \param srv the server
/// \return the new peer
static peer_t *accept_client(tcp_server_t *srv)
{
    peer_t *new_client = NULL;
    int client_fd = 0;
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

    client_fd = accept(srv->sock_fd,
        (struct sockaddr *)&client_addr,
        &client_addr_size);
    if (client_fd < 0) {
        ZAPPY_LOG("accept");
        return (NULL);
    }
    new_client = new_peer(client_fd, client_addr);
    if (new_client == NULL) {
        ZAPPY_LOG("peer_create");
        return (NULL);
    }
    FD_SET(client_fd, &srv->read_fds);
    return (new_client);
}

bool server_accept_new_client(tcp_server_t *srv)
{
    peer_t *new = accept_client(srv);

    if (new == NULL) {
        ZAPPY_LOG("Internal Error: could not accept new client.\n");
        return (false);
    }
    CIRCLEQ_INSERT_HEAD(&srv->peers_head, new, peers);
    return (true);
}
