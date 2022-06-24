/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** Unpack
*/

/// \file src/zappy_server_src/core/entity/pack_entity.c

#include "entity/entity.h"
#include "entity/entity_types.h"
#include "container.h"
#include "entity/player.h"
#include "entity/tile.h"
#include "entity/eggs.h"
#include "entity/pack.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>

char *pack_container(container_t *cont)
{
    char *tmp = NULL;

    if ((tmp = (char*)malloc(sizeof(char) * (get_len_container(cont) + CONT_SIZE))) == NULL)
        return NULL;
    sprintf(tmp, "inventory{%d;%d;%d;%d;%d;%d;%d}",
            cont->food,
            cont->linemate,
            cont->deraumere,
            cont->sibur,
            cont->mendiane,
            cont->phiras,
            cont->thystame);
    return tmp;
}

char *pack_player(entity_t *entity)
{
    char *tmp = NULL;
    player_t *player = NULL;
    char *container = NULL;
    char *player_uuid = malloc(sizeof(char) * 40);

    player = (player_t*)entity->data;
    if ((tmp = (char*)malloc(sizeof(char) *
        (get_len_player(entity, player) + PLAYER_SIZE))) == NULL)
        return NULL;
    container = pack_container(player->inventory);
    uuid_unparse(player->uuid, player_uuid);
    sprintf(tmp, "player{%d;%d;%s;%d;%s;%s;%d;%d}",
            entity->position.x, entity->position.y, player_uuid,
            player->status, container, player->team, player->level,
            player->orientation);
    free(container);
    free(player_uuid);
    return tmp;
}

char *pack_tile(entity_t *entity)
{
    char *tmp = NULL;
    char *container = NULL;
    tile_t *tile = NULL;

    tile = (tile_t*)entity->data;
    if ((tmp = (char*)malloc(sizeof(char) *
        (get_len_tile(entity, tile) + TILE_SIZE))) == NULL)
        return NULL;
    container = pack_container(tile->inventory);
    sprintf(tmp, "tile{%d;%d;%s}",
            entity->position.x,
            entity->position.y,
            container);
    free(container);
    return tmp;
}

char *pack_egg(entity_t *entity)
{
    char *tmp = NULL;
    egg_t *egg = NULL;
    char *egg_uuid = malloc(sizeof(char) * 40);

    egg = (egg_t*)entity->data;
    if ((tmp = malloc(sizeof(char) *
        (get_len_egg(entity, egg) + EGG_SIZE))) == NULL)
        return NULL;
    uuid_unparse(egg->id, egg_uuid);
    sprintf(tmp, "egg{%d;%d;%s;%s}",
            entity->position.x,
            entity->position.y,
            egg_uuid,
            (char *)egg->team_name);
    free(egg_uuid);
    return tmp;
}

char *pack_entity(entity_t *entity)
{
    char *packed = NULL;

    switch (entity->type) {
        case ENTITY_PLAYER_TYPE:
            packed = pack_player(entity);
            break;
        case ENTITY_TILE_TYPE:
            packed = pack_tile(entity);
            break;
        case ENTITY_EGG_TYPE:
            packed = pack_egg(entity);
            break;
        default:
            break;
    }
    return packed;
}
