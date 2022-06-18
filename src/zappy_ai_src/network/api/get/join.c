/*
** EPITECH PROJECT, 2022
** Project
** File description:
** join
*/

/// \file src/zappy_ai_src/network/api/get/join.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"

char *c_interface_get_join_response(void)
{
    char *res = NULL;

    if (client_data == NULL || !client_data->current_response)
        return NULL;
    if (strncmp(client_data->current_response, "211", 3)) {
        retcode_exit(false);
        return NULL;
    }
    res = retcode_get_arg();
    retcode_exit(true);
    return res;
}
