/*
** EPITECH PROJECT, 2022
** Project
** File description:
** forward_command
*/

/// \file src/zappy_server_src/core/commands/forward_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"
#include "entity/tile.h"

/// \brief Move an entity to a given direction
/// \param player Entity informations
/// \param map Map informations
static void move_x(entity_t *player, map_t *map)
{
    position_t *pos = &player->position;
    player_t *player_data = (player_t *)player->data;
    tile_t *tile = NULL;

    tile = (tile_t*)get_tile(map, pos->x, pos->y)->data;
    if (player_data->orientation == NORTH)
        pos->x = (pos->x - 1) % map->height;
    else
        pos->x = (pos->x + 1) % map->height;
    remove_entity_from_tile(tile, player);
    tile = (tile_t*)get_tile(map, pos->x, pos->y)->data;
    add_entity_to_tile(tile, player);
}

/// \brief Move an entity to a given direction
/// \param player Entity informations
/// \param map Map informations
static void move_y(entity_t *player, map_t *map)
{
    position_t *pos = &player->position;
    player_t *player_data = (player_t *)player->data;
    tile_t *tile = NULL;

    tile = (tile_t*)get_tile(map, pos->x, pos->y)->data;
    if (player_data->orientation == EAST)
        pos->x = (pos->y + 1) % map->height;
    else
        pos->x = (pos->y - 1) % map->height;
    remove_entity_from_tile(tile, player);
    tile = (tile_t*)get_tile(map, pos->x, pos->y);
    add_entity_to_tile(tile, player);
}

bool command_forward(char *arg, player_list_t *player, server_data_t *serv)
{
    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    if (!scheduler_schedule_event(serv->scheduler,
    ((player_t *)player->player_data->data)->uuid, 7))
        return false;
    player->scheduled_action = find_ai_command_end("/forward", NULL);
    if (player->scheduled_action == NULL)
        return false;
    return true;
}

bool command_forward_end(char *arg, player_list_t *player,
server_data_t *serv)
{
    entity_t *player_entity = NULL;
    player_t *player_data = NULL;

    (void) arg;
    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    player_entity = (entity_t *)player->player_data;
    player_data = (player_t *)player_entity->data;
    if (player_data->orientation == NORTH || player_data->orientation == SOUTH)
        move_x(player_entity, serv->map);
    else
        move_y(player_entity, serv->map);
    send_entities_list_info(serv);
    pop_message(player->player_peer);
    return print_retcode(213, NULL, player->player_peer, true);
}