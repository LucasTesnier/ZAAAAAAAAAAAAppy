/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** entity_wrapper_remove
*/

/// \file src/zappy_server/core/entity/entity_wrapper_remove.c

#include <stdlib.h>
#include "entity/entity.h"
#include "entity/entity_types.h"
#include "entity/eggs.h"
#include "entity/player.h"
#include "entity/tile.h"
#include "sys/queue.h"
#include <stdio.h>

void entity_wrapper_remove_entity(entity_wrapper_t *wrapper, entity_t *entity)
{
    if (!wrapper || !entity)
        return;
    switch (entity->type) {
        case ENTITY_PLAYER_TYPE:
            printf("AAAAAA\n");
            TAILQ_REMOVE(&wrapper->players, entity, entities);
            break;
        case ENTITY_EGG_TYPE:
            TAILQ_REMOVE(&wrapper->eggs, entity, entities);
            break;
        case ENTITY_TILE_TYPE:
            TAILQ_REMOVE(&wrapper->tiles, entity, entities);
            break;
        default:
            break;
    }
    delete_entity(entity);
}
