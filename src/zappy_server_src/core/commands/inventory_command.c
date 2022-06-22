/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** inventory_command
*/

/// \file src/zappy_server_src/core/commands/inventory_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"
#include "container.h"

bool command_inventory(char *arg, player_list_t *player, server_data_t *serv)
{
    if (!player->player_data)
        return print_retcode(402, arg, player->player_peer, false);
    if (!scheduler_schedule_event(serv->scheduler,
    ((player_t *)player->player_data->data)->uuid, 1))
        return false;
    player->scheduled_action = find_ai_command_end("/inventory", NULL);
    if (player->scheduled_action == NULL)
        return false;
    return true;
}

bool command_inventory_end(char *arg, player_list_t *player,
server_data_t *serv __attribute__((unused)))
{
    entity_t *player_entity = NULL;
    player_t *player_data = NULL;
    container_t *inventory = NULL;
    char *temp = NULL;

    if (!player->player_data)
        return print_retcode(402, arg, player->player_peer, false);
    player_entity = (entity_t *)player->player_data;
    player_data = (player_t *)player_entity->data;
    inventory = player_data->inventory;
    pop_message(player->player_peer);
    temp = pack_inventory(inventory);
    print_retcode(212, temp, player->player_peer, true);
    free(temp);
    return true;
}
