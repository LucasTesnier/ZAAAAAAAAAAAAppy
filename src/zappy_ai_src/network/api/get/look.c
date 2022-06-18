/*
** EPITECH PROJECT, 2022
** Project
** File description:
** look
*/

/// \file src/zappy_ai_src/network/api/get/look.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"

char *c_interface_get_look_response(void)
{
    char *res = NULL;

    if (client_data == NULL || !client_data->current_response)
        return false;
    if (strncmp(client_data->current_response, "215", 3)) {
        retcode_exit(false);
        return NULL;
    }
    res = retcode_get_arg();
    retcode_exit(true);
    return res;
}
