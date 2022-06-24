/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** container_utils
*/

/// \file src/zappy_server_src/core/container_utils.c

#include "container.h"
#include <stdio.h>

/// \brief Utility function to get the length of an int
static size_t get_int_len(int val)
{
    char str[80];

    memset(str, 0, 80);
    sprintf(str, "%d", val);
    return strlen(str);
}

/// \brief get the length of the str representation of a container
static int get_len_container(container_t *cont)
{
    int len = 0;

    len += get_int_len(cont->food);
    len += get_int_len(cont->linemate);
    len += get_int_len(cont->deraumere);
    len += get_int_len(cont->sibur);
    len += get_int_len(cont->mendiane);
    len += get_int_len(cont->phiras);
    len += get_int_len(cont->thystame);
    return len;
}

char *pack_inventory(container_t *inv)
{
    char *tmp;

    if ((tmp = (char*)malloc(sizeof(char) *
        (get_len_container(inv) + 88))) == NULL)
        return NULL;
    sprintf(tmp, "[food %d, linemate %d, deraumere %d, sibur %d, mendiane %d, \
phiras %d, thystame %d]",
            inv->food,
            inv->linemate,
            inv->deraumere,
            inv->sibur,
            inv->mendiane,
            inv->phiras,
            inv->thystame);
    return tmp;
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
    return container;
}
