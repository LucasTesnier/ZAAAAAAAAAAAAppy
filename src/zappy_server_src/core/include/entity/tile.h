/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** tile
*/

/// \file src/zappy_server/core/include/entity/tile.h

#ifndef TILE_H
    #define TILE_H

    #include "container.h"
    #include "entity.h"
    #include <sys/queue.h>
    #include <stdlib.h>
    #include <uuid/uuid.h>
    #include <stdbool.h>

/// Represents a tile from the zappy map
typedef struct tile_s {
    /// The tile contents
    container_t *inventory;
} tile_t;

typedef struct incantation_level_s {
    /// \brief required player
    int player;

    /// \brief required linemate
    unsigned int linemate;

    /// \brief required deraumere
    unsigned int deraumere;

    /// \brief required sibur
    unsigned int sibur;

    /// \brief required mendiane
    unsigned int mendiane;

    /// \brief required phiras
    unsigned int phiras;

    /// \brief required thystame
    unsigned int thystame;
} incantation_level_t;

static inline bool comp_inc_lvl_cont(incantation_level_t inc, container_t cont)
{
    if (inc.linemate > cont.linemate)
        return false;
    if (inc.deraumere > cont.deraumere)
        return false;
    if (inc.sibur > cont.sibur)
        return false;
    if (inc.mendiane > cont.mendiane)
        return false;
    if (inc.phiras > cont.phiras)
        return false;
    if (inc.thystame > cont.thystame)
        return false;
    return true;
}

/// \brief Create a new tile data
tile_t *create_new_tile(void);

/// \brief Destroy a tile
/// \param tile The tile to destroy
/// \note The entity list is not destroyed
void delete_tile(void *tile);

#endif /* TILE_H */
