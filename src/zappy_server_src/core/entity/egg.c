/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** egg
*/

/// \file src/zappy_server/core/include/entity/egg.h

#include "entity/eggs.h"
#include <uuid/uuid.h>

egg_t *create_new_egg(const char *team_name)
{
    egg_t *egg = malloc(sizeof(egg_t));

    if (egg == NULL)
        return (NULL);
    egg->team_name = strdup(team_name);
    uuid_generate(egg->id);
    return egg;
}

void delete_egg(egg_t *egg)
{
    free(egg->team_name);
    free(egg);
}
