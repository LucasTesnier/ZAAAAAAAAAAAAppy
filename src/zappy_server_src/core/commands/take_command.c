/*
** EPITECH PROJECT, 2022
** Project
** File description:
** take_command
*/

/// \file src/zappy_server_src/core/commands/take_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"
#include "entity/tile.h"

bool command_take(char *arg, player_list_t *player, server_data_t *serv)
{
    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    if (!scheduler_schedule_event(serv->scheduler,
    ((player_t *)player->player_data->data)->uuid, 7))
        return false;
    player->scheduled_action = find_ai_command_end("/take", arg);
    if (player->scheduled_action == NULL)
        return false;
    return true;
}

/// \brief Take the food object in the tile
/// \param player The player informations
/// \param tile The tile informations
/// \param type The ressource type to take
/// \return true When operation succeed
/// \return false When operation failed
static bool take_action_food(player_t *player, tile_t *tile, char *type)
{
    if (!strcmp(type, "food")) {
        if (tile->inventory->food <= 0)
            return false;
        player->inventory->food += 126;
        tile->inventory->food -= 1;
    }
    return true;
}

/// \brief Take the last object in the tile
/// \param player The player informations
/// \param tile The tile informations
/// \param type The ressource type to take
/// \return true When operation succeed
/// \return false When operation failed
static bool take_action_last(player_t *player, tile_t *tile, char *type)
{
    if (!strcmp(type, "mendiane")) {
        if (tile->inventory->mendiane <= 0)
            return false;
        player->inventory->mendiane += 1;
        tile->inventory->mendiane -= 1;
    }
    if (!strcmp(type, "phiras")) {
        if (tile->inventory->phiras <= 0)
            return false;
        player->inventory->phiras += 1;
        tile->inventory->phiras -= 1;
    }
    if (!strcmp(type, "thystame")) {
        if (tile->inventory->thystame <= 0)
            return false;
        player->inventory->thystame += 1;
        tile->inventory->thystame -= 1;
    }
    return take_action_food(player, tile, type);
}

/// \brief Take the first object in the tile
/// \param player The player informations
/// \param tile The tile informations
/// \param type The ressource type to take
/// \return true When operation succeed
/// \return false When operation failed
static bool take_action(player_t *player, tile_t *tile, char *type)
{
    if (!strcmp(type, "linemate")) {
        if (tile->inventory->linemate <= 0)
            return false;
        player->inventory->linemate += 1;
        tile->inventory->linemate -= 1;
    }
    if (!strcmp(type, "deraumere")) {
        if (tile->inventory->deraumere <= 0)
            return false;
        player->inventory->deraumere += 1;
        tile->inventory->deraumere -= 1;
    }
    if (!strcmp(type, "sibur")) {
        if (tile->inventory->sibur <= 0)
            return false;
        player->inventory->sibur += 1;
        tile->inventory->sibur -= 1;
    }
    return take_action_last(player, tile, type);
}

bool command_take_end(char *arg, player_list_t *player,
server_data_t *serv)
{
    entity_t *player_entity = NULL;
    player_t *player_data = NULL;
    tile_t *tile = NULL;

    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    player_entity = (entity_t *)player->player_data;
    player_data = (player_t *)player_entity->data;
    tile = (tile_t *)get_tile(serv->map,
    player_entity->position.x, player_entity->position.y)->data;
    if (!take_action(player_data, tile, arg)) {
        pop_message(player->player_peer);
        return print_retcode(314, NULL, player->player_peer, false);
    }
    entity_diff_add_entity(serv->modified_entities, player_entity);
    entity_diff_add_entity(serv->modified_entities, get_tile(serv->map,
        player_entity->position.x, player_entity->position.y));
    pop_message(player->player_peer);
    return print_retcode(220, arg, player->player_peer, true);
}
