/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** fetch_message
*/

/// \file client/client_net_utils/fetch_message.c

#include "client_utils.h"
#include <string.h>
#include <unistd.h>

char *fetch_message(client_net_server_t *server)
{
    char *msg;
    ssize_t read_size = 0;

    if (!server || !server->pending_read)
        return NULL;
    server->pending_read = false;
    read_size = read(server->sock_fd, server->input_buffer, MAX_MSG);
    if (read_size < 0) {
        TEAMS_LOG("Internal Server Error: read\n");
        return NULL;
    }
    if (read_size == 0) {
        TEAMS_LOG("Connection to the server lost\n");
        return NULL;
    }
    server->input_buffer[read_size] = '\0';
    msg = strndup(server->input_buffer, strlen(server->input_buffer));
    return msg;
}
