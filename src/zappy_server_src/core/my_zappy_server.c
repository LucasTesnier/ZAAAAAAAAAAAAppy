/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** my_zappy_server
*/

/// \file src/zappy_server_src/core/my_zappy_server.c

#include "my_zappy_server.h"
#include "fd_set_manage.h"

zappy_server_t *create_new_server(long port)
{
    zappy_server_t *new_server = malloc(sizeof(zappy_server_t));

    if (!new_server)
        return NULL;
    new_server->network_server = create_tcp_server(port);
    if (!new_server->network_server)
        return NULL;
    return new_server;
}

void destroy_zappy_server(zappy_server_t *server)
{
    if (server->network_server)
        free(server->network_server);
    if (server->network_server)
        free(server);
}