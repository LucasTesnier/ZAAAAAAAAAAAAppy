/*
** EPITECH PROJECT, 2022
** Project
** File description:
** entrpypoint
*/

/// THIS FILE IS GOING TO BE DELETED. USE IT ONLY FOR DEVELOPMENT

#include "api.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

void sigint_handler(int var __attribute__((unused)))
{
    c_interface_try_to_disconnect_to_server();
    exit(0);
}

int main(int ac, char **av)
{
    int port = atoi(av[1]);
    char *team_name = av[2];
    char *temp = NULL;

    (void) team_name;
    (void) ac;
    signal(SIGINT, sigint_handler);
    if (!c_interface_try_to_connect_to_server("127.0.0.1", port))
        return 84;
    while (!c_interface_get_response_sate());
    if (!c_interface_get_connect_to_server_response())
        return 84;
    if (!c_interface_ask_join("AAAAA"))
        return 84;
    while (!c_interface_get_response_sate());
    if (!c_interface_get_join_response())
        return 84;
    if (!c_interface_ask_inventory())
        return 84;
    while (!c_interface_get_response_sate());
    temp = c_interface_get_inventory_response();
    if (!temp)
        return 84;
    printf("Inventory : %s\n", temp);
    if (!c_interface_ask_forward())
        return 84;
    while (!c_interface_get_response_sate());
    if (!c_interface_get_forward_response())
        return 84;
    if (!c_interface_ask_right())
        return 84;
    while (!c_interface_get_response_sate());
    if (!c_interface_get_right_response())
        return 84;
    if (!c_interface_ask_left())
        return 84;
    while (!c_interface_get_response_sate());
    if (!c_interface_get_left_response())
        return 84;
    if (!c_interface_ask_look())
        return 84;
    while (!c_interface_get_response_sate());
    temp = c_interface_get_look_response();
    if (temp == NULL)
        return 84;
    printf("Look : %s\n", temp);
    c_interface_try_to_disconnect_to_server();
    return 0;
}