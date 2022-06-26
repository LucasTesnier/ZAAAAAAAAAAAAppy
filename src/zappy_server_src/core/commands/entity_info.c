/*
** EPITECH PROJECT, 2022
** Project
** File description:
** entity_info
*/

/// \file src/zappy_server_src/core/commands/entity_info.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/entity.h"
#include "entity/pack.h"

char *pack_all_entities(entity_wrapper_t *entities)
{
    char *res = malloc(sizeof(char) * 1);
    char *temp = NULL;
    entity_t *entity = NULL;

    if (res == NULL)
        return NULL;
    res[0] = '\0';
    TAILQ_FOREACH(entity, &entities->players, entities) {
        temp = pack_entity(entity);
        res = realloc(res, sizeof(char) * (strlen(res) + strlen(temp) + 1));
        strcat(res, temp);
        free(temp);
    }
    TAILQ_FOREACH(entity, &entities->eggs, entities) {
        temp = pack_entity(entity);
        res = realloc(res, sizeof(char) * (strlen(res) + strlen(temp) + 1));
        strcat(res, temp);
        free(temp);
    }
    return res;
}

bool send_entities_list_info(server_data_t *serv)
{
    peer_t *peer = NULL;
    char *temp = NULL;

    for (size_t i = 0; i < serv->active_player_n; i++)
        if (serv->active_players[i]->disconnected == CONNECTED &&
        serv->active_players[i]->type == GUI) {
            peer = serv->active_players[i]->player_peer;
            break;
        }

    temp = pack_all_entities(serv->entities);
    print_retcode(707, temp, peer, true);
    free(temp);
    return true;
}
