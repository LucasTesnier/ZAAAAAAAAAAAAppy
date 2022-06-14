/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** pack
*/

/// \file src/zappy_gui_src/pack.h

#ifndef PACK_H_
    #define PACK_H_

    #include "entity.h"
    #include "entity_types.h"
    #include "container.h"
    #include "player.h"
    #include "tile.h"
    #include "egg.h"

/// \brief pack a generic container for an inventory or the content of a tile
/// \return a serialized string representating the inventory
char *pack_container(container_t *cont);

/// \brief pack a player
/// \return a serialized string representating a player
char *pack_player(entity_t *entity);

/// \brief pack a tile
/// \return a serialized string representating a tile
char *pack_tile(entity_t *entity);

/// \brief pack an egg
/// \return a serialized string representating an egg
char *pack_egg(entity_t *entity);

/// \brief pack one entity
/// \return a serialized string representating an entity
char *pack(entity_t *entity);

#endif /* !PACK_H_ */
