/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** inventory_command
*/

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"
#include "container.h"

bool command_inventory(char *arg, player_list_t *player, server_data_t *serv)
{
    player_t *player_data = NULL;
    container_t *inventory = NULL;

    (void) arg;
    (void) serv;
    if (!player->player_data)
        return print_retcode(402, arg, player->player_peer, false);
    pop_message(player->player_peer);
    player_data = player->player_data;
    inventory = player_data->inventory;

}
