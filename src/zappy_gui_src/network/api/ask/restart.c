/*
** EPITECH PROJECT, 2022
** Project
** File description:
** restart
*/

/// \file src/zappy_gui_src/network/api/ask/restart.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"
#include <stdlib.h>

bool c_interface_ask_restart(char *configuration)
{
    char *message = NULL;

    if (client_data == NULL || client_data->net_srv->pending_write)
        return false;
    message = malloc(sizeof(char) * (strlen(configuration) + 7));
    if (!message)
        return false;
    message[0] = '\0';
    strcat(message, "/restart ");
    strcat(message, configuration);
    strcat(message, "\n\n");
    set_output_buffer(client_data->net_srv, message);
    free(message);
    return true;
}