/*
** EPITECH PROJECT, 2022
** Project
** File description:
** restart
*/

/// \file src/zappy_gui_src/network/api/get/restart.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"

bool c_interface_get_restart_response(void)
{
    if (client_data == NULL || !client_data->current_response)
        return false;
    if (get_retcodes().number != 710)
        return retcode_exit(false);
    return retcode_exit(true);
}
