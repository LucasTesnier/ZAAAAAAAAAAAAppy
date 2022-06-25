/*
** EPITECH PROJECT, 2022
** Project
** File description:
** remove_inventory
*/

/// \file src/zappy_server_src/core/include/remove_inventory.h

#ifndef REMOVE_INVENTORY_H
    #define REMOVE_INVENTORY_H

    #include "entity/entity.h"

/// \brief Remove minimum ressource in the inventory for rare ressource
/// \param inventory The inventory where the data is removed
/// \param to_remove The container where the removing quantity is stored
static inline void remove_min_from_inventory_rare_ressource(
container_t *inventory, container_t *to_remove)
{
    unsigned temp = 0;

    if (inventory->mendiane < to_remove->mendiane) {
        temp = inventory->mendiane;
        inventory->mendiane -= inventory->mendiane;
        to_remove->mendiane -= temp;
    }
    if (inventory->phiras < to_remove->phiras) {
        temp = inventory->phiras;
        inventory->phiras -= inventory->phiras;
        to_remove->phiras -= temp;
    }
    if (inventory->thystame < to_remove->thystame) {
        temp = inventory->thystame;
        inventory->thystame -= inventory->thystame;
        to_remove->thystame -= temp;
    }
}

/// \brief Remove minimum ressource in the inventory
/// \param inventory The inventory where the data is removed
/// \param to_remove The container where the removing quantity is stored
static inline void remove_min_from_inventory(container_t *inventory,
container_t *to_remove)
{
    unsigned temp = 0;

    if (inventory->linemate < to_remove->linemate) {
        temp = inventory->linemate;
        inventory->linemate -= inventory->linemate;
        to_remove->linemate -= temp;
    }
    if (inventory->deraumere < to_remove->deraumere) {
        temp = inventory->deraumere;
        inventory->deraumere -= inventory->deraumere;
        to_remove->deraumere -= temp;
    }
    if (inventory->sibur < to_remove->sibur) {
        temp = inventory->sibur;
        inventory->sibur -= inventory->sibur;
        to_remove->sibur -= temp;
    }
    remove_min_from_inventory_rare_ressource(inventory, to_remove);
}

/// \brief Remove maxium ressource in the inventory for the rare ressource
/// \param inventory The inventory where the data is removed
/// \param to_remove The container where the removing quantity is stored
static inline void remove_max_from_inventory_rare_ressource(
container_t *inventory, container_t *to_remove)
{
    if (inventory->phiras >= to_remove->phiras) {
        inventory->phiras -= to_remove->phiras;
        to_remove->phiras = 0;
    }
    if (inventory->thystame >= to_remove->thystame) {
        inventory->thystame -= to_remove->thystame;
        to_remove->thystame = 0;
    }
}

/// \brief Remove maxium ressource in the inventory
/// \param inventory The inventory where the data is removed
/// \param to_remove The container where the removing quantity is stored
static inline void remove_max_from_inventory(container_t *inventory,
container_t *to_remove)
{
    if (inventory->linemate >= to_remove->linemate) {
        inventory->linemate -= to_remove->linemate;
        to_remove->linemate = 0;
    }
    if (inventory->deraumere >= to_remove->deraumere) {
        inventory->deraumere -= to_remove->deraumere;
        to_remove->deraumere = 0;
    }
    if (inventory->sibur >= to_remove->sibur) {
        inventory->sibur -= to_remove->sibur;
        to_remove->sibur = 0;
    }
    if (inventory->mendiane >= to_remove->mendiane) {
        inventory->mendiane -= to_remove->mendiane;
        to_remove->mendiane = 0;
    }
    remove_max_from_inventory_rare_ressource(inventory, to_remove);
    remove_min_from_inventory(inventory, to_remove);
}

#endif /* !INCANTATION_H_ */
