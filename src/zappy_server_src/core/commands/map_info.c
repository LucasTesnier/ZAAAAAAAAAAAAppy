/*
** EPITECH PROJECT, 2022
** Project
** File description:
** map_info
*/

/// \file src/zappy_server_src/core/commands/map_info.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"
#include "entity/pack.h"

char *pack_all_tile(map_t *map)
{
    char *res = malloc(sizeof(char) * 1);
    char *temp = NULL;

    if (res == NULL)
        return NULL;
    res[0] = '\0';
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            temp = pack_tile(map->tiles[i * map->width + j]);
            res = realloc(res, sizeof(char) *
            (strlen(res) + strlen(temp) + 1));
            strcat(res, temp);
            free(temp);
        }
    }
    return res;
}

char *pack_modified_entities(entity_diff_t *entity_diff)
{
    char *res = malloc(sizeof(char) * 1);
    char *temp = NULL;

    if (res == NULL)
        return NULL;
    res[0] = '\0';
    for (size_t i = 0; i < entity_diff->offset; i++) {
        temp = pack_entity(entity_diff->entities[i]);
        res = realloc(res, sizeof(char) *
        (strlen(res) + strlen(temp) + 1));
        strcat(res, temp);
        free(temp);
    }
    return res;
}

bool send_map_info(server_data_t *serv)
{
    peer_t *peer = NULL;
    char *temp = NULL;

    for (size_t i = 0; i < serv->active_player_n; i++) {
        if (serv->active_players[i]->disconnected == CONNECTED &&
        serv->active_players[i]->type == GUI) {
            peer = serv->active_players[i]->player_peer;
            break;
        }
    }
    if (peer == NULL) {
        dprintf(2, "No GUI client found.\n");
        return false;
    }
    temp = pack_modified_entities(serv->modified_entities);
    entity_diff_reset(serv->modified_entities);
    print_retcode(708, temp, peer, true);
    free(temp);
    return true;
}
