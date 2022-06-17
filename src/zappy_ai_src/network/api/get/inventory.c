/*
** EPITECH PROJECT, 2022
** Project
** File description:
** inventory
*/

/// \file src/zappy_ai_src/network/api/get/inventory.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"

char *c_interface_get_inventory_response(void)
{
    if (client_data == NULL || !client_data->current_response)
        return NULL;
    if (strncmp(client_data->current_response, "212", 3)) {
        retcode_exit(false);
        return NULL;
    }
    return retcode_get_arg();
}