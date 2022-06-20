/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** entity_wrapper
*/

/// \file src/zappy_server/core/entity/entity_wrapper.c

#include "entity/entity.h"
#include "entity/entity_types.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

entity_wrapper_t *create_entity_wrapper(void)
{
    entity_wrapper_t *wrapper = malloc(sizeof(entity_wrapper_t));

    if (!wrapper)
        return NULL;
    memset(wrapper, 0, sizeof(entity_wrapper_t));
    TAILQ_INIT(&wrapper->players);
    TAILQ_INIT(&wrapper->eggs);
    TAILQ_INIT(&wrapper->tiles);
    return wrapper;
}

static void delete_entities_list(struct entities_list_s* entity_list)
{
    entity_t *entity = NULL;
    entity_t *tmp = NULL;

    entity = TAILQ_FIRST(entity_list);
    while (entity != NULL) {
        tmp = TAILQ_NEXT(entity , entities);
        delete_entity(entity);
        entity = tmp;
    }
}

void delete_entity_wrapper(entity_wrapper_t *wrapper)
{
    if (!wrapper)
        return;
    printf("=============Deleting all entities=============\n");
    delete_entities_list(&wrapper->players);
    delete_entities_list(&wrapper->eggs);
    delete_entities_list(&wrapper->tiles);
    free(wrapper);
    printf("===============================================\n");
}
