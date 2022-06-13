/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** container_manips
*/

#ifndef CONTAINER_MANIPS_H
    #define CONTAINER_MANIPS_H

    #define CONTAINER_ADD_FOOD(container, amount) (container)->food += (amount)

    #define CONTAINER_ADD_LINEMATE(container, amount) \
        (container)->linemate += (amount)

    #define CONTAINER_ADD_DERAUMERE(container, amount) \
        (container)->deraumere += (amount)

    #define CONTAINER_ADD_SIBUR(container, amount) \
        (container)->sibur += (amount)

    #define CONTAINER_ADD_MENDIANE(container, amount) \
        (container)->mendiane += (amount)

    #define CONTAINER_ADD_PHIRAS(container, amount) \
        (container)->phiras += (amount)

    #define CONTAINER_ADD_THYSTAME(container, amount) \
        (container)->thystame += (amount)

    #define CONTAINER_REMOVE_FOOD(container, amount) \
        (container)->food -= (amount)

    #define CONTAINER_REMOVE_LINEMATE(container, amount) \
        (container)->linemate -= (amount)

    #define CONTAINER_REMOVE_DERAUMERE(container, amount) \
        (container)->deraumere -= (amount)

    #define CONTAINER_REMOVE_SIBUR(container, amount) \
        (container)->sibur -= (amount)

    #define CONTAINER_REMOVE_MENDIANE(container, amount) \
        (container)->mendiane -= (amount)

    #define CONTAINER_REMOVE_PHIRAS(container, amount) \
        (container)->phiras -= (amount)

    #define CONTAINER_REMOVE_THYSTAME(container, amount) \
        (container)->thystame -= (amount)

#endif /* CONTAINER_MANIPS_H */
