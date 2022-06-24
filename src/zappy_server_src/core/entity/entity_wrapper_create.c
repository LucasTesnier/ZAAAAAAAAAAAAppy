/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** entity_wrapper_create
*/

/// \file src/zappy_server/core/include/entity/entity_wrapper_create.c

#include <stdlib.h>
#include "entity/entity.h"
#include "entity/eggs.h"
#include "entity/player.h"
#include "entity/tile.h"
#include "sys/queue.h"

void entity_wrapper_create_player(entity_wrapper_t *wrapper, position_t pos,
const char *team_name)
{
    entity_t *entity = create_entity(ENTITY_PLAYER_TYPE, pos);
    player_t *player_data = create_player(team_name);

    if (!wrapper || !entity || !player_data)
        return;
    entity->position = pos;
    entity->data = player_data;
    TAILQ_INSERT_TAIL(&wrapper->players, entity, entities);
}

entity_t * entity_wrapper_create_egg(entity_wrapper_t *wrapper, position_t pos,
const char *team_name)
{
    entity_t *entity = create_entity(ENTITY_EGG_TYPE, pos);
    egg_t *egg_data = create_new_egg(team_name);

    if (!wrapper || !entity || !egg_data)
        return NULL;
    entity->position = pos;
    entity->data = egg_data;
    TAILQ_INSERT_TAIL(&wrapper->eggs, entity, entities);
    return entity;
}

void entity_wrapper_create_tile(entity_wrapper_t *wrapper, position_t pos)
{
    entity_t *entity = create_entity(ENTITY_TILE_TYPE, pos);
    tile_t *tile_data = create_new_tile();

    if (!wrapper || !entity || !tile_data)
        return;
    entity->position = pos;
    entity->data = tile_data;
    TAILQ_INSERT_TAIL(&wrapper->tiles, entity, entities);
}
