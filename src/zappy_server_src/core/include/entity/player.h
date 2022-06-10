/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** player
*/

/// \file src/zappy_server/core/include/entity/player.h

#ifndef PLAYER_H
    #define PLAYER_H

    #include "container.h"
    #include "container_manip.h"
    #include <uuid/uuid.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdbool.h>

/// \brief orientation of the player
enum player_orientation_e {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

/// Reprensents a player
typedef struct player_s {
    /// Unique player id
    uuid_t uuid;

    /// The player team
    char* team;

    /// The player level
    unsigned int level;

    /// The player inventory
    container_t *inventory;

    /// The current player orientation, default NORTH
    enum player_orientation_e orientation;
} player_t;

/// \brief Creates a new player and associate it with the given team name
player_t *create_player(char *team_name);

/// \brief Level up the player
bool player_level_up(player_t *player);

/// \brief Updates the player orientation
bool player_set_orientation(player_t *player,
enum player_orientation_e orientation);

/// \brief Delete the player
void delete_player(player_t *player);

#endif /* PLAYER_H */