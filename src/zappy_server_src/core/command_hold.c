/*
** EPITECH PROJECT, 2022
** Project
** File description:
** command_hold
*/

/// \file src/zappy_server_src/core/command_hold.c

#include "server.h"
#include "command_hold.h"
#include "rcodes.h"

/// \brief List of all the ai command start
static const command_data_t ai_command_list[] = {
    {"/logout", NULL, &command_logout},
    {"/forward", NULL, &command_forward},
    {"/turn", "Args Left Right", &command_turn},
    {"/look", NULL, &command_look},
    {"/inventory", NULL, &command_inventory},
    {"/broadcast", "Args message", &command_broadcast},
    {"/connectnbr", NULL, &command_connectnbr},
    {"/fork", NULL, &command_fork},
    {"/eject", NULL, &command_eject},
    {"/take", "Args type", &command_take},
    {"/place", "Args type", &command_place},
    {"/incantation", NULL, &command_incantation},
    {"/join", "Args Team", &command_join},
    {NULL, NULL, NULL}
};

/// \brief List of all the gui command
static const command_data_t gui_command_list[] = {
    {"/logout", NULL, &command_logout},
    {"/restart", "Args config", NULL},
    {NULL, NULL, NULL}
};

static const command_data_t flutter_command_list[] = {
    {"/logout", NULL, &command_logout},
    {"/get_density", NULL, &command_get_density},
    {"/push_density", "Args", &command_push_density},
    {NULL, NULL, NULL}
};

/// \brief List of all the unknown command
static const command_data_t unknown_command_list[] = {
    {"/login", "Args type", &command_login},
    {NULL, NULL, NULL}
};

/// \brief Cross all the gui command and try to match a command
/// \param command Command info to fill
/// \param cmd Command to match
/// \return true When command is found
/// \return false When command is not found
static bool find_gui_command(command_data_t *command, char *cmd)
{
    int pos = 0;

    for (; gui_command_list[pos].name; pos++)
        if (!strncmp(gui_command_list[pos].name, cmd,
        strlen(gui_command_list[pos].name)))
            break;
    if (!gui_command_list[pos].name)
        return false;
    command->name = gui_command_list[pos].name;
    command->ptr = gui_command_list[pos].ptr;
    if (cmd[strlen(gui_command_list[pos].name)] == ' ' &&
    gui_command_list[pos].arg) {
        command->arg = cmd + strlen(gui_command_list[pos].name) + 1;
        return true;
    }
    command->arg = NULL;
    if (cmd[strlen(gui_command_list[pos].name)] == '\0' &&
    !gui_command_list[pos].arg)
        return true;
    return false;
}

/// \brief Cross all the flutter command and try to match a command
/// \param command Command info to fill
/// \param cmd Command to match
/// \return true When command is found
/// \return false When command is not found
static bool find_flutter_command(command_data_t *command, char *cmd)
{
    int pos = 0;

    for (; flutter_command_list[pos].name; pos++)
        if (!strncmp(flutter_command_list[pos].name, cmd,
        strlen(flutter_command_list[pos].name)))
            break;
    if (!flutter_command_list[pos].name)
        return false;
    command->name = flutter_command_list[pos].name;
    command->ptr = flutter_command_list[pos].ptr;
    if (cmd[strlen(flutter_command_list[pos].name)] == ' ' &&
    flutter_command_list[pos].arg) {
        command->arg = cmd + strlen(flutter_command_list[pos].name) + 1;
        return true;
    }
    command->arg = NULL;
    if (cmd[strlen(flutter_command_list[pos].name)] == '\0' &&
    !flutter_command_list[pos].arg)
        return true;
    return false;
}

/// \brief Cross all the ai command and try to match a command
/// \param command Command info to fill
/// \param cmd Command to match
/// \return true When command is found
/// \return false When command is not found
static bool find_ai_command(command_data_t *command, char *cmd)
{
    int pos = 0;

    for (; ai_command_list[pos].name; pos++)
        if (!strncmp(ai_command_list[pos].name, cmd,
        strlen(ai_command_list[pos].name)))
            break;
    if (!ai_command_list[pos].name)
        return false;
    command->name = ai_command_list[pos].name;
    command->ptr = ai_command_list[pos].ptr;
    if (cmd[strlen(ai_command_list[pos].name)] == ' ' &&
    ai_command_list[pos].arg) {
        command->arg = cmd + strlen(ai_command_list[pos].name) + 1;
        return true;
    }
    command->arg = NULL;
    if (cmd[strlen(ai_command_list[pos].name)] == '\0' &&
    !ai_command_list[pos].arg)
        return true;
    return false;
}

/// \brief Cross all the unknown command and try to match a command
/// \param command Command info to fill
/// \param cmd Command to match
/// \return true When command is found
/// \return false When command is not found
static bool find_unknown_command(command_data_t *command, char *cmd)
{
    int pos = 0;

    for (; unknown_command_list[pos].name; pos++)
        if (!strncmp(unknown_command_list[pos].name, cmd,
        strlen(unknown_command_list[pos].name)))
            break;
    if (!unknown_command_list[pos].name)
        return false;
    command->name = unknown_command_list[pos].name;
    command->ptr = unknown_command_list[pos].ptr;
    if (cmd[strlen(unknown_command_list[pos].name)] == ' ' &&
    unknown_command_list[pos].arg) {
        command->arg = cmd + strlen(unknown_command_list[pos].name) + 1;
        return true;
    }
    command->arg = NULL;
    if (cmd[strlen(unknown_command_list[pos].name)] == '\0' &&
    !unknown_command_list[pos].arg)
        return true;
    return false;
}

/// \brief Parse and match the given command to a existing one
/// \param command Command to parse
/// \param player_info Player informations
/// \return command_data_t* Newly created command data
static command_data_t *find_command_data(char *command,
player_list_t *player_info)
{
    command_data_t *command_data = malloc(sizeof(command_data_t));
    bool operation = false;

    if (command_data == NULL)
        return NULL;
    if (player_info->type == GUI)
        operation = find_gui_command(command_data, command);
    if (player_info->type == AI)
        operation = find_ai_command(command_data, command);
    if (player_info->type == FLUTTER)
        operation = find_flutter_command(command_data, command);
    if (player_info->type == UNKNOWN)
        operation = find_unknown_command(command_data, command);
    if (operation == false) {
        free(command_data);
        return NULL;
    }
    return command_data;
}

void compute_command(char *command, player_list_t *player_info,
server_data_t *server_data)
{
    command_data_t *command_data = NULL;

    command[strlen(command) - 2] = '\0';
    command_data = find_command_data(command, player_info);
    dprintf(2, "Get command : %s\n", command);
    if (command_data == NULL) {
        pop_message(player_info->player_peer);
        print_retcode(501, command, player_info->player_peer, false);
        free(command);
        return;
    }
    if (!command_data->ptr(command_data->arg, player_info, server_data)) {
        pop_message(player_info->player_peer);
    }
    free(command);
    free(command_data);
}
