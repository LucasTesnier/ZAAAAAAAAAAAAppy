/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** container_manips
*/

/// \file src/zappy_server/core/include/container_manip.h

#ifndef CONTAINER_MANIPS_H
    #define CONTAINER_MANIPS_H

    /// Add food to a container
    #define CONTAINER_ADD_FOOD(container, amount) (container)->food += (amount)

    /// Add linemate to a container
    #define CONTAINER_ADD_LINEMATE(container, amount) \
        (container)->linemate += (amount)

    /// Add deraumere to a container
    #define CONTAINER_ADD_DERAUMERE(container, amount) \
        (container)->deraumere += (amount)

    /// Add sibur to a container
    #define CONTAINER_ADD_SIBUR(container, amount) \
        (container)->sibur += (amount)

    /// Add mendiane to a container
    #define CONTAINER_ADD_MENDIANE(container, amount) \
        (container)->mendiane += (amount)

    /// Add phiras to a container
    #define CONTAINER_ADD_PHIRAS(container, amount) \
        (container)->phiras += (amount)

    /// Add thystame to a container
    #define CONTAINER_ADD_THYSTAME(container, amount) \
        (container)->thystame += (amount)

    /// Remove food from a container
    #define CONTAINER_REMOVE_FOOD(container, amount) \
        (container)->food -= (amount)

    /// Remove linemate from a container
    #define CONTAINER_REMOVE_LINEMATE(container, amount) \
        (container)->linemate -= (amount)

    /// Remove deraumere from a container
    #define CONTAINER_REMOVE_DERAUMERE(container, amount) \
        (container)->deraumere -= (amount)

    /// Remove sibur from a container
    #define CONTAINER_REMOVE_SIBUR(container, amount) \
        (container)->sibur -= (amount)

    /// Remove mendiane from a container
    #define CONTAINER_REMOVE_MENDIANE(container, amount) \
        (container)->mendiane -= (amount)

    /// Remove phiras from a container
    #define CONTAINER_REMOVE_PHIRAS(container, amount) \
        (container)->phiras -= (amount)

    /// Remove thystame from a container
    #define CONTAINER_REMOVE_THYSTAME(container, amount) \
        (container)->thystame -= (amount)

#endif /* CONTAINER_MANIPS_H */
