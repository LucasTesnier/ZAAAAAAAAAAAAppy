/*
** EPITECH PROJECT, 2022
** Project
** File description:
** place_command
*/

/// \file src/zappy_server_src/core/commands/place_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"
#include "entity/tile.h"

bool command_place(char *arg, player_list_t *player, server_data_t *serv)
{
    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    if (!scheduler_schedule_event(serv->scheduler,
    ((player_t *)player->player_data->data)->uuid, 7))
        return false;
    player->scheduled_action = find_ai_command_end("/place", arg);
    if (player->scheduled_action == NULL)
        return false;
    return true;
}

/// \brief Place the last object in the tile
/// \param player The player informations
/// \param tile The tile informations
/// \param type The ressource type to place
/// \return true When operation succeed
/// \return false When operation failed
static bool place_action_last(player_t *player, tile_t *tile, char *type)
{
    if (!strcmp(type, "mendiane")) {
        if (player->inventory->mendiane <= 0)
            return false;
        tile->inventory->mendiane += 1;
        player->inventory->mendiane -= 1;
    }
    if (!strcmp(type, "phiras")) {
        if (player->inventory->phiras <= 0)
            return false;
        tile->inventory->phiras += 1;
        player->inventory->phiras -= 1;
    }
    if (!strcmp(type, "thystame")) {
        if (player->inventory->thystame <= 0)
            return false;
        tile->inventory->thystame += 1;
        player->inventory->thystame -= 1;
    }
    return true;
}

/// \brief place the first object in the tile
/// \param player The player informations
/// \param tile The tile informations
/// \param type The ressource type to place
/// \return true When operation succeed
/// \return false When operation failed
static bool place_action(player_t *player, tile_t *tile, char *type)
{
    if (!strcmp(type, "linemate")) {
        if (player->inventory->linemate <= 0)
            return false;
        tile->inventory->linemate += 1;
        player->inventory->linemate -= 1;
    }
    if (!strcmp(type, "deraumere")) {
        if (player->inventory->deraumere <= 0)
            return false;
        tile->inventory->deraumere += 1;
        player->inventory->deraumere -= 1;
    }
    if (!strcmp(type, "sibur")) {
        if (player->inventory->sibur <= 0)
            return false;
        tile->inventory->sibur += 1;
        player->inventory->sibur -= 1;
    }
    return place_action_last(player, tile, type);
}

bool command_place_end(char *arg, player_list_t *player,
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
    if (!place_action(player_data, tile, arg)) {
        pop_message(player->player_peer);
        return print_retcode(315, NULL, player->player_peer, false);
    }
    send_map_info(serv);
    pop_message(player->player_peer);
    return print_retcode(221, arg, player->player_peer, true);
}