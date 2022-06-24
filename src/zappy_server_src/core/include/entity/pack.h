/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** pack_entity
*/

/// \file src/zappy_server_src/core/include/entity/pack_entity.h

#ifndef PACK_H_
    #define PACK_H_

    #include "entity.h"
    #include "entity_types.h"
    #include "container.h"
    #include "player.h"
    #include "tile.h"
    #include "eggs.h"

    /// \brief size to malloc for a packed container
    #define CONT_SIZE 18

    /// \brief size to malloc for a packed player
    #define PLAYER_SIZE 71

    /// \brief size to malloc for a packed tile
    #define TILE_SIZE 26

    /// \brief size to malloc for a packed egg
    #define EGG_SIZE 50

/// \brief generic way of packing an int
/// \param val value to pack_entity
/// \return a serialized string representing an int
char *pack_int(int val);

/// \brief generic way of packing a string
/// \param val value to pack_entity
/// \return a serialized string representing a string
char *pack_str(char *val);

/// \brief get the len of an int
/// \param val value to get len
/// \return the len of the string representing the value
int get_int_len(int val);

/// \brief get the len of a container
/// \param cont container to get len
/// \return the len of the string representing a container
int get_len_container(container_t *cont);

/// \brief get the len of a player
/// \param ent entity to get len
/// \param p player to get len
/// \return the len of the string representing a player
int get_len_player(entity_t *ent, player_t *p);

/// \brief get the len of a tile
/// \param ent entity to get len
/// \param t tile to get len
/// \return the len of the string representing a tile
int get_len_tile(entity_t *ent, tile_t *t);

/// \brief get the len of a egg
/// \param ent entity to get len
/// \param t egg to get len
/// \return the len of the string representing a egg
int get_len_egg(entity_t *ent, egg_t *t);

/// \brief pack_entity a generic container for an inventory or the content of a tile
/// \param cont container to pack_entity
/// \return a serialized string representing the inventory
char *pack_container(container_t *cont);

/// \brief pack_entity a player
/// \param entity entity containing the player to pack_entity
/// \return a serialized string representing a player
char *pack_player(entity_t *entity);

/// \brief pack_entity a tile
/// \param entity entity containing the tile to pack_entity
/// \return a serialized string representing a tile
char *pack_tile(entity_t *entity);

/// \brief pack_entity an egg
/// \param entity entity containing the egg to pack_entity
/// \return a serialized string representing an egg
char *pack_egg(entity_t *entity);

/// \brief pack_entity one entity
/// \param entity entity to pack_entity
/// \return a serialized string representing an entity
char *pack_entity(entity_t *entity);

#endif /* !PACK_H_ */
