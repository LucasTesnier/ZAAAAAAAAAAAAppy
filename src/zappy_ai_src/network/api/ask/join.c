/*
** EPITECH PROJECT, 2022
** Project
** File description:
** join
*/

/// \file src/zappy_ai_src/network/api/ask/join.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"
#include <stdlib.h>

bool c_interface_ask_join(char *team_name)
{
    char *message = NULL;

    if (client_data == NULL || client_data->net_srv->pending_write)
        return false;
    message = malloc(sizeof(char) * (strlen(team_name) + 7));
    if (!message)
        return false;
    message[0] = '\0';
    strcat(message, "/join ");
    strcat(message, team_name);
    strcat(message, "\n\n");
    set_output_buffer(client_data->net_srv, message);
    free(message);
    return true;
}