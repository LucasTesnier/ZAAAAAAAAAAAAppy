/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** unpack
*/

#include "data_game.h"
#include <string>
#include <iostream>

static const egg_t eggs[] = {
    {.team = 0, .life = 0},
};


ressource_t init_ressources(void)
{
    ressource_t r;
    r.food = 0;
    r.deraumere = 0;
    r.linemate = 0;
    r.mendiane = 0;
    r.phiras = 0;
    r.sibur = 0;
    r.thystame = 0;
    return r;
}

player_t *init_player(void)
{
    player_t *p = (player_t *)malloc(sizeof(player_t));
    if (p) {
        p->x = 0;
        p->y = 0;
        p->life = 0;
        p->team_name = NULL;
        p->action_time = 0;
        p->action_info = NULL;
        p->status_player = STATUSUNDEFINED;
        p->inventory = init_ressources();
        p->level = LEVELUNDEFINED;
        p->orientation = ORIENTATIONUNDEFINED;
    }
    return p;
}

tile_t *init_tile(void)
{
    tile_t *t = (tile_t *)malloc(sizeof(tile_t));
    if (t) {
        t->x = 0;
        t->y = 0;
        t->ressources = init_ressources();
        t->eggs = NULL;
    }
    return t;
}

data_t unpack(char *data_string)
{
    data_t data;
    return data;
};

std::string pack(data_t data)
{
    std::string packed;
    player_t player;
    int nb_player = 1;
    for (int i = 0; i < nb_player; i++) {
        player = data.players[i];
        std::cout << player.action_time <<std::endl;
        packed.append("player{" + std::to_string(player.x) + ';' + std::to_string(player.y) + ';'
        + std::to_string(player.life) + ';' + std::to_string(player.action_time) + ';'
        + std::to_string(player.status_player) + ";inventory{"
        + std::to_string(player.inventory.food) + ';' + std::to_string(player.inventory.linemate) + ';'
        + ';' +std::to_string(player.inventory.deraumere) + ';' + std::to_string(player.inventory.sibur) + ';'
        + std::to_string(player.inventory.mendiane) + ';' + std::to_string(player.inventory.thystame) + ';'
        + std::to_string(player.inventory.phiras) + ';' + std::to_string(player.inventory.thystame)
        + "};" + player.team_name + ';' + std::to_string(player.level) + ';' + std::to_string(player.orientation));
    }
    return packed;
};