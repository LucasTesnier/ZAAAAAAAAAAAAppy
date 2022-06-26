/*
** EPITECH PROJECT, 2022
** Project
** File description:
** entity_diff_remove
*/

/// \file src/zappy_server_src/core/entity/entity_diff_remove.c

#include "entity/entity.h"
#include <stdlib.h>

void entity_diff_remove_entity(entity_diff_t *diff, entity_t *to_remove)
{
    size_t removed = 0;

    if (diff == NULL || to_remove)
        return;
    for (size_t i = 0; i < diff->offset - removed; i++) {
        if (diff->entities[i] == to_remove)
            removed++;
        diff->entities[i] = diff->entities[i + removed];
    }
    diff->offset -= removed;
    if (removed)
        entity_diff_remove_entity(diff, to_remove);
}
