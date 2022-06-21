/*
** EPITECH PROJECT, 2022
** Project
** File description:
** look_process
*/

/// \file src/zappy_server_src/core/commands/look_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"
#include "entity/tile.h"

static void look_north(position_t player,
position_t map_size, int lvl, position_t* looked_cases)
{
    position_t tmp = player;

    for (int i = 0; i < lvl; i++) {
        
    }
}

static void look_south(position_t player,
position_t map_size, int lvl, position_t* looked_cases)
{
    tile_t *tile = NULL;
}

static void look_west(position_t player,
position_t map_size, int lvl, position_t* looked_cases)
{
    tile_t *tile = NULL;
}

static void look_east(position_t player,
position_t map_size, int lvl, position_t* looked_cases)
{
    tile_t *tile = NULL;
}

position_t *compute_look_cmd(position_t player, position_t map_size,
int level, enum player_orientation_e orientation)
{
    position_t *looked_cases = malloc(sizeof(position_t) * 2);
    void (*look[])(position_t, position_t, int, position_t*) = {
        look_north, look_south, look_east, look_west
    };

    if (!looked_cases)
        return NULL;
    look[orientation](player, map_size, level, looked_cases);
    return looked_cases;
}