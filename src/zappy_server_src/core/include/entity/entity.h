/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** entity
*/

/// \file src/zappy_server_src/core/include/entity/entity.h

#ifndef ENTITY_H
    #define ENTITY_H

    #include "entity_types.h"
    #include "sys/queue.h"
    #include <stdbool.h>

/// Represents a generic position in the game
typedef struct position_s {
    int x;
    int y;
} position_t;

/// Represents a generic entity
typedef struct entity_s {
    /// The entity type, defined in \file entity_types.h
    entity_type_t type;

    /// The position of the entity
    position_t position;

    /// Entity specific data
    void *data;

    /// Entity collection
    TAILQ_ENTRY(entity_s) entities;
} entity_t;

/// Entity list head
TAILQ_HEAD(entities_list_s, entity_s);

/// \brief Create a new entity
/// \param type the entity typ
/// \param position the entity position
/// \return a new entity or NULL if it failed
entity_t *create_entity(unsigned int type, position_t position);

/// \brief Sets the entity data
/// \param entity the entity
/// \param data the entity data
/// \return true if it succeeded, false otherwise
bool entity_set_data(entity_t *entity, void *data);

#endif /* ENTITY_H */
