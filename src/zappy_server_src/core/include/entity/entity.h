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
    #include <uuid/uuid.h>

/// Represents a generic position in the game
typedef struct position_s {
    /// x
    int x;
    /// y
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

/// Entity wrapper used at the top level
typedef struct entity_wrapper_s {
    /// The players list
    struct entities_list_s players;
    /// The eggs list
    struct entities_list_s eggs;
    /// The tiles list
    struct entities_list_s tiles;
} entity_wrapper_t;

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

/// \brief Delete and entity
/// \param entity the entity to delete
/// \note This function deletes the entity data
void delete_entity(entity_t *entity);

/// \brief Create a new entity wrapper
/// \return a new entity wrapper or NULL if it failed
entity_wrapper_t *create_entity_wrapper(void);

/// \brief Delete an entity wrapper
/// \param wrapper the entity wrapper to delete
void delete_entity_wrapper(entity_wrapper_t *wrapper);

/// \brief Create a new player and adds to the collection of players
/// \param wrapper the entity wrapper to add the player to
/// \param position the player position
/// \param team_name the player team_name
void entity_wrapper_create_player(entity_wrapper_t *wrapper, position_t pos,
const char *team_name);

/// \brief Add a previously created player entity to the collection of entity
/// \param wrapper the entity wrapper to add the player to
/// \param entity the player entity to add
void entity_wrapper_add_player(entity_wrapper_t *wrapper, entity_t *player);

/// \brief Create a new egg and adds to the collection of eggs
/// \param wrapper the entity wrapper to add the egg to
/// \param position the egg position
/// \param team_name the egg team_name
/// \return uuid_t * The uuid of the created egg
uuid_t *entity_wrapper_create_egg(entity_wrapper_t *wrapper, position_t pos,
const char *team_name);

/// \brief Add a previously created egg entity to the collection of entity
/// \param wrapper the entity wrapper to add the egg to
/// \param entity the egg entity to add
void entity_wrapper_add_egg(entity_wrapper_t *wrapper, entity_t *egg);

/// \brief Create a new tile and adds to the collection of tiles
/// \param wrapper the entity wrapper to add the tile to
/// \param position the tile position
void entity_wrapper_create_tile(entity_wrapper_t *wrapper, position_t pos);

/// \brief Remove an entity from the collection
/// \param wrapper the entity wrapper to remove the entity from
/// \param entity the entity to remove
void entity_wrapper_remove_entity(entity_wrapper_t *wrapper, entity_t *entity);

#endif /* ENTITY_H */
