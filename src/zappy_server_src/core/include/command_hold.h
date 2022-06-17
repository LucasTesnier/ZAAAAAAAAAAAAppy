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

/// List of AI command end
static const command_data_t ai_command_list_end[] = {
    {"/inventory", NULL, &command_inventory_end},
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
    command->arg = arg;
    return command;
}

#endif /* !COMMAND_H_ */
