/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** container
*/

/// \file src/zappy_server/core/include/container.h

#ifndef CONTAINER_H
    #define CONTAINER_H

    #include <stdlib.h>
    #include <string.h>

/// Generic type for items storage
typedef struct container_s {
    unsigned int food;
    unsigned int linemate;
    unsigned int deraumere;
    unsigned int sibur;
    unsigned int mendiane;
    unsigned int phiras;
    unsigned int thystame;
} container_t;

/// \brief Create a new container and initialize it with 0
/// \return a new container or NULL if it failed
container_t *new_container(void);

/// \brief Display a container
void debug_display_container(container_t *container);

/// \brief Destroy a container
void delete_container(container_t *container);

#endif /* CONTAINER_H */
