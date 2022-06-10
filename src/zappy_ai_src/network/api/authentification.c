/*
** EPITECH PROJECT, 2022
** Project
** File description:
** authentification
*/

#include "intern_data.h"
#include "client_utils.h"

volatile zappy_client_t *client_data = NULL;

bool c_interface_try_to_connect_to_server(char *host, long port,
char *team_name)
{
    if (client_data != NULL) {
        dprintf(2, "You are already connected to the server.\n");
        return false;
    }
    (void) host;
    (void) port;
    (void) team_name;
    return true;
}

bool c_interface_try_to_disconnect_to_server(void)
{
    if (client_data == NULL) {
        dprintf(2, "You are already disconnected from the server.\n");
        return false;
    }
    return true;
}