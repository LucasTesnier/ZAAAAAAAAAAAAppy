/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** entity_wrapper_add
*/

/// \file src/zappy_server_src/core/entity/entity_wrapper_add.c

#include "entity/entity.h"
#include "entity/player.h"
#include "entity/eggs.h"
#include <sys/queue.h>

void entity_wrapper_add_player(entity_wrapper_t *wrapper, entity_t *player)
{
    if (!wrapper || !player)
        return;
    TAILQ_INSERT_TAIL(&wrapper->players, player, entities);
}

void entity_wrapper_add_egg(entity_wrapper_t *wrapper, entity_t *egg)
{
    if (!wrapper || !egg)
        return;
    TAILQ_INSERT_TAIL(&wrapper->eggs, egg, entities);
}
