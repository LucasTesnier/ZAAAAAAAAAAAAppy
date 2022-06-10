/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** entity_types
*/

/// \file src/zappy_server/core/include/entity/entity_types.h

#ifndef ENTITY_TYPES_H
    #define ENTITY_TYPES_H

/// Enumerates the different types of entities.
typedef enum entity_type_e {
    ENTITY_PLAYER_TYPE,
    ENTITY_EGG_TYPE,
    ENTITY_TILE_TYPE,

    /// The number of entity types - Keep last
    ENTITY_TYPE_SIZE
} entity_type_t;

#endif /* ENTITY_TYPES_H */
