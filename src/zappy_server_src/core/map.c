/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** map
*/

#include "map.h"
#include "entity/entity.h"
#include "entity/tile.h"
#include "entity/entity_types.h"
#include <stdlib.h>

entity_t* get_tile(map_t *map, int x, int y)
{
    if (!map)
        return NULL;
    if (x < 0 || x >= map->width || y < 0 || y >= map->height)
        return NULL;
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
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            map->tiles[i * width + j] = create_entity(ENTITY_TILE_TYPE,
                (position_t){j, i});
            map->tiles[i * width + j]->data = create_new_tile();
        }
    }
    return map;
}
