/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** entity
*/

#include "entity/entity.h"
#include <stdbool.h>
#include <stdlib.h>

entity_t *create_entity(unsigned int type, position_t position)
{
    entity_t *entity = malloc(sizeof(entity_t));

    if (entity == NULL)
        return (NULL);
    entity->type = type;
    entity->position = position;
    entity->data = NULL;
    return entity;
}

bool entity_set_data(entity_t *entity, void *data)
{
    if (entity == NULL)
        return false;
    entity->data = data;
    return true;
}
