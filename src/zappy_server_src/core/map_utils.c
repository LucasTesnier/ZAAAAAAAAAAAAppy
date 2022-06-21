/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** map_utils
*/

#include "map.h"
#include "entity/entity.h"
#include "entity/player.h"
#include "entity/eggs.h"
#include "entity/tile.h"
#include <uuid/uuid.h>
#include <stdio.h>

/// \brief Display the content of a tile on the console
/// \param tile Tile to display
/// \param x X position of the tile
/// \param y Y position of the tile
static void display_tile(tile_t *tile, int x, int y)
{
    entity_t *player_entity = NULL;
    player_t *player_entity_data = NULL;
    char *uuid_repr = malloc(sizeof(char) * 37);

    printf("============Printing tile at %d %d==============\n",
        x, y);
    printf("||\t Food : %d\t||\n", tile->inventory->food);
    printf("||\t Linemate : %d\t||\n", tile->inventory->linemate);
    printf("||\t Deraumere : %d\t||\n", tile->inventory->deraumere);
    printf("||\t Sibur : %d\t||\n", tile->inventory->sibur);
    printf("||\t Mendiane : %d\t||\n", tile->inventory->mendiane);
    printf("||\t Phiras : %d\t||\n", tile->inventory->phiras);
    printf("||\t Thystame : %d\t||\n", tile->inventory->thystame);
    TAILQ_FOREACH(player_entity, &tile->entities, entities) {
        player_entity_data = (player_t *)player_entity->data;
        uuid_unparse(player_entity_data->uuid, uuid_repr);
        printf("||\t Player : %s\t||\n", uuid_repr);
    }
    printf("================================================\n");
    free(uuid_repr);
}

void display_map(map_t *map)
{
    for (int i = 0 ; i < map->height ; i++) {
        for (int j = 0 ; j < map->width ; j++) {
            display_tile((tile_t *)map->tiles[i * map->width + j]->data,
                j, i);
        }
    }
}