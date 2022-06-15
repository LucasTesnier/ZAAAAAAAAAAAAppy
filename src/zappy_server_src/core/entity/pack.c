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
#include "pack.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *pack_container(container_t *cont)
{
    char *tmp;

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
    free(cont);
    return tmp;
}

char *pack_player(entity_t *entity)
{
    char *tmp;
    player_t *player;

    if ((player = (player_t*)malloc(sizeof(player_t))) == NULL)
        return NULL;
    player = (player_t*)entity->data;
    if ((tmp = (char*)malloc(sizeof(char) *
        (get_len_player(entity, player) + PLAYER_SIZE))) == NULL)
        return NULL;
    sprintf(tmp, "player{%d;%d;%s;%s;%d;%d}",
            entity->position.x,
            entity->position.y,
            pack_container(player->inventory),
            player->team,
            player->level,
            player->orientation);
    free(player);
    return tmp;
}

char *pack_tile(entity_t *entity)
{
    char *tmp;
    tile_t *tile;

    if ((tile = (tile_t*)malloc(sizeof(tile_t))) == NULL)
        return NULL;
    tile = (tile_t*)entity->data;
    if ((tmp = (char*)malloc(sizeof(char) *
        (get_len_tile(entity, tile) + TILE_SIZE))) == NULL)
        return NULL;
    sprintf(tmp, "tile{%d;%d;%s}",
            entity->position.x,
            entity->position.y,
            pack_container(tile->inventory));
    free(tile);
    return tmp;
}

char *pack_egg(entity_t *entity)
{
    char *tmp;
    egg_t *egg;

    if ((egg = (egg_t*)malloc(sizeof(egg_t))) == NULL)
        return NULL;
    egg = (egg_t*)entity->data;
    if ((tmp = malloc(sizeof(char) *
        (get_len_egg(entity, egg) + EGG_SIZE))) == NULL)
        return NULL;
    sprintf(tmp, "egg{%d;%d;%s}",
            entity->position.x,
            entity->position.y,
            (char *)egg->team_name);
    return tmp;
}

//TODO subject of the pack (entity_pack?)
char *pack(entity_t *entity)
{
    char *packed;

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

int main(void)
{
    position_t pos= {.x = 42, .y = 4242};
    entity_t *ent = create_entity(ENTITY_PLAYER_TYPE, pos);
    player_t *p = create_player(strdup("guiguilebg"));
    ent->data = p;
    char *test = pack(ent);
    printf("%s\n", test);


    position_t pos1= {.x = 42, .y = 4242};
    entity_t *ent2 = create_entity(ENTITY_TILE_TYPE, pos1);
    tile_t *p2 = create_new_tile();
    entity_set_data(ent2, p2);
    char *test2 = pack(ent2);
    printf("%s\n", test2);


    position_t pos2= {.x = 42, .y = 4242};
    entity_t *ent3 = create_entity(ENTITY_EGG_TYPE, pos2);
    egg_t *p3 = create_new_egg(strdup("guiguilebgoeuf"));
    ent3->data = p3;
    char *test3 = pack(ent3);
    printf("%s\n", test3);
    return 0;
}