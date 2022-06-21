/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** map
*/

/// \file src/zappy_server_src/core/include/map.h

#ifndef MAP_H
    #define MAP_H

    #include "entity/entity.h"


/// Represents the zappy map
typedef struct map_s {
    /// The collection of tiles
    entity_t **tiles;
    /// The width of the map
    int width;
    /// The height of the map
    int height;
} map_t;

/// \brief Creates a new map with the given dimensions
/// \param width The width of the map
/// \param height The height of the map
/// \return The newly created map or NULL if an error occured
map_t *create_new_map(int width, int height);

/// \brief Get a tile from the map given its coordinates
/// \param map The map to get the tile from
/// \param x The x coordinate of the tile
/// \param y The y coordinate of the tile
/// \return The tile at the given coordinates or NULL if an error occured
entity_t* get_tile(map_t *map, int x, int y);

/// \brief Generate new ressources on the map !
/// \param map The map informations
void generate_new_ressource(map_t *map);

/// \brief Utility function to print the map
void display_map(map_t *map);

#endif /* MAP_H */
