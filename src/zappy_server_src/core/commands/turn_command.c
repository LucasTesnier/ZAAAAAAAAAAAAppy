/*
** EPITECH PROJECT, 2022
** Project
** File description:
** turn_command
*/

/// \file src/zappy_server_src/core/commands/turn_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"

bool command_turn(char *arg, player_list_t *player, server_data_t *serv)
{
    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    if (!scheduler_schedule_event(serv->scheduler,
    ((player_t *)player->player_data->data)->uuid, 7))
        return false;
    player->scheduled_action = find_ai_command_end("/turn", arg);
    if (player->scheduled_action == NULL)
        return false;
    return true;
}

/// \brief Rotate the player orientation to the left
/// \param player The player object
static void turn_left(player_t *player)
{
    if (player->orientation == NORTH) {
        player->orientation = WEST;
        return;
    }
    if (player->orientation == WEST) {
        player->orientation = SOUTH;
        return;
    }
    if (player->orientation == SOUTH) {
        player->orientation = EAST;
        return;
    }
    if (player->orientation == EAST) {
        player->orientation = NORTH;
        return;
    }
}

/// \brief Rotate the player orientation to the left
/// \param player The player object
static void turn_right(player_t *player)
{
    if (player->orientation == NORTH) {
        player->orientation = EAST;
        return;
    }
    if (player->orientation == EAST) {
        player->orientation = SOUTH;
        return;
    }
    if (player->orientation == SOUTH) {
        player->orientation = WEST;
        return;
    }
    if (player->orientation == WEST) {
        player->orientation = NORTH;
        return;
    }
}

bool command_turn_end(char *arg, player_list_t *player,
server_data_t *serv)
{
    entity_t *player_entity = NULL;
    player_t *player_data = NULL;

    (void) serv;
    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    player_entity = (entity_t *)player->player_data;
    player_data = (player_t *)player_entity->data;
    if (!strcmp(arg, "left"))
        turn_left(player_data);
    else
        turn_right(player_data);
    pop_message(player->player_peer);
    return print_retcode(214, arg, player->player_peer, true);
}
