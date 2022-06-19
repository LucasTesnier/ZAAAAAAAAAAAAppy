/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** send_message
*/

/// \file src/zappy_gui_src/network/net_utils/send_message.c

#include "client_utils.h"
#include <string.h>
#include <unistd.h>

void set_output_buffer(client_net_server_t *server, const char *msg)
{
    if (!server || !msg)
        return;
    if (server->pending_write || strlen(msg) == 0)
        return;
    strcpy(server->output_buffer, msg);
    server->pending_write = true;
}

bool send_message(client_net_server_t *server)
{
    if (!server)
        return false;
    if (server->connected)
        write(server->sock_fd,
        server->output_buffer,
        strlen(server->output_buffer));
    server->pending_write = false;
    return true;
}
