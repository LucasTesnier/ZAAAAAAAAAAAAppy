/*
** EPITECH PROJECT, 2022
** Project
** File description:
** join
*/

/// \file src/zappy_ai_src/network/api/ask/join.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"

bool c_interface_ask_join(char *team_name)
{
    if (client_data == NULL || client_data->net_srv->pending_write)
        return false;
    return send_request("join", team_name);
}