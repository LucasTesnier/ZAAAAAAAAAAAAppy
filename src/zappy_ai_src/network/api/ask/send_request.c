/*
** EPITECH PROJECT, 2022
** Project
** File description:
** send_request
*/

/// \file src/zappy_ai_src/network/api/ask/send_request.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"
#include <stdlib.h>

bool send_request(char *command, char *arg)
{
    char *message = malloc(sizeof(char) * (((!arg) ? 0 : strlen(arg)) + 7));

    if (!message)
        return false;
    message[0] = '\0';
    if (arg)
        sprintf(message, "/%s %s\n\n", command, arg);
    else
        sprintf(message, "/%s\n\n", command);
    set_output_buffer(client_data->net_srv, message);
    free(message);
    return true;
}