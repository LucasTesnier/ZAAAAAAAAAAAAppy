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
#include <sys/param.h>

void resolve_looked_cases(position_t *looked_cases, size_t looked_case_idx,
position_t map_size);

/// \brief Get all the tiles when in front of a player when facing north
/// \param player the player position
/// \param map_size the map size
/// \param looked_cases the collection of cases visited by the look cmd
static void look_north(position_t player,
position_t map_size, int lvl, position_t* looked_cases)
{
    position_t left = (position_t){player.x - 1, player.y - 1};
    position_t right = (position_t){player.x + 1, player.y - 1};
    size_t looked_case_idx = 1;

    for (int i = 1; i <= lvl; i++) {
        for (int j = MIN(left.x, right.x); j <= MAX(left.x, right.x); j++) {
            looked_cases[looked_case_idx++] = (position_t){j, left.y};
        }
        left.x -= 1;
        right.x += 1;
        right.y -= 1;
        left.y -= 1;
    }
    resolve_looked_cases(looked_cases, looked_case_idx, map_size);
}

/// \brief Get all the tiles when in front of a player when facing south
/// \param player the player position
/// \param map_size the map size
/// \param looked_cases the collection of cases visited by the look cmd
static void look_south(position_t player,
position_t map_size, int lvl, position_t* looked_cases)
{
    position_t left = (position_t) {player.x - 1, player.y + 1};
    position_t right = (position_t) {player.x + 1, player.y + 1};
    size_t looked_case_idx = 1;

    for (int i = 1; i <= lvl; i++) {
        for (int j = MIN(left.x, right.x); j < MAX(left.x, right.x); j++) {
            looked_cases[looked_case_idx++] = (position_t) {j, left.y};
        }
        left.x -= 1;
        right.x += 1;
        right.y += 1;
        left.y += 1;
    }
    resolve_looked_cases(looked_cases, looked_case_idx, map_size);
}

/// \brief Get all the tiles when in front of a player when facing west
/// \param player the player position
/// \param map_size the map size
/// \param looked_cases the collection of cases visited by the look cmd
static void look_west(position_t player,
position_t map_size, int lvl, position_t* looked_cases)
{
    position_t left = (position_t) {player.x - 1, player.y - 1};
    position_t right = (position_t) {player.x - 1, player.y + 1};
    size_t looked_case_idx = 1;

    for (int i = 1; i <= lvl; i++) {
        for (int j = MIN(left.x, right.x); j < MAX(left.x, right.x); j++) {
            looked_cases[looked_case_idx++] = (position_t) {j, left.y};
        }
        left.y -= 1;
        right.y += 1;
        right.x -= 1;
        left.x -= 1;
    }
    resolve_looked_cases(looked_cases, looked_case_idx, map_size);
}

/// \brief Get all the tiles when in front of a player when facing east
/// \param player the player position
/// \param map_size the map size
/// \param looked_cases the collection of cases visited by the look cmd
static void look_east(position_t player,
position_t map_size, int lvl, position_t* looked_cases)
{
    position_t left = (position_t) {player.x + 1, player.y - 1};
    position_t right = (position_t) {player.x + 1, player.y + 1};
    size_t looked_case_idx = 1;

    for (int i = 1; i <= lvl; i++) {
        for (int j = MIN(left.x, right.x); j < MAX(left.x, right.x); j++) {
            looked_cases[looked_case_idx++] = (position_t) {j, left.y};
        }
        left.y -= 1;
        right.y += 1;
        right.x += 1;
        left.x += 1;
    }
    resolve_looked_cases(looked_cases, looked_case_idx, map_size);
}

position_t *compute_look_cmd(position_t player, position_t map_size,
int level, enum player_orientation_e orientation)
{
    position_t *looked_cases = NULL;
    size_t looked_cases_size = 1;
    void (*look[])(position_t, position_t, int, position_t*) = {
        look_north, look_south, look_east, look_west
    };
    for (int i = 1; i <= level; i++)
        looked_cases_size += 3 + ((i - 1) * 2);
    looked_cases_size++;
    looked_cases = malloc(sizeof(position_t) * looked_cases_size);
    if (!looked_cases)
        return NULL;
    looked_cases[0] = player;
    looked_cases[looked_cases_size - 1] = (position_t){-1, -1};
    look[orientation](player, map_size, level, looked_cases);
    return looked_cases;
}
