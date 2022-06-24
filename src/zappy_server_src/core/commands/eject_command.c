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
/// \param player Entity information's
/// \param map Map information's
/// \param dir Direction to go
static void move_x(entity_t *player, map_t *map,
enum player_orientation_e dir)
{
    position_t *pos = &player->position;

    if (dir == NORTH)
        pos->x = (map->width == 1) ? 0 : (pos->x - 1) % (map->width - 1);
    else
        pos->x = (pos->x - 1) < 0 ? map->width - 1 :
            (pos->x - 1) % (map->width - 1);
}

/// \brief Move an entity to a given direction
/// \param player Entity information's
/// \param map Map information's
/// \param dir Direction to go
static void move_y(entity_t *player, map_t *map,
enum player_orientation_e dir)
{
    position_t *pos = &player->position;
    if (dir == EAST)
        pos->x = (map->height == 1) ? 0 : (pos->y + 1) % (map->height - 1);
    else
        pos->x = (pos->y - 1) < 0 ? (map->height - 1)
            : (pos->y - 1) % (map->height - 1);
}

/// \brief Cross all the entities on the tile_pos and push them
/// \param serv Server information
/// \param player Player information's
/// \param tile_pos Tile information's
static void eject_action(server_data_t *serv, player_t *player,
position_t tile_pos)
{
    entity_t *entity = NULL;

    TAILQ_FOREACH(entity, &serv->entities->players, entities) {
        if (entity->position.x != tile_pos.x
            && entity->position.y != tile_pos.y)
            continue;
        if (!uuid_compare(((player_t *)entity->data)->uuid, player->uuid))
            continue;
        if (player->orientation == NORTH)
            move_x(entity, serv->map, NORTH);
        if (player->orientation == SOUTH)
            move_x(entity, serv->map, SOUTH);
        if (player->orientation == EAST)
            move_y(entity, serv->map, EAST);
        if (player->orientation == WEST)
            move_y(entity, serv->map, WEST);
        send_unexpected_eject(get_eject_dir(serv, entity, tile_pos), serv,
            (player_t *)entity->data);
        entity_diff_add_entity(serv->modified_entities, entity);
    }
}

bool command_eject_end(char *arg, player_list_t *player,
server_data_t *serv __attribute__((unused)))
{
    entity_t *player_entity = NULL;
    player_t *player_data = NULL;

    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    player_entity = (entity_t *)player->player_data;
    player_data = (player_t *)player_entity->data;
    eject_action(serv, player_data, player_entity->position);
    send_entities_list_info(serv);
    pop_message(player->player_peer);
    return print_retcode(219, NULL, player->player_peer, true);
}
