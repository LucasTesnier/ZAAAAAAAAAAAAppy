/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** look_utils
*/

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"
#include "entity/tile.h"
#include <sys/param.h>

/// \brief Utility function to convert overflown
/// position into a map bounded pos
/// \param looked_cases The collection of cases visited by the look cmd
/// \param looked_case_idx The collection size
void resolve_looked_cases(position_t *looked_cases, size_t looked_case_idx,
position_t map_size)
{
    for (size_t i = 0; i < looked_case_idx; i++) {
        if (looked_cases[i].x < 0)
            looked_cases[i].x = (map_size.x == 1) ? 0 : map_size.x -
            (abs(looked_cases[i].x) % (map_size.x));
        if (looked_cases[i].x >= map_size.x)
            looked_cases[i].x = (map_size.x == 1) ? 0 : looked_cases[i].x
            % (map_size.x);
        if (looked_cases[i].y < 0)
            looked_cases[i].y = (map_size.y == 1) ? 0 : map_size.y -
            (abs(looked_cases[i].y) % (map_size.y));
        if (looked_cases[i].y >= map_size.y)
            looked_cases[i].y = (map_size.y == 1) ? 0 : looked_cases[i].y
            % (map_size.y);
    }
}

int get_look_case_total_size(container_t *cases)
{
    int res = 0;
    int convenance_entity = 1000;

    res += strlen("food ") * cases->food;
    res += strlen("linemate ") * cases->linemate;
    res += strlen("deraumere ") * cases->deraumere;
    res += strlen("sibur ") * cases->sibur;
    res += strlen("mendiane ") * cases->mendiane;
    res += strlen("phiras ") * cases->phiras;
    res += strlen("thystame ") * cases->thystame;
    res += convenance_entity;
    return res;
}
