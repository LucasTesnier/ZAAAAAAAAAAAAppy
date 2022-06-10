/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** entity
*/

#ifndef ENTITY_H
    #define ENTITY_H

    #include "entity_types.h"
    #include "sys/queue.h"

/// Represents a generic position in the game
typedef struct position_s {
    int x;
    int y;
} position_t;

/// Represents a generic entity
typedef struct entity_s {
    /// The entity type, defined in \file entity_types.h
    unsigned int type;

    /// The position of the entity
    position_t position;

    /// Entity specific data
    void *data;

    /// Entity collection
    TAILQ_ENTRY(entity_s) entities;
} entity_t;

/// Entity list head
TAILQ_HEAD(entities_list_s, entity_s);

#endif /* ENTITY_H */
