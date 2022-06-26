/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** entity_diff
*/

/// \file src/zappy_server_src/core/entity/entity_diff.c

#include "entity/entity.h"
#include <stdlib.h>

entity_diff_t *create_entity_diff(size_t initial_size)
{
    entity_diff_t *new_diff = malloc(sizeof(entity_diff_t));

    if (new_diff == NULL)
        return NULL;
    new_diff->diff_size = initial_size;
    new_diff->entities = malloc(sizeof(entity_t *) * initial_size);
    if (new_diff->entities == NULL) {
        free(new_diff);
        return NULL;
    }
    new_diff->offset = 0;
    return new_diff;
}

bool entity_diff_expand_size(entity_diff_t *diff, size_t offset)
{
    size_t new_size = diff->diff_size + offset;

    if (diff == NULL)
        return false;
    diff->entities = realloc(diff->entities, sizeof(entity_t *) * new_size);
    if (diff->entities == NULL)
        return false;
    diff->diff_size = new_size;
    return true;
}

void entity_diff_add_entity(entity_diff_t *diff, entity_t *entity)
{
    if (diff == NULL)
        return;
    if (diff->offset + 1 >= diff->diff_size)
        if (!entity_diff_expand_size(diff, diff->offset + 1))
            return;
    diff->entities[diff->offset++] = entity;
}

void entity_diff_reset(entity_diff_t *diff)
{
    if (diff == NULL)
        return;
    diff->offset = 0;
}

void destroy_entity_diff(entity_diff_t **diff)
{
    if (diff == NULL)
        return;
    free((*diff)->entities);
    free(*diff);
    *diff = NULL;
}
