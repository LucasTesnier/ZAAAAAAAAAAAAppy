/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** server_write_client
*/

/// \file server/net_utils/fd_sets_manage/server_write_client.c

#include "net_utils.h"

bool client_set_output_buffer(peer_t *tmp, char const *message)
{
    if (!tmp || !message)
        return (false);
    if (strlen(message) > MAX_MSG || tmp->pending_write >= 20)
        return (false);
    strcpy(tmp->output_buffer[tmp->pending_write], message);
    tmp->pending_write += 1;
    return (true);
}

/// \brief Remove a write from the stack
/// \param peer The user peer
static void pop_write(peer_t *peer)
{
    if (!peer)
        return;
    if (!peer->pending_write)
        return;
    for (int i = 0; i < peer->pending_write - 1; i++) {
        peer->output_buffer[i][0] = '\0';
        strcat(peer->output_buffer[i], peer->output_buffer[i + 1]);
    }
    peer->pending_write -= 1;
}

bool server_write_client(tcp_server_t *srv, peer_t *tmp)
{
    ssize_t write_size;
    size_t msg_size;

    if (!srv || !tmp)
        return (false);
    if ((msg_size = strlen(tmp->output_buffer[0])) <= 0) {
        ZAPPY_LOG("Internal Error: empty output buffer.\n");
        return (false);
    }
    if ((write_size = write(tmp->sock_fd, tmp->output_buffer[0],
    msg_size)) < 0) {
        ZAPPY_LOG("write\n");
        return (false);
    }
    if (write_size != (ssize_t)msg_size) {
        ZAPPY_LOG("Internal Error: could not write all the message.\n");
        return (false);
    }
    pop_write(tmp);
    return (true);
}
