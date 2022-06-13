/*
** EPITECH PROJECT, 2022
** Project
** File description:
** unexpected
*/

/// \file src/zappy_gui_src/network/api/get/unexpected.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"

char *c_interface_get_unexpected_response(void)
{
    retcodes_t retcode;

    if (client_data == NULL || !client_data->current_response)
        return NULL;
    retcode = get_retcodes();
    if (retcode.type != UNEXPECTED)
        return NULL;
    if (retcode.number == 211)
        return get_retcode_arg(retcode);
}