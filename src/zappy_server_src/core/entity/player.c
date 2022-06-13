/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** player
*/

/// \file src/zappy_server_src/core/entity/player.c

#include "entity/player.h"

player_t *create_player(char *team_name)
{
    player_t *player = (player_t*)malloc(sizeof(player_t));

    if (!player)
        return NULL;
    memset(player, 0, sizeof(player_t));
    player->team = strdup(team_name);
    player->inventory = new_container();
    CONTAINER_ADD_FOOD(player->inventory, 10);
    player->level = 1;
    uuid_generate(player->uuid);
    return player;
}

bool player_level_up(player_t *player)
{
    if (player->level == 8)
        return false;
    player->level++;
    return true;
}

void delete_player(player_t *player)
{
    if (!player)
        return;
    free(player->team);
    delete_container(player->inventory);
    free(player);
}

bool player_set_orientation(player_t *player,
enum player_orientation_e orientation)
{
    if (!player)
        return false;
    player->orientation = orientation;
    return true;
}