/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** entity_delete
*/

/// \file src/zappy_server/core/entity/entity_delete.c

#include "entity/entity.h"
#include "entity/eggs.h"
#include "entity/player.h"
#include "entity/tile.h"
#include "entity/entity_types.h"
#include <stdio.h>

/// \brief Entity data delete functions
static void (*entity_delete_funcs[])(void *) = {
    [ENTITY_PLAYER_TYPE] = delete_player,
    [ENTITY_EGG_TYPE] = delete_egg,
    [ENTITY_TILE_TYPE] = delete_tile
};

void delete_entity(entity_t *entity)
{
    if (!entity)
        return;
    dprintf(2, "||\tDeleting entity at pos: {%d, %d}\n",
    entity->position.x, entity->position.y);
    entity_delete_funcs[entity->type](entity->data);
    free(entity);
}
