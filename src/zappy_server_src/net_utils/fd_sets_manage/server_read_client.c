/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** server_read_client
*/

/// \file server/net_utils/fd_sets_manage/server_read_client.c

#include "net_utils.h"
#include "fd_set_manage.h"

char *fetch_message(peer_t *peer)
{
    if (!peer)
        return NULL;
    if (!peer->pending_read)
        return NULL;
    return strdup(peer->input_buffer[0]);
}

void pop_message(peer_t *peer)
{
    if (!peer)
        return;
    if (!peer->pending_read)
        return;
    for (int i = 0; i < peer->pending_read - 1; i++) {
        peer->input_buffer[i][0] = '\0';
        strcat(peer->input_buffer[i], peer->input_buffer[i + 1]);
    }
    peer->pending_read -= 1;
}

bool server_read_client(tcp_server_t *srv, peer_t *tmp)
{
    ssize_t read_size;

    if (!tmp || !srv)
        return false;
    if (tmp->pending_read >= 10)
        return false;
    read_size = read(tmp->sock_fd,
    tmp->input_buffer[tmp->pending_read], MAX_MSG);
    if (read_size < 0)
        return false;
    if (read_size == 0) {
        ZAPPY_LOG("Client disconnected");
        server_close_client(srv, tmp);
        return false;
    }
    tmp->input_buffer[tmp->pending_read][read_size] = '\0';
    tmp->pending_read += 1;
    return true;
}
