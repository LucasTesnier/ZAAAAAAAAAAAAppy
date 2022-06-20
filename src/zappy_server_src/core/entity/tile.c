/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** tile
*/

#include "entity/tile.h"
#include "container.h"
#include <stdbool.h>
#include <uuid/uuid.h>
#include <stdio.h>

tile_t *create_new_tile(void)
{
    tile_t *tile = malloc(sizeof(tile_t));

    if (tile == NULL)
        return (NULL);
    tile->inventory = new_container();
    TAILQ_INIT(&tile->entities);
    return tile;
}

bool is_entity_on_tile(tile_t *tile, entity_t *entity)
{
    entity_t *tmp = NULL;

    if (!tile || !entity)
        return false;
    TAILQ_FOREACH(tmp, &tile->entities, entities)
        if (entity == tmp)
            return true;
    return false;
}

bool add_entity_to_tile(tile_t *tile, entity_t *entity)
{
    if (entity->type == ENTITY_TILE_TYPE || is_entity_on_tile(tile, entity))
        return false;
    TAILQ_INSERT_TAIL(&tile->entities, entity, entities);
    return true;
}

bool remove_entity_from_tile(tile_t *tile, entity_t *entity)
{
    if (tile == NULL)
        return false;
    if (entity->type == ENTITY_TILE_TYPE || !is_entity_on_tile(tile, entity))
        return false;
    if (TAILQ_NEXT(entity, entities) == NULL) {
        TAILQ_REMOVE(&tile->entities, entity, entities);
        TAILQ_INIT(&tile->entities);
        return true;
    } else
        TAILQ_REMOVE(&tile->entities, entity, entities);
    return true;
}

void delete_tile(void *tile)
{
    tile_t *tile_data = (tile_t *)tile;

    if (tile_data == NULL)
        return;
    free(tile_data->inventory);
    free(tile_data);
}
