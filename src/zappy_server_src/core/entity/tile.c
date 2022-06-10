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
    TAILQ_REMOVE(&tile->entities, entity, entities);
    return true;
}

void delete_tile(tile_t *tile)
{
    if (tile == NULL)
        return;
    free(tile->inventory);
    free(tile);
}