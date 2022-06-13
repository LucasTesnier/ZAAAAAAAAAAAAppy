/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** unpack
*/

/// \file src/zappygui/packunpack.c

#include "entity.h"
#include "entity_types.h"
#include "player.h"
#include <string.h>
#include <cstdio>
#include <sys/queue.h>

char *pack_container(container_t *cont)
{
    char *tmp;
    char str[80];

    tmp = strdup(";inventory{");
    sprintf(str, "%d", cont->food);
    strcat(tmp, str);
    strcat(tmp, ";");
    sprintf(str, "%d", cont->linemate);
    strcat(tmp, str);
    strcat(tmp, ";");
    sprintf(str, "%d", cont->deraumere);
    strcat(tmp, str);
    strcat(tmp, ";");
    sprintf(str, "%d", cont->sibur);
    strcat(tmp, str);
    strcat(tmp, ";");
    sprintf(str, "%d", cont->mendiane);
    strcat(tmp, str);
    strcat(tmp, ";");
    sprintf(str, "%d", cont->phiras);
    strcat(tmp, str);
    strcat(tmp, ";");
    sprintf(str, "%d", cont->thystame);
    strcat(tmp, str);
    strcat(tmp, "};");
    free(tmp);
    free(str);
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
    sprintf(str, "%d", entity->position.x);
    strcat(tmp, str);
    strcat(tmp, ";");
    sprintf(str, "%d", entity->position.y);
    strcat(tmp, str);
    strcat(tmp, pack_container(player->inventory));
    strcat(tmp, player->team);
    strcat(tmp, ";");
    sprintf(str, "%d", player->level);
    strcat(tmp, str);
    strcat(tmp, "}");
    free(tmp);
    free(str);
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
    sprintf(str, "%d", entity->position.x);
    strcat(tmp, str);
    strcat(tmp, ";");
    sprintf(str, "%d", entity->position.y);
    strcat(tmp, str);
    strcat(tmp, pack_container(tile->inventory));
    strcat(tmp, "}");
    free(tmp);
    free(str);
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
    sprintf(str, "%d", entity->position.x);
    strcat(tmp, str);
    strcat(tmp, ";");
    sprintf(str, "%d", entity->position.y);
    strcat(tmp, str);
    strcat(tmp, ";");
    strcat(tmp, egg->team_name);
    strcat(tmp, "}");
    return tmp;
}

char *pack(entity_t *entity)
{
    entity_t *ent;
    char *packed = strdup("");
    TAILQ_FOREACH(ent, entity, entity->entities) {
        switch (entity->type)
        {
        case ENTITY_PLAYER_TYPE:
            strcat(packed, pack_player(ent));
            break;
        case ENTITY_TILE_TYPE:
            strcat(packed, pack_tile(ent));
            break;
        case ENTITY_EGG_TYPE:
            strcat(packed, pack_egg(ent));
            break;
        default:
            break;
        }
    }
    return packed;
}