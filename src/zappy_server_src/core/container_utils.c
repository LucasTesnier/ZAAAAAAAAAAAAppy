/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** container_utils
*/

/// \file src/zappy_server_src/core/container_utils.c

#include "container.h"
#include <stdio.h>

void debug_display_container(container_t *container)
{
    if (!container)
        return;
    printf("===== CONTAINER =====\n");
    printf("\tlinemate: %d\n", container->linemate);
    printf("\tderaumere: %d\n", container->deraumere);
    printf("\tsibur: %d\n", container->sibur);
    printf("\tmendiane: %d\n", container->mendiane);
    printf("\tphiras: %d\n", container->phiras);
    printf("\tthystame: %d\n", container->thystame);
    printf("=====================\n");
}

void delete_container(container_t *container)
{
    if (!container)
        return;
    free(container);
}

container_t *new_container(void)
{
    container_t *container = (container_t*)malloc(sizeof(container_t));

    if (!container)
        return NULL;
    memset(container, 0, sizeof(container_t));
}
