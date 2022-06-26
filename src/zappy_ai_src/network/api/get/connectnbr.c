/*
** EPITECH PROJECT, 2022
** Project
** File description:
** connectnbr
*/

/// \file src/zappy_ai_src/network/api/get/connectnbr.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"
#include <stdlib.h>

int c_interface_get_connectable_response(void)
{
    char *res = NULL;

    if (client_data == NULL || !client_data->current_response)
        return -1;
    if (strncmp(client_data->current_response, "217", 3)) {
        retcode_exit(false);
        return -1;
    }
    res = retcode_get_arg();
    retcode_exit(true);
    if (res == NULL)
        return -1;
    return atoi(res);
}
