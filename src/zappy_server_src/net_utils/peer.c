/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** peer
*/

/// \file server/net_utils/peer.c

#include "net_utils.h"

peer_t *new_peer(int fd, struct sockaddr_in addr)
{
    peer_t *new_peer = malloc(sizeof(peer_t));

    if (new_peer == NULL)
        ZAPPY_LOG("malloc");
    bzero(new_peer, sizeof(peer_t));
    new_peer->sock_fd = fd;
    new_peer->peer_addr = addr;
    new_peer->connected = true;
    new_peer->pending_read = 0;
    new_peer->pending_write = 0;
    return (new_peer);
}
