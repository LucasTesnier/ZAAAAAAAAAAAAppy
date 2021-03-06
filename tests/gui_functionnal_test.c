/*
** EPITECH PROJECT, 2022
** Project
** File description:
** entrypoint
*/

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

    (void) ac;
    signal(SIGINT, sigint_handler);
    if (!c_interface_try_to_connect_to_server("127.0.0.1", port))
        return 84;
    while (1) {
        while (!c_interface_get_response_state());
        if (!c_interface_get_unexpected_response_state())
            return 84;
        char *temp = c_interface_get_unexpected_response();
        printf("Unexpected : %s\n", temp);
        free(temp);
    }
    c_interface_try_to_disconnect_to_server();
    return 0;
}
