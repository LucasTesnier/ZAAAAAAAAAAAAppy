/*
** EPITECH PROJECT, 2022
** Project
** File description:
** start_information
*/

/// \file src/zappy_server_src/core/commands/start_informations.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"
#include "entity/pack.h"

/// \brief Pack all the team name
/// \param list The team list
/// \return char* The packed team name
static char *pack_team_name(char **list)
{
    char *res = malloc(sizeof(char) * 100000);

    if (res == NULL)
        return NULL;
    res[0] = '\0';
    for (int i = 0; list[i]; i++) {
        strcat(res, list[i]);
        if (list[i + 1])
            strcat(res, ";");
    }
    return res;
}

/// \brief Packed all the argument
/// \param args The argument to be packed
/// \return char* The packed arguments
static char *pack_all_arg(argument_t *args)
{
    char *res = malloc(sizeof(char) * 100000);
    int team_number = 0;
    char *team_name = NULL;

    if (res == NULL)
        return NULL;
    for (; args->team_list[team_number]; team_number++);
    team_name = pack_team_name(args->team_list);
    res[0] = '\0';
    sprintf(res, "start{%i;%i;%i;{%s};%i}", args->width, args->height,
    team_number, team_name, args->client_nb);
    free(team_name);
    return res;
}

/// \brief Pack all the data
/// \param serv The server information's
/// \return char* The packed data
static char *pack_all_data(server_data_t *serv)
{
    char *res = malloc(sizeof(char) * 1);
    char *temp = NULL;

    if (res == NULL)
        return NULL;
    res[0] = '\0';
    temp = pack_all_arg(serv->arguments);
    res = realloc(res, sizeof(char) * (strlen(temp) + strlen(res) + 1));
    strcat(res, temp);
    free(temp);
    temp = pack_all_tile(serv->map);
    res = realloc(res, sizeof(char) * (strlen(temp) + strlen(res) + 1));
    strcat(res, temp);
    free(temp);
    temp = pack_all_entities(serv->entities);
    res = realloc(res, sizeof(char) * (strlen(temp) + strlen(res) + 1));
    strcat(res, temp);
    free(temp);
    return res;
}

bool send_start_info(server_data_t *serv)
{
    peer_t *peer = NULL;
    char *temp = NULL;

    for (size_t i = 0; i < serv->active_player_n; i++)
        if (serv->active_players[i]->disconnected == CONNECTED &&
        serv->active_players[i]->type == GUI) {
            peer = serv->active_players[i]->player_peer;
            break;
        }

    temp = pack_all_data(serv);
    print_retcode(701, temp, peer, true);
    free(temp);
    return true;
}
