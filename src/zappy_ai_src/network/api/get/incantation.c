/*
** EPITECH PROJECT, 2022
** Project
** File description:
** incantation
*/

/// \file src/zappy_ai_src/network/api/get/incantation.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"
#include <stdlib.h>

int c_interface_get_incantation_response(void)
{
    char *res = NULL;

    if (client_data == NULL || !client_data->current_response)
        return 0;
    if (strncmp(client_data->current_response, "222", 3)) {
        retcode_exit(false);
        return 0;
    }
    res = retcode_get_arg();
    retcode_exit(true);
    if (res == NULL)
        return 0;
    return atoi(res);
}
