/*
** EPITECH PROJECT, 2022
** Project
** File description:
** unexpected
*/

/// \file src/zappy_ai_src/network/api/get/unexpected.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"

char *c_interface_get_unexpected_response(void)
{
    retcodes_t retcode;
    char *temp = NULL;

    if (client_data == NULL || !client_data->current_response)
        return NULL;
    retcode = get_retcodes();
    if (retcode.type != UNEXPECTED)
        return NULL;
    if (retcode.number == 601) {
        retcode_exit(true);
        return "dead";
    }
    temp = retcode_get_arg();
    retcode_exit(true);
    return temp;
}