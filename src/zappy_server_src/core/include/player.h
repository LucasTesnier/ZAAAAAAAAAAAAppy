/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** player
*/

#ifndef PLAYER_H
    #define PLAYER_H

    #include "container.h"
    #include "container_manip.h"
    #include <uuid/uuid.h>
    #include <string.h>
    #include <stdlib.h>

/// \brief orientation of the player
enum player_orientation_e{
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

static inline player_t *create_player(char *team_name)
{
    player_t *player = (player_t*)malloc(sizeof(player_t));

    if (!player)
        return NULL;

    memset(player, 0, sizeof(player_t));
    player->team = strdup(team_name);
    player->inventory = new_container();
    CONTAINER_ADD_FOOD(player->inventory, 10);
    player->level = 1;
    uuid_generate(player->uuid);
    return player;
}

#endif /* PLAYER_H */
