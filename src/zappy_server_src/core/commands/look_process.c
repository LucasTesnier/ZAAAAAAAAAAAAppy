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

position_t *compute_the_looked_case(position_t player, position_t map_size,
int level, enum player_orientation_e orientation)
{
    position_t *looked_case = malloc(sizeof(position_t) * 2);

    if (!looked_case)
        return NULL;
    looked_case[0] = (position_t) {player.x, player.y};
    looked_case[1] = (position_t) {-1, -1};
    (void) player;
    (void) map_size;
    (void) level;
    (void) orientation;
    return looked_case;
}