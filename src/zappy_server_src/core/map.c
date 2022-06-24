/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** map
*/

/// \file src/zappy_server_src/core/map.c

#include "map.h"
#include "entity/entity.h"
#include "entity/tile.h"
#include "entity/entity_types.h"
#include <stdlib.h>
#include <stdio.h>

/// \brief List of all the ressource and her density for gen
static const generate_t gen_list[] = {
    {"food", 0.5},
    {"linemate", 0.3},
    {"deraumere", 0.15},
    {"sibur", 0.1},
    {"mendiane", 0.1},
    {"phiras", 0.08},
    {"thystame", 0.05},
    {NULL, -1}
};

/// \brief Compute the quantity of a ressource by her density
/// \param map The map informations
/// \param density The density of the ressource
/// \return int The quantity of the ressource
static int compute_ressource_number(map_t *map, float density)
{
    float res = 0;

    res = (float)map->width * (float)map->height;
    res *= density;
    if (res < 0)
        res = 1;
    return (int)res;
}

/// \brief Add a ressource inside a random tile
/// \param map The map informations
/// \param type The type of the ressources
static void add_ressource_randomly(map_t *map, char *type,
entity_diff_t *modified_entities)
{
    entity_t *tile = get_tile(map, rand() % map->width, rand() % map->height);
    container_t *cases = NULL;

    if (tile == NULL)
        return;
    cases = ((tile_t *)tile->data)->inventory;
    if (!strcmp(type, "food"))
        cases->food += 1;
    if (!strcmp(type, "linemate"))
        cases->linemate += 1;
    if (!strcmp(type, "deraumere"))
        cases->deraumere += 1;
    if (!strcmp(type, "sibur"))
        cases->sibur += 1;
    if (!strcmp(type, "mendiane"))
        cases->mendiane += 1;
    if (!strcmp(type, "phiras"))
        cases->phiras += 1;
    if (!strcmp(type, "thystame"))
        cases->thystame += 1;
    entity_diff_add_entity(modified_entities, tile);
}

void generate_new_resource(map_t *map, entity_diff_t *modified_entities)
{
    for (int i = 0; gen_list[i].name; i++) {
        for (int j = 0; j <
        compute_ressource_number(map, gen_list[i].density) + 1; j++)
            add_ressource_randomly(map, gen_list[i].name, modified_entities);
    }
}

entity_t* get_tile(map_t *map, int x, int y)
{
    if (!map)
        return NULL;
    if (x < 0 || x >= map->width || y < 0 || y >= map->height)
        return map->tiles[0];
    return map->tiles[y * map->width + x];
}

map_t *create_new_map(int width, int height)
{
    map_t *map = malloc(sizeof(map_t));

    if (!map)
        return NULL;
    map->tiles = malloc(sizeof(entity_t *) * height * width);
    if (!map->tiles)
        return NULL;
    map->height = height;
    map->width = width;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            map->tiles[i * width + j] = create_entity(ENTITY_TILE_TYPE,
                (position_t){j, i});
            map->tiles[i * width + j]->data = create_new_tile();
        }
    }
    generate_new_resource(map, NULL);
    return map;
}
