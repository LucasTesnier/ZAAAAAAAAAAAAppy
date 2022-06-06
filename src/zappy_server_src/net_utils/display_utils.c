/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** display_utils
*/

/// \file server/net_utils/display_utils.c

#include "net_utils.h"

void display_clients(struct peers_head *peers_head)
{
    peer_t *tmp = NULL;

    printf("\n\nList of connected clients:\n/*----------------------*/\n");
    CIRCLEQ_FOREACH(tmp, peers_head, peers)
        printf(" - %s:%hu on socket: %d\n",
            inet_ntoa(tmp->peer_addr.sin_addr),
            ntohs(tmp->peer_addr.sin_port), tmp->sock_fd);
    printf("/*----------------------*/\n");
}

void display_start_message(struct sockaddr_in addr)
{
    char *host_repr = malloc(sizeof(char) * 16);

    if (host_repr == NULL) {
        TEAMS_LOG("malloc");
        return;
    }
    memset(host_repr, 0, sizeof(char) * 16);
    inet_ntop(AF_INET, &addr.sin_addr, host_repr, 16);
    printf("Server started on %s:%hu.\n", host_repr, ntohs(addr.sin_port));
    free(host_repr);
}
