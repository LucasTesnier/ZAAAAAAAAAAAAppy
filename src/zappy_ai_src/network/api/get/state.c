/*
** EPITECH PROJECT, 2022
** Project
** File description:
** state
*/

/// \file src/zappy_ai_src/network/api/get/state.c

#include "intern_data.h"
#include "client_utils.h"
#include "api.h"

bool c_interface_get_unexpected_response_state(void)
{
    if (client_data == NULL || !client_data->current_response)
        return false;
    if (get_retcodes().type == UNEXPECTED)
        return true;
    return false;
}

bool c_interface_get_response_sate(void)
{
    char *resp = NULL;

    if (client_data == NULL)
        return false;
    if (client_data->current_response)
        return true;
    update_client(client_data->net_srv);
    resp = fetch_message(client_data->net_srv);
    if (resp == NULL)
        return false;
    client_data->current_response = resp;
    dprintf(2, "Get response : %s\n", resp);
    return true;
}

bool c_interface_get_network_state(void)
{
    if (client_data == NULL)
        return false;
    if (!client_data->current_response)
        return true;
    if (!strcmp(client_data->current_response, "close"))
        return false;
    return true;
}