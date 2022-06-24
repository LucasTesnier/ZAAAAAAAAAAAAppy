/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** server_close_client
*/

/// \file server/net_utils/fd_sets_manage/server_close_client.c

#include "net_utils.h"

bool server_close_client(tcp_server_t *srv, peer_t *tmp)
{
    if (!tmp || !srv)
        return (false);
    tmp->connected = false;
    return (true);
}
