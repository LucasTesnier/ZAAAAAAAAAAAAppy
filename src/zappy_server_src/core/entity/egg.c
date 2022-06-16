/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** egg
*/

/// \file src/zappy_server_src/core/entity/egg.c

#include "entity/eggs.h"
#include <uuid/uuid.h>
#include <stdlib.h>

egg_t *create_new_egg(const char *team_name)
{
    egg_t *egg = malloc(sizeof(egg_t));

    if (egg == NULL)
        return (NULL);
    egg->team_name = strdup(team_name);
    uuid_generate(egg->id);
    return egg;
}

void delete_egg(void *egg)
{
    egg_t *egg_data = (egg_t *)egg;

    if (egg == NULL)
        return;
    free(egg_data->team_name);
    free(egg_data);
}
