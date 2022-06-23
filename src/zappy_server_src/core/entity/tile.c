/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** tile
*/

#include "entity/tile.h"
#include "container.h"
#include <stdbool.h>
#include <uuid/uuid.h>
#include <stdio.h>

tile_t *create_new_tile(void)
{
    tile_t *tile = malloc(sizeof(tile_t));

    if (tile == NULL)
        return (NULL);
    tile->inventory = new_container();
    return tile;
}

void delete_tile(void *tile)
{
    tile_t *tile_data = (tile_t *)tile;

    if (tile_data == NULL)
        return;
    free(tile_data->inventory);
    free(tile_data);
}
