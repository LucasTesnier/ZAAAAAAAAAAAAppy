/*
** EPITECH PROJECT, 2022
** Project
** File description:
** eject_process
*/

/// \file src/zappy_server_src/core/commands/eject_process.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"
#include "entity/tile.h"

int get_eject_dir(server_data_t *serv, entity_t *entity, position_t old)
{
    return get_directionnal_value(entity->position, (position_t) {
    serv->map->width, serv->map->height}, old,
    ((player_t *)entity)->orientation);
}