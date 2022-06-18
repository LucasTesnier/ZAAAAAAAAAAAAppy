/*
** EPITECH PROJECT, 2022
** Project
** File description:
** broadcast
*/

/// \file src/zappy_ai_src/network/api/get/broadcast.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"

bool c_interface_get_broadcast_response(void)
{
    if (client_data == NULL || !client_data->current_response)
        return false;
    if (strncmp(client_data->current_response, "216", 3))
        return retcode_exit(false);
    return retcode_exit(true);
}