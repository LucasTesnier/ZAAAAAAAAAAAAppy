/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** select
*/

/// \file server/net_utils/select.c

#include "net_utils.h"

int server_wait(tcp_server_t *srv, struct timeval time)
{
    if (select(FD_SETSIZE,
        &srv->read_fds,
        &srv->write_fds,
        &srv->err_fds,
        &time) == -1) {
        ZAPPY_LOG("select");
        return (-1);
    }
    return (0);
}
