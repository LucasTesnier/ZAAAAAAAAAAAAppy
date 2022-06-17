/*
** EPITECH PROJECT, 2022
** Project
** File description:
** forward_command
*/

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"

bool command_forward(char *arg, player_list_t *player, server_data_t *serv)
{
    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    if (!scheduler_schedule_event(serv->scheduler,
    ((player_t *)player->player_data)->uuid, 7))
        return false;
    player->scheduled_action = find_ai_command_end("/forward", NULL);
    if (player->scheduled_action == NULL)
        return false;
    return true;
}

bool command_forward_end(char *arg, player_list_t *player,
server_data_t *serv)
{
    (void) arg;
    (void) serv;
    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    pop_message(player->player_peer);
    return print_retcode(213, NULL, player->player_peer, true);
}