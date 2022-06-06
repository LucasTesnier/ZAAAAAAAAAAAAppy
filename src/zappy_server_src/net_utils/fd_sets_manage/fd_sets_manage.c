/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** fd_sets_manage
*/

/// \file server/net_utils/fd_sets_manage/fd_set_manage.c

#include "net_utils.h"
#include "fd_set_manage.h"

void server_fill_fd_sets(tcp_server_t *srv)
{
    peer_t *tmp = NULL;

    FD_ZERO(&srv->read_fds);
    FD_ZERO(&srv->write_fds);
    FD_ZERO(&srv->err_fds);
    CIRCLEQ_FOREACH(tmp, &srv->peers_head, peers) {
        if (!tmp->pending_read)
            FD_SET(tmp->sock_fd, &srv->read_fds);
        if (tmp->pending_write)
            FD_SET(tmp->sock_fd, &srv->write_fds);
    }
    FD_SET(srv->sock_fd, &srv->read_fds);
}

bool server_manage_fd_update(tcp_server_t *srv)
{
    peer_t *tmp = NULL;

    if (FD_ISSET(srv->sock_fd, &srv->read_fds))
        return server_accept_new_client(srv);
    CIRCLEQ_FOREACH(tmp, &srv->peers_head, peers) {
        if (FD_ISSET(tmp->sock_fd, &srv->read_fds))
            tmp->pending_read = server_read_client(srv, tmp);
        if (FD_ISSET(tmp->sock_fd, &srv->write_fds))
            server_write_client(srv, tmp);
        if (FD_ISSET(tmp->sock_fd, &srv->err_fds))
            server_close_client(srv, tmp);
    }
    return false;
}
