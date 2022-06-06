/*
** EPITECH PROJECT, 2022
** Project
** File description:
** command_hold
*/

/// \file src/zappy_server_src/core/command_hold.c

#include "server.h"
#include "command_hold.h"

/// List of all the ai command
static const command_data_t ai_command_list[2] = {
    {"/logout", NULL, NULL},
    {NULL, NULL, NULL}
};

/// List of all the gui command
static const command_data_t gui_command_list[2] = {
    {"/logout", NULL, NULL},
    {NULL, NULL, NULL}
};

/// List of all the unknown command
static const command_data_t unknown_command_list[2] = {
    {"/login", "Args", NULL},
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

    command[strlen(command)] = '\0';
    command_data = find_command_data(command, player_info);
    free(command);
    printf("HERE\n");
    if (command_data == NULL)
        return;
    printf("Why not :) %s\n", command_data->name);
    (void) server_data;
    /// EXECUTE THE COMMAND
    free(command_data);
}