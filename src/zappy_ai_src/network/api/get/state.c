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
    printf("Get response : %s\n", resp);
    return true;
}