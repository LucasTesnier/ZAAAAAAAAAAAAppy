/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** entity_wrapper
*/

/// \file src/zappy_server/core/include/entity/entity_wrapper.c

#include "entity/entity.h"
#include "entity/entity_types.h"
#include <stdlib.h>
#include <string.h>

entity_wrapper_t *create_entity_wrapper(void)
{
    entity_wrapper_t *wrapper = malloc(sizeof(entity_wrapper_t));

    if (!wrapper)
        return NULL;
    memset(wrapper, 0, sizeof(entity_wrapper_t));
    TAILQ_INIT(wrapper->players);
    TAILQ_INIT(wrapper->eggs);
    TAILQ_INIT(wrapper->tiles);
    return wrapper;
}

void delete_entity_wrapper(entity_wrapper_t *wrapper)
{
    entity_t *entity;

    if (!wrapper)
        return;
    while (!TAILQ_EMPTY(wrapper->players)) {
        entity = TAILQ_FIRST(wrapper->players);
        TAILQ_REMOVE(wrapper->players, entity, entities);
        delete_entity(entity);
    }
    while (!TAILQ_EMPTY(wrapper->eggs)) {
        entity = TAILQ_FIRST(wrapper->eggs);
        TAILQ_REMOVE(wrapper->eggs, entity, entities);
        delete_entity(entity);
    }
    while (!TAILQ_EMPTY(wrapper->tiles)) {
        entity = TAILQ_FIRST(wrapper->tiles);
        TAILQ_REMOVE(wrapper->tiles, entity, entities);
        delete_entity(entity);
    }
    free(wrapper);
}
