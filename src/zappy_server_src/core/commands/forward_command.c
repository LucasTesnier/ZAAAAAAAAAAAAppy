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
#include "map.h"

/// \brief Move an entity to a given direction
/// \param player Entity informations
/// \param map Map informations
static void move_x(entity_t *player, map_t *map)
{
    position_t *pos = &player->position;
    player_t *player_data = (player_t *)player->data;

    if (player_data->orientation == NORTH)
        pos->x = (pos->x - 1) < 0 ? (map->width - 1) :
        (pos->x - 1) % (map->width - 1);
    else
        pos->x = (map->width == 1) ? 0 : (pos->x + 1) % (map->width - 1);
}

/// \brief Move an entity to a given direction
/// \param player Entity information's
/// \param map Map information's
static void move_y(entity_t *player, map_t *map)
{
    position_t *pos = &player->position;
    player_t *player_data = (player_t *)player->data;

    if (player_data->orientation == EAST)
        pos->y = (map->height == 1) ? 0 : (pos->y + 1) % (map->height - 1);
    else
        pos->y = (pos->y - 1) < 0 ? (map->height - 1) :
        (pos->y - 1) % (map->height - 1);
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

bool command_forward_end(char *arg __attribute__((unused)),
player_list_t *player, server_data_t *serv)
{
    entity_t *player_entity = NULL;
    player_t *player_data = NULL;

    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    player_entity = (entity_t *)player->player_data;
    player_data = (player_t *)player_entity->data;
    if (player_data->orientation == NORTH || player_data->orientation == SOUTH)
        move_x(player_entity, serv->map);
    else
        move_y(player_entity, serv->map);
//    TAILQ_INSERT_HEAD(&serv->entities->players, player_entity, entities);
    send_entities_list_info(serv);
    pop_message(player->player_peer);
    return print_retcode(213, NULL, player->player_peer, true);
}
