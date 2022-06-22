/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** fork_utils
*/

/// \file src/zapper_server_src/core/commands/broadcast_command.c

#include "command_hold.h"
#include "entity/player.h"
#include "entity/eggs.h"
#include "entity/tile.h"

void manage_forked_egg(entity_t *player_entity, server_data_t *serv)
{
    entity_t *egg_entity = NULL;
    egg_t *egg_data = NULL;
    player_t *player_data = NULL;
    entity_t *tile_entity = NULL;

    player_data = (player_t *)player_entity->data;
    egg_entity = entity_wrapper_create_egg(serv->entities,
        player_entity->position, player_data->team);
    egg_data = (egg_t*)egg_entity->data;
    scheduler_schedule_event(serv->scheduler, egg_data->id, 20);
    tile_entity = get_tile(serv->map, player_entity->position.x,
        player_entity->position.y);
    if (!tile_entity)
        return;
}
