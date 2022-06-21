/*
** EPITECH PROJECT, 2022
** Project
** File description:
** eject_command
*/

/// \file src/zappy_server_src/core/commands/eject_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"
#include "entity/tile.h"

bool command_eject(char *arg, player_list_t *player, server_data_t *serv)
{
    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    if (!scheduler_schedule_event(serv->scheduler,
    ((player_t *)player->player_data->data)->uuid, 7))
        return false;
    player->scheduled_action = find_ai_command_end("/eject", NULL);
    if (player->scheduled_action == NULL)
        return false;
    return true;
}

/// \brief Move an entity to a given direction
/// \param player Entity informations
/// \param map Map informations
/// \param dir Direction to go
static void move_x(entity_t *player, map_t *map,
enum player_orientation_e dir)
{
    position_t *pos = &player->position;
    tile_t *tile = NULL;

    tile = (tile_t*)get_tile(map, pos->x, pos->y)->data;
    if (dir == NORTH)
        pos->x = (pos->x - 1) % (map->height - 1);
    else
        pos->x = (pos->x - 1) < 0 ? map->height - 1 :
            (pos->x - 1) % (map->height - 1);
    remove_entity_from_tile(tile, player);
    tile = (tile_t*)get_tile(map, pos->x, pos->y)->data;
    add_entity_to_tile(tile, player);
}

/// \brief Move an entity to a given direction
/// \param player Entity informations
/// \param map Map informations
/// \param dir Direction to go
static void move_y(entity_t *player, map_t *map,
enum player_orientation_e dir)
{
    position_t *pos = &player->position;
    tile_t *tile = NULL;

    tile = (tile_t*)get_tile(map, pos->x, pos->y)->data;
    if (dir == EAST)
        pos->x = (pos->y + 1) % (map->height - 1);
    else
        pos->x = (pos->y - 1) < 0 ? (map->height - 1)
            : (pos->y - 1) % (map->height - 1);
    remove_entity_from_tile(tile, player);
    tile = (tile_t*)get_tile(map, pos->x, pos->y);
    add_entity_to_tile(tile, player);
}

/// \brief Cross all the entities on the tile and push them
/// \param serv Server information
/// \param player Player informations
/// \param tile Tile informations
static void eject_action(server_data_t *serv, player_t *player, tile_t *tile)
{
    entity_t *entity = NULL;
    player_t *tmp = NULL;

    TAILQ_FOREACH(entity, &tile->entities, entities) {
        if (entity->type != ENTITY_PLAYER_TYPE)
            continue;
        tmp = (player_t *)entity->data;
        if (!uuid_compare(tmp->uuid, player->uuid))
            continue;
        if (player->orientation == NORTH)
            move_x(entity, serv->map, NORTH);
        if (player->orientation == SOUTH)
            move_x(entity, serv->map, SOUTH);
        if (player->orientation == EAST)
            move_y(entity, serv->map, EAST);
        if (player->orientation == WEST)
            move_y(entity, serv->map, WEST);
        send_unexpected_eject(player->orientation, serv, tmp);
    }
}

bool command_eject_end(char *arg, player_list_t *player,
server_data_t *serv)
{
    entity_t *player_entity = NULL;
    player_t *player_data = NULL;
    tile_t *tile = NULL;

    (void) serv;
    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    player_entity = (entity_t *)player->player_data;
    player_data = (player_t *)player_entity->data;
    tile = (tile_t *)get_tile(serv->map,
    player_entity->position.x, player_entity->position.y)->data;
    eject_action(serv, player_data, tile);
    send_entities_list_info(serv);
    pop_message(player->player_peer);
    return print_retcode(219, NULL, player->player_peer, true);
}