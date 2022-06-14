/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** unpack
*/

/// \file src/zappy_server_src/core/entity/pack.c

#include "entity.h"
#include "entity_types.h"
#include "container.h"
#include "player.h"
#include "tile.h"
#include "eggs.h"
#include <string.h>
#include <sys/queue.h>
#include <stdio.h>
#include <stdlib.h>

char *pack_container(container_t *cont)
{
    char *tmp = (char*)malloc(sizeof(char) * (get_len_container(cont) + 21));

    strcpy(tmp, ";inventory{");
    strcat(tmp, pack_int(cont->food));
    strcat(tmp, pack_int(cont->linemate));
    strcat(tmp, pack_int(cont->deraumere));
    strcat(tmp, pack_int(cont->sibur));
    strcat(tmp, pack_int(cont->mendiane));
    strcat(tmp, pack_int(cont->phiras));
    strcat(tmp, pack_int(cont->thystame));
    strcat(tmp, pack_str("}"));
    free(cont);
    return tmp;
}

char *pack_player(entity_t *entity)
{
    player_t *player = (player_t*)malloc(sizeof(player_t));
    char *tmp;

    player = (player_t*)entity->data;
    tmp = (char*)malloc(sizeof(char) * (get_len_player(entity, player) + 35));
    strcpy(tmp, "player{");
    strcat(tmp, pack_int(entity->position.x));
    strcat(tmp, pack_int(entity->position.y));
    strcat(tmp, pack_container(player->inventory));
    strcat(tmp, pack_str(player->team));
    strcat(tmp, pack_int(player->level));
    strcat(tmp, pack_int(player->orientation));
    strcat(tmp, pack_str(strdup("}")));
    free(player);
    return tmp;
}

char *pack_tile(entity_t *entity)
{
    tile_t *tile = (tile_t*)malloc(sizeof(tile_t));
    char *tmp;

    tile = (tile_t*)entity->data;
    tmp = (char*)malloc(sizeof(char) * (get_len_tile(entity, tile) + 30));
    strcpy(tmp, "tile{");
    strcat(tmp, pack_int(entity->position.x));
    strcat(tmp, pack_int(entity->position.y));
    strcat(tmp, pack_container(tile->inventory));
    strcat(tmp, pack_str(strdup("}")));
    free(tile);
    return tmp;
}

char *pack_egg(entity_t *entity)
{
    char *tmp;
    char str[80];
    egg_t *egg = (egg_t*)malloc(sizeof(egg_t));

    egg = (egg_t*)entity->data;
    tmp = malloc(sizeof(char) * (get_len_egg(entity, egg) + 10));
    strcpy(tmp, strdup("egg{"));
    strcat(tmp, pack_int(entity->position.x));
    strcat(tmp, pack_int(entity->position.y));
    strcat(tmp, pack_str((char *)egg->team_name));
    strcat(tmp, pack_str(strdup("}")));
    return tmp;
}

char *pack(entity_t *entity)
{
    char *packed = strdup("");
    char *tmp;

    switch (entity->type) {
        case ENTITY_PLAYER_TYPE:
            tmp = pack_player(entity);
            strcat(packed, tmp);
            free(tmp);
            break;
        case ENTITY_TILE_TYPE:
            strcat(packed, pack_tile(entity));
            break;
        case ENTITY_EGG_TYPE:
            strcat(packed, pack_egg(entity));
            break;
        default:
            break;
    }
    return packed;
}