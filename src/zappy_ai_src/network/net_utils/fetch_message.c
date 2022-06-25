/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** fetch_message
*/

/// \file src/zappy_ai_src/network/net_utils/fetch_message.c

#include "client_utils.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/// \brief Read a new message
/// \param server The server data
/// \return char* The readed message
static char *read_a_message(client_net_server_t *server)
{
    ssize_t read_size = 0;

    read_size = read(server->sock_fd, server->input_buffer, MAX_MSG);
    if (read_size < 0) {
        ZAPPY_LOG("Internal Server Error: read\n");
        return NULL;
    }
    if (read_size == 0) {
        ZAPPY_LOG("Connection to the server lost\n");
        return "close";
    }
    server->input_buffer[read_size] = '\0';
    return strndup(server->input_buffer, strlen(server->input_buffer));
}

char *fetch_message(client_net_server_t *server)
{
    char *msg;
    char *temp = NULL;

    if (!server || !server->pending_read)
        return NULL;
    server->pending_read = false;
    msg = read_a_message(server);
    if (msg == NULL || !strcmp(msg, "close") || msg[strlen(msg) - 1] == '\n')
        return msg;
    while ((temp = read_a_message(server)) != NULL && strcmp(temp, "close")) {
        msg = realloc(msg, sizeof(char) * (strlen(msg) + strlen(temp) + 10));
        strcat(msg, temp);
        if (msg[strlen(msg) - 1] == '\n')
            break;
        free(temp);
    }
    return msg;
}
