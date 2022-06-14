/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** pack
*/

/// \file src/zappy_gui_src/Core/Network/pack.h

#ifndef PACK_H_
    #define PACK_H_

    #include "entity.h"
    #include "entity_types.h"
    #include "container.h"
    #include "player.h"
    #include "tile.h"
    #include "egg.h"

/// \brief generic way of packing an int
/// \return a serialized string representing an int
char *pack_int(int val);

/// \brief generic way of packing a string
/// \return a serialized string representing a string
char *pack_str(char *val);

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
