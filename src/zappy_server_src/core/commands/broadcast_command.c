/*
** EPITECH PROJECT, 2022
** Project
** File description:
** broadcast_command
*/

/// \file src/zappy_server_src/core/commands/broadcast_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"

bool command_broadcast(char *arg, player_list_t *player, server_data_t *serv)
{
    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    if (!scheduler_schedule_event(serv->scheduler,
    ((player_t *)player->player_data->data)->uuid, 7))
        return false;
    player->scheduled_action = find_ai_command_end("/broadcast", arg);
    if (player->scheduled_action == NULL)
        return false;
    return true;
}

/// \brief Get the list of all player_list_t to send the messages
/// \param serv The server informations
/// \param player The player informations
/// \return player_list_t** The list of all player to send
static player_list_t **get_send_list(server_data_t *serv,
player_list_t *player)
{
    player_list_t **to_send = NULL;
    int count = 0;

    for (size_t i = 0; i < serv->active_player_n; i++)
        if (serv->active_players[i]->type == AI &&
        serv->active_players[i]->disconnected == CONNECTED)
            count++;
    if (count == 1)
        return NULL;
    to_send = malloc(sizeof(player_list_t *) * (count + 1));
    count = 0;
    for (size_t i = 0; i < serv->active_player_n; i++)
        if (serv->active_players[i]->type == AI &&
        serv->active_players[i] != player &&
        serv->active_players[i]->disconnected == CONNECTED) {
            to_send[count] = serv->active_players[i];
            count++;
        }
    to_send[count] = NULL;
    return to_send;
}

/// \brief Cross all the to_send list and tell them the message
/// \param to_send The list of player to send the messages
/// \param serv The server informations
/// \param send The sender informations
/// \param message The message to send
static void process_send(player_list_t **to_send, server_data_t *serv,
player_list_t *send, char *message)
{
    char *temp = malloc(sizeof(char) * (strlen(message) + 15));
    entity_t *player = NULL;

    if (temp == NULL)
        return;
    for (int i = 0; to_send[i]; i++) {
        temp[0] = '\0';
        player = to_send[i]->player_data;
        sprintf(temp, "message %i, %s", get_directionnal_value(
        player->position, (position_t) {
        serv->map->width, serv->map->height}, send->player_data->position,
        ((player_t *)player->data)->orientation), message);
        print_retcode(603, temp, to_send[i]->player_peer, true);
    }
    (void) send;
    (void) serv;
    free(temp);
}

bool command_broadcast_end(char *arg, player_list_t *player,
server_data_t *serv)
{
    player_list_t **to_send = NULL;

    (void) serv;
    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    to_send = get_send_list(serv, player);
    if (to_send != NULL) {
        process_send(to_send, serv, player, arg);
        free(to_send);
    }
    pop_message(player->player_peer);
    return print_retcode(216, arg, player->player_peer, true);
}
