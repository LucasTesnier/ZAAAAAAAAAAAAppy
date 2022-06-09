/*
** EPITECH PROJECT, 2022
** Project
** File description:
** argument_handling
*/

/// \file src/zappy_server_src/core/argument_handling.c

#include "server.h"
#include "argument_handling.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

/// \brief Cross all the args list to detect flags
/// \param args Argument data structure
/// \param ac Number of args
/// \param av List of all the args
/// \param is_team Is the -n option has been detected ?
/// \return true When operation succeed
/// \return false When operation failed
static bool process_argument_handling(argument_t *args, int ac, char **av,
bool *is_team)
{
    int opt = 0;

    while ((opt = getopt(ac, av, ":p:x:y:nc:f:")) != -1 && opt != '?') {
        if (opt == 'p')
            args->port = atol(optarg);
        if (opt == 'x')
            args->width = atoi(optarg);
        if (opt == 'y')
            args->height = atoi(optarg);
        if (opt == 'c')
            args->client_nb = atoi(optarg);
        if (opt == 'f')
            args->freq = atoi(optarg);
        if (opt == 'n')
            *is_team = true;
        if (opt == ':')
            return false;
    }
    return true;
}

/// \brief Compute the team name list
/// \param args Argument data structure
/// \param ac Number of args
/// \param av List of all the args
/// \param is_team Is the -n option has been detected ?
/// \return true When operation succeed
/// \return false When operation failed
static bool process_team_list(argument_t *args, int ac, char **av,
bool is_team)
{
    int pos = 0;

    if (!is_team) {
        dprintf(2, "Please use the -n option.\n");
        return false;
    }
    args->team_list = malloc(sizeof(char *) * ac);
    if (!args->team_list)
        return false;
    for (; optind < ac; optind++) {
        args->team_list[pos] = av[optind];
        pos++;
    }
    args->team_list[pos] = NULL;
    if (pos == 0 || pos == 1) {
        dprintf(2, "Please give a minimum of 2 teams.\n");
        return false;
    }
    return true;
}

/// \brief Check the arguments integrity
/// \param args Argument data structure
/// \return true When operation succeed
/// \return false When operation failed
static bool process_integrity(argument_t *args)
{
    if (args->port == 0) {
        dprintf(2, "Please give a valid port.\n");
        return false;
    }
    if (args->width == 0 || args->height == 0) {
        dprintf(2, "Please give a valid map size.\n");
        return false;
    }
    if (args->client_nb == 0) {
        dprintf(2, "Please give a valid client nb.\n");
        return false;
    }
    if (args->freq == 0) {
        dprintf(2, "Please give a valid timefrequence.\n");
        return false;
    }
    return true;
}

argument_t *argument_handling(int ac, char **av)
{
    argument_t *args = malloc(sizeof(argument_t) * 1);
    bool is_team = false;

    if (args == NULL)
        return NULL;
    args->port = 0;
    args->width = 0;
    args->height = 0;
    args->client_nb = 0;
    args->freq = 0;
    if (!process_argument_handling(args, ac, av, &is_team))
        return NULL;
    if (!process_integrity(args))
        return NULL;
    if (!process_team_list(args, ac, av, is_team))
        return NULL;
    return args;
}

void argument_destroy(argument_t *args)
{
    if (!args)
        return;
    free(args->team_list);
    free(args);
}
