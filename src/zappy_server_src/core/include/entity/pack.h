/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** pack
*/

/// \file src/zappy_server_src/core/include/entity/pack.h

#ifndef PACK_H_
    #define PACK_H_

    #include "entity.h"
    #include "entity_types.h"
    #include "container.h"
    #include "player.h"
    #include "tile.h"
    #include "eggs.h"

/// \brief generic way of packing an int
/// \return a serialized string representing an int
char *pack_int(int val);

/// \brief generic way of packing a string
/// \return a serialized string representing a string
char *pack_str(char *val);

/// \brief get the len of an int
/// \return the len of the string representing the value
int get_int_len(int val);

/// \brief get the len of a container
/// \return the len of the string representing a container
int get_len_container(container_t *cont);

/// \brief get the len of a player
/// \return the len of the string representing a player
int get_len_player(entity_t *ent, player_t *p);

/// \brief get the len of a tile
/// \return the len of the string representing a tile
int get_len_tile(entity_t *ent, tile_t *t);

/// \brief get the len of a egg
/// \return the len of the string representing a egg
int get_len_egg(entity_t *ent, egg_t *t);

/// \brief pack a generic container for an inventory or the content of a tile
/// \return a serialized string representing the inventory
char *pack_container(container_t *cont);

/// \brief pack a player
/// \return a serialized string representing a player
char *pack_player(entity_t *entity);

/// \brief pack a tile
/// \return a serialized string representing a tile
char *pack_tile(entity_t *entity);

/// \brief pack an egg
/// \return a serialized string representing an egg
char *pack_egg(entity_t *entity);

/// \brief pack one entity
/// \return a serialized string representing an entity
char *pack(entity_t *entity);

#endif /* !PACK_H_ */
