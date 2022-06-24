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

/// \brief Generic type for items storage
typedef struct container_s {
    /// \brief The amount of food inside the container
    int food;
    /// \brief The amount of linemate inside the container
    unsigned int linemate;
    /// \brief The amount of deraumere inside the container
    unsigned int deraumere;
    /// \brief The amount of sibur inside the container
    unsigned int sibur;
    /// \brief The amount of mendiane inside the container
    unsigned int mendiane;
    /// \brief The amount of phiras inside the container
    unsigned int phiras;
    /// \brief The amount of thystame inside the container
    unsigned int thystame;
} container_t;

/// \brief Generate data
typedef struct generate_s {
    /// \brief Name of the ressource
    char *name;

    /// \brief Density of the ressource
    float density;
} generate_t;

/// \brief Create a new container and initialize it with 0
/// \return a new container or NULL if it failed
container_t *new_container(void);

/// \brief Display a container
void debug_display_container(container_t *container);

/// \brief Destroy a container
void delete_container(container_t *container);

/// \brief Get the string representation of a container
/// \return a string representation of the container or NULL if it failed
char *pack_inventory(container_t *inv);

#endif /* CONTAINER_H */
