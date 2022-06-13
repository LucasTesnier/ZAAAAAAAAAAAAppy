/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** map
*/

#include "map.h"
#include "entity/entity.h"
#include <stdlib.h>

map_t *create_new_map(int width, int height)
{
    map_t *map = malloc(sizeof(map_t));

    if (!map)
        return NULL;
    map->tiles = malloc(sizeof(entity_t *) * height * width);
    if (!map->tiles)
        return NULL;
    return map;
}

entity_t* get_tile(map_t *map, int x, int y)
{
    if (!map)
        return NULL;
    if (x < 0 || x >= map->width || y < 0 || y >= map->height)
        return NULL;
    return map->tiles[y * map->width + x];
}
