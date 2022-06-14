/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** pack_get_len
*/

/// \file src/zappy_server_src/core/entity/pack_get_len.c

#include "entity.h"
#include "container.h"
#include "player.h"
#include "tile.h"
#include "eggs.h"
#include "pack.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int get_int_len(int val)
{
    char str[80];

    memset(str, 0, 80);
    sprintf(str, "%d", val);
    return strlen(str);
}

int get_len_container(container_t *cont)
{
    int len = 0;

    len += get_int_len(cont->food);
    len += get_int_len(cont->linemate);
    len += get_int_len(cont->deraumere);
    len += get_int_len(cont->sibur);
    len += get_int_len(cont->mendiane);
    len += get_int_len(cont->phiras);
    len += get_int_len(cont->thystame);
    return len;
}

int get_len_player(entity_t *ent, player_t *p)
{
    int len = 0;

    len += get_int_len(ent->position.x);
    len += get_int_len(ent->position.y);
    len += get_len_container(p->inventory);
    len += strlen(p->team);
    len += get_int_len(p->level);
    len += get_int_len(p->orientation);
    return len;
}

int get_len_tile(entity_t *ent, tile_t *t)
{
    int len = 0;

    len += get_int_len(ent->position.x);
    len += get_int_len(ent->position.y);
    len += get_len_container(t->inventory);
    return len;
}

int get_len_egg(entity_t *ent, egg_t *e)
{
    int len = 0;

    len += get_int_len(ent->position.x);
    len += get_int_len(ent->position.y);
    len += strlen(e->team_name);
    return len;
}
