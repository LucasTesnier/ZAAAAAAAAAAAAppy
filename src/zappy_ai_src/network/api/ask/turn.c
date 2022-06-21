/*
** EPITECH PROJECT, 2022
** Project
** File description:
** turn
*/

/// \file src/zappy_ai_src/network/api/ask/turn.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"

bool c_interface_ask_right(void)
{
    if (client_data == NULL || client_data->net_srv->pending_write
    || !c_interface_get_network_state())
        return false;
    return send_request("turn", "right");
}

bool c_interface_ask_left(void)
{
    if (client_data == NULL || client_data->net_srv->pending_write
    || !c_interface_get_network_state())
        return false;
    return send_request("turn", "left");
}