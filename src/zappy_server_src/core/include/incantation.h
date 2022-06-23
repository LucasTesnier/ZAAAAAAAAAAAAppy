/*
** EPITECH PROJECT, 2022
** Project
** File description:
** incantation
*/

#ifndef INCANTATION_H_
    #define INCANTATION_H_

    #include "remove_inventory.h"

/// \file src/zappy_server_src/core/include/incantation.h

/// \brief Check if th given inventory is empty
/// \param inventory The inventory to inspect
/// \return true When inventory is empty
/// \return false When inventory is not empty
static inline bool inventory_is_empty(container_t inventory)
{
    if (inventory.linemate > 0)
        return false;
    if (inventory.deraumere > 0)
        return false;
    if (inventory.sibur > 0)
        return false;
    if (inventory.mendiane > 0)
        return false;
    if (inventory.phiras > 0)
        return false;
    if (inventory.thystame > 0)
        return false;
    return true;
}

/// \brief Cross all the player and choose player to remove ressource for inc
/// \param wrapper The wrapper of all entities
/// \param player_pos The position of the incantation
/// \param to_remove The container where the removing quantity is stored
/// \param level The player level for incantation
static inline void remove_ressource_randomly(entity_wrapper_t *wrapper,
position_t player_pos, container_t to_remove, unsigned int level)
{
    entity_t *entity = NULL;

    TAILQ_FOREACH(entity, &wrapper->players, entities) {
        if (entity->position.x != player_pos.x &&
        entity->position.y != player_pos.y)
            continue;
        if (((player_t *)entity->data)->level < level)
            continue;
        remove_max_from_inventory(((player_t *)entity->data)->inventory,
        &to_remove);
        if (inventory_is_empty(to_remove))
            break;
    }
}

#endif /* !INVENTORY_H_ */
