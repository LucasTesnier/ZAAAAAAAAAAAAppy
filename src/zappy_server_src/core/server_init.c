/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** server_init
*/

/// \file src/zappy_server/core/server_init.c

#include "server.h"
#include "argument_handling.h"
#include "sys/queue.h"
#include <stdlib.h>
#include <stdbool.h>

/// \brief Parse the arguments and initialize the server
/// \param server_data the server data
/// \param argc the number of arguments
/// \param argv the arguments
static bool init_args(server_data_t *server_data, int ac, char **av)
{
    if (!(server_data->arguments = argument_handling(ac, av)))
        return NULL;
    server_data->active_players = malloc(sizeof(player_list_t *) * 1);
    if (server_data->active_players == NULL)
        return NULL;
    server_data->active_players[0] = NULL;
    server_data->active_player_n = 0;
}
/// \brief Init the server scheduler, map and inial entities
/// \param server_data the server data
/// \todo set the players to a random position
static bool init_objects(server_data_t *server_data)
{
    server_data->map = create_new_map(server_data->arguments->width,
    server_data->arguments->height);
    if (server_data->map == NULL)
        return NULL;
    if (!(server_data->scheduler = create_scheduler(
        server_data->arguments->freq)))
        return NULL;
    if (!(server_data->entities = create_entity_wrapper()))
        return NULL;
    for (int i = 0; i < server_data->arguments->width; i++) {
        for (int j = 0; j < server_data->arguments->height; j++) {
            TAILQ_INSERT_HEAD(server_data->entities->tiles,
            get_tile(server_data->map, i, j), entities);
        }
    }
}

server_data_t *init_server_data(int ac, char **av)
{
    server_data_t *server_data = malloc(sizeof(server_data_t) * 1);
    int size_queue = 0;

    if (server_data == NULL)
        return NULL;
    if (!init_args(server_data, ac, av))
        return NULL;
    for (int i = 0; server_data->arguments->team_list[i]; i++)
        size_queue += server_data->arguments->client_nb;
    if (!init_objects(server_data))
        return NULL;
    server_data->server = create_new_server(server_data->arguments->port,
    size_queue);
    if (server_data->server == NULL)
        return NULL;
    server_data->server->state = true;
    return server_data;
}
