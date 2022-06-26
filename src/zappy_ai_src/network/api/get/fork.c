/*
** EPITECH PROJECT, 2022
** Project
** File description:
** fork
*/

/// \file src/zappy_ai_src/network/api/get/fork.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"

bool c_interface_get_fork_response(void)
{
    if (client_data == NULL || !client_data->current_response)
        return false;
    if (strncmp(client_data->current_response, "218", 3))
        return retcode_exit(false);
    return retcode_exit(true);
}
