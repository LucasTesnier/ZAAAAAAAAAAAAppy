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

/// \brief Command informations and data
typedef struct command_data_s {
    /// Name of the command
    char *name;
    /// Arg of the command (Possibly NULL)
    char *arg;
    /// Function pointer to the command
    bool (*ptr)(char *, player_list_t *, server_data_t *);
} command_data_t;

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

#endif /* !COMMAND_H_ */
