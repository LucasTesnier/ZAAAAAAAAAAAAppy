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

    /// The collection of entities that are presents on the tile
    struct entities_list_s entities;
} tile_t;

/// \brief Create a new tile data
tile_t *create_new_tile(void);

/// \brief Add an entity to a tile
/// \param tile The tile to add the entity to
/// \param entity The entity to add to the tile
/// \return true if the entity was added, false otherwise
/// \warning entity->type must not be ENTITY_TILE_TYPE
bool add_entity_to_tile(tile_t *tile, entity_t *entity);

/// \brief Remove an entity from a tile
/// \param tile The tile to remove the entity from
/// \param uuid The uuid of the entity to remove from the tile
/// \return true if the entity was removed, false otherwise
/// \warning entity->type must not be ENTITY_TILE_TYPE
bool remove_entity_from_tile(tile_t *tile, entity_t *entity);

/// \brief Check if an entity is on a tile
/// \param tile The tile to check
/// \param uuid The uuid of the entity to check
/// \return true if the entity is on the tile, false otherwise
/// \warning entity->type must not be ENTITY_TILE_TYPE
/// \warning entity->id must be set
bool is_entity_on_tile(tile_t *tile, entity_t *entity);

/// \brief Destroy a tile
/// \param tile The tile to destroy
/// \note The entity list is not destroyed
void delete_tile(tile_t *tile);

#endif /* TILE_H */
