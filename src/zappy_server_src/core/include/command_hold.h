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

#endif /* !COMMAND_H_ */
