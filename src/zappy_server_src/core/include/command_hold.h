/*
** EPITECH PROJECT, 2022
** Project
** File description:
** command
*/

/// \file src/zappy_server_src/core/include/command_hold.h

#ifndef COMMAND_H_
    #define COMMAND_H_

    #include "server.h"
    #include <stdbool.h>
    #include "entity/player.h"

/// \brief Hold the command process (Identification and execution)
/// \param command Command in string format
/// \param player_info Info about the player
/// \param server_data Server informations
void compute_command(char *command, player_list_t *player_info,
server_data_t *server_data);

/// \brief Command for disconnection
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Serveur informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_logout(char *arg, player_list_t *player, server_data_t *serv);

/// \brief Command for login
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Serveur informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_login(char *arg, player_list_t *player, server_data_t *serv);

/// \brief Command for join the game
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Serveur informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_join(char *arg, player_list_t *player, server_data_t *serv);

/// \brief Start the inventory process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_inventory(char *arg, player_list_t *player, server_data_t *serv);

/// \brief End the inventory process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_inventory_end(char *arg, player_list_t *player,
server_data_t *serv);

/// \brief Start the forward process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_forward(char *arg, player_list_t *player, server_data_t *serv);

/// \brief End the forward process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_forward_end(char *arg, player_list_t *player,
server_data_t *serv);

/// \brief Start the turn process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_turn(char *arg, player_list_t *player, server_data_t *serv);

/// \brief End the turn process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_turn_end(char *arg, player_list_t *player,
server_data_t *serv);

/// \brief Start the look process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_look(char *arg, player_list_t *player, server_data_t *serv);

/// \brief End the look process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_look_end(char *arg, player_list_t *player,
server_data_t *serv);

/// \brief Start the broadcast process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_broadcast(char *arg, player_list_t *player, server_data_t *serv);

/// \brief End the broadcast process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_broadcast_end(char *arg, player_list_t *player,
server_data_t *serv);

/// \brief End the connectnbr process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_connectnbr(char *arg, player_list_t *player, server_data_t *serv);

/// \brief Start the fork process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_fork(char *arg, player_list_t *player, server_data_t *serv);

/// \brief End the fork process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_fork_end(char *arg, player_list_t *player,
server_data_t *serv);

/// \brief Start the eject process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_eject(char *arg, player_list_t *player, server_data_t *serv);

/// \brief End the eject process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_eject_end(char *arg, player_list_t *player,
server_data_t *serv);

/// \brief Start the take process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_take(char *arg, player_list_t *player, server_data_t *serv);

/// \brief End the take process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_take_end(char *arg, player_list_t *player,
server_data_t *serv);

/// \brief Start the place process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_place(char *arg, player_list_t *player, server_data_t *serv);

/// \brief End the place process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_place_end(char *arg, player_list_t *player,
server_data_t *serv);

/// \brief Start the incantation process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_incantation(char *arg, player_list_t *player,
server_data_t *serv);

/// \brief End the incantation process
/// \param arg Arg of the command
/// \param player Player informations
/// \param serv Server informations
/// \return true When operation succeed
/// \return false When operation failed
bool command_incantation_end(char *arg, player_list_t *player,
server_data_t *serv);

/// \brief Send a eject signal to a player
/// \param direction The eject direction
/// \param serv Server informations
/// \param tmp The data of the player
void send_unexpected_eject(enum player_orientation_e direction,
server_data_t *serv, player_t *tmp);

/// List of AI command end
static const command_data_t ai_command_list_end[] = {
    {"/inventory", NULL, &command_inventory_end},
    {"/forward", NULL, &command_forward_end},
    {"/turn", NULL, &command_turn_end},
    {"/look", NULL, &command_look_end},
    {"/broadcast", NULL, &command_broadcast_end},
    {"/fork", NULL, &command_fork_end},
    {"/eject", NULL, &command_eject_end},
    {"/take", NULL, &command_take_end},
    {"/place", NULL, &command_place_end},
    {"/incantation", NULL, &command_incantation_end},
    {NULL, NULL, NULL}
};

/// \brief Create a command data from a name
/// \param cmd Name of the command
/// \param arg Args of the command
/// \return command_data_t* Newly created command
static inline command_data_t *find_ai_command_end(char *cmd, char *arg)
{
    command_data_t *command = malloc(sizeof(command_data_t));
    int pos = 0;

    if (command == NULL)
        return NULL;
    for (; ai_command_list_end[pos].name; pos++)
        if (!strcmp(ai_command_list_end[pos].name, cmd))
            break;
    if (!ai_command_list_end[pos].name)
        return NULL;
    command->name = ai_command_list_end[pos].name;
    command->ptr = ai_command_list_end[pos].ptr;
    command->arg = (!arg) ? NULL : strdup(arg);
    return command;
}

/// \brief Delete a command_data object
/// \param command The command data object to delete
static inline void delete_command_data(command_data_t *command)
{
    if (command->arg)
        free(command->arg);
    free(command);
}

#endif /* !COMMAND_H_ */
