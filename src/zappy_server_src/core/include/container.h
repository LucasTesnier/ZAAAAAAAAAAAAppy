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
    /// The amount of food inside the container
    unsigned int food;
    /// The amount of linemate inside the container
    unsigned int linemate;
    /// The amount of deraumere inside the container
    unsigned int deraumere;
    /// The amount of sibur inside the container
    unsigned int sibur;
    /// The amount of mendiane inside the container
    unsigned int mendiane;
    /// The amount of phiras inside the container
    unsigned int phiras;
    /// The amount of thystame inside the container
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
