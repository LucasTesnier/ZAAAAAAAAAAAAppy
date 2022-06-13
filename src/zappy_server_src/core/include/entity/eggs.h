/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** eggs
*/

/// \file src/zappy_server/core/include/entity/eggs.h

#ifndef EGGS_H
    #define EGGS_H

    #include <uuid/uuid.h>
    #include <string.h>

/// \brief Represents an egg that will hatch after a given time
typedef struct egg_s {
    /// The egg id
    uuid_t id;

    /// The egg team
    const char *team_name;
} egg_t;

/// \brief Creates a new egg with the given team name
/// \param team_name the team of the egg
egg_t *create_new_egg(const char *team_name);

/// \brief Delete an egg
/// \param egg the egg to delete
void delete_egg(egg_t *egg);

#endif /* EGGS_H */
