/*
** EPITECH PROJECT, 2022
** Project
** File description:
** broadcast
*/

/// \file src/zappy_server_src/core/include/broadcast.h

#ifndef BROADCAST_H_
    #define BROADCAST_H_

    #include "entity/entity.h"
    #include <stdbool.h>

/// \brief All usefull data for broadcast compute
typedef struct broadcast_data_s {
    /// \brief The case count
    int count;
    /// \brief The total turn count
    int turn_number;
    /// \brief List of direction to take
    enum player_orientation_e *direction_list;
    /// \brief List of movement to apply
    int *movement_list;
    /// \brief Coords of the spiral position
    position_t current_pos;
} broadcast_data_t;

/// \brief Modifify a position by a given direction
/// \param pos The positition to modify
/// \param dir The direction to apply
static inline void broadcast_apply_direction_on_position(position_t *pos,
enum player_orientation_e dir)
{
    if (dir == WEST)
        pos->x -= 1;
    if (dir == SOUTH)
        pos->y -= 1;
    if (dir == EAST)
        pos->x += 1;
    if (dir == NORTH)
        pos->y += 1;
}

/// \brief Get the rest of the directionnal list
/// \param direction_list The directionnal list
static inline void broadcast_get_direction_list_other(
enum player_orientation_e *direction_list)
{
    if (direction_list[0] == SOUTH) {
        direction_list[1] = EAST;
        direction_list[2] = NORTH;
        direction_list[3] = WEST;
        direction_list[4] = SOUTH;
    }
    if (direction_list[0] == WEST) {
        direction_list[1] = SOUTH;
        direction_list[2] = EAST;
        direction_list[3] = NORTH;
        direction_list[4] = WEST;
    }
}

/// \brief Compute the directionnal list for a player broadcast
/// \param orientation The orientation of the player
/// \return enum player_orientation_e* The directionnal list
static inline enum player_orientation_e *broadcast_get_direction_list(
enum player_orientation_e orientation)
{
    enum player_orientation_e *direction_list =
    malloc(sizeof(enum player_orientation_e) * 5);

    if (direction_list == NULL)
        return NULL;
    direction_list[0] = orientation;
    if (orientation == NORTH) {
        direction_list[1] = WEST;
        direction_list[2] = SOUTH;
        direction_list[3] = EAST;
        direction_list[4] = NORTH;
    }
    if (orientation == EAST) {
        direction_list[1] = NORTH;
        direction_list[2] = WEST;
        direction_list[3] = SOUTH;
        direction_list[4] = EAST;
    }
    broadcast_get_direction_list_other(direction_list);
    return direction_list;
}

/// \brief Compute the pos coord into a circular map and compare it
/// to the destination coords
/// \param dest The coord of the destination
/// \param pos The coord of the player
/// \param map_size The map size
/// \return true When pos and dest are at the same coord
/// \return false When pos and dest are not at the same coord
static inline bool resolve_directionnal_position(position_t dest,
position_t pos, position_t map_size)
{
    if (pos.x < 0)
        pos.x = abs(pos.x) % (map_size.x - 1);
    if (pos.x >= map_size.x)
        pos.x = pos.x % (map_size.x - 1);
    if (pos.y < 0)
        pos.y = abs(pos.y) % (map_size.y - 1);
    if (pos.y >= map_size.y)
        pos.y = pos.y % (map_size.y - 1);
    if (pos.x == dest.x && pos.y == dest.y)
        return true;
    return false;
}

/// \brief Get the movement list based on the turn number
/// \param turn_number Number of the actual turn
/// \return int* The movement list
static inline int *get_movement_list(int turn_number)
{
    int *movement_list = malloc(sizeof(int) * 5);

    if (movement_list == NULL)
        return NULL;
    movement_list[0] = 1;
    movement_list[1] = 1 + 2 * (turn_number -1);
    movement_list[2] = 2 * turn_number;
    movement_list[3] = 2 * turn_number;
    movement_list[4] = 2 * turn_number;
    return movement_list;
}

#endif /* !BROADCAST_H_ */
