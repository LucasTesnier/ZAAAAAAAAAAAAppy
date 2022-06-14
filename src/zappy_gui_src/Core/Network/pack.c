/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** unpack
*/

/// \file src/zappy_gui_src/Core/Network/pack.c

#include "entity.h"
#include "entity_types.h"
#include "container.h"
#include "player.h"
#include "tile.h"
#include "eggs.h"
#include <string.h>
#include <sys/queue.h>
#include <stdio.h>

char *pack_int(int val)
{
    char *tmp;
    char str[80];

    sprintf(str, "%d", val);
    tmp = (char*)malloc(sizeof(char) * strlen(str) + 2);
    strcat(tmp, str);
    strcat(tmp, ";");
    return tmp;
}

char *pack_str(char *val)
{
    char *tmp;

    tmp = (char*)malloc(sizeof(char) * strlen(val) + 2);
    strcat(tmp, val);
    strcat(tmp, ";");
    return tmp;
}

char *pack_container(container_t *cont)
{
    char *tmp;
    char str[80];

    tmp = strdup(";inventory{");
    strcat(tmp, pack_int(cont->food));
    strcat(tmp, pack_int(cont->linemate));
    strcat(tmp, pack_int(cont->deraumere));
    strcat(tmp, pack_int(cont->sibur));
    strcat(tmp, pack_int(cont->mendiane));
    strcat(tmp, pack_int(cont->phiras));
    strcat(tmp, pack_int(cont->thystame));
    strcat(tmp, pack_str(strdup("}")));
    free(cont);
    return tmp;
}

char *pack_player(entity_t *entity)
{
    char *tmp;
    char str[80];
    player_t *player = (player_t*)malloc(sizeof(player_t));

    player = (player_t*)entity->data;
    tmp = strdup("player{");
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
    char *tmp;
    char str[80];
    tile_t *tile = (tile_t*)malloc(sizeof(tile_t));

    tile = (tile_t*)entity->data;
    tmp = strdup("tile{");
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
    tmp = strdup("egg{");
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

    switch (entity->type)
    {
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