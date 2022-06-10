/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** unpack
*/

#include "data_game.h"
#include <string.h>
#include <string>
#include <vector>
#include <iostream>

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

std::vector<std::string> stov(const std::string &str, char separator, bool pushEmptyStrings = false)
    {
        std::vector<std::string> vector;
        std::string temp;
        size_t len = str.size();

        for (size_t i = 0; i < len; i++) {
            if (str[i] == separator) {
                if (pushEmptyStrings || !temp.empty()) {
                    vector.push_back(temp);
                    temp.clear();
                }
            }
            else
                temp.push_back(str[i]);
        }
        if (pushEmptyStrings || !temp.empty())
            vector.push_back(temp);
        return vector;
    }

data_t unpack(char *data_string)
{
    data_t data;
    auto parsed = stov(data_string, '{');
    return data;
};

std::string pack(data_t data)
{
    std::string packed;
    tile_t t;
    player_t p;
    for (int i = 0; i < data.nb_players; i++) {
        p = data.players[i];
        auto tmp = "player{" + std::to_string(p.x) + ';' + std::to_string(p.y) + ';'
        + std::to_string(p.life) + ';' + std::to_string(p.action_time) + ';'
        + std::to_string(p.status_player) + ";inventory{"
        + std::to_string(p.inventory.food) + ';' + std::to_string(p.inventory.linemate)
        + ';' +std::to_string(p.inventory.deraumere) + ';' + std::to_string(p.inventory.sibur) + ';'
        + std::to_string(p.inventory.mendiane) + ';' + std::to_string(p.inventory.thystame) + ';'
        + std::to_string(p.inventory.phiras) + ';' + std::to_string(p.inventory.thystame)
        + "};" + p.team_name + ';' + std::to_string(p.level) + ';' + std::to_string(p.orientation) + "}";
        packed.append(tmp);
    }
    for (int i = 0; i < data.nb_tiles; i++) {
        t = data.tiles[i];
        auto tmp = "tile{" + std::to_string(t.x) + ";" + std::to_string(t.y) + ";"
        + "ressources{" + std::to_string(t.ressources.food) + ';' + std::to_string(t.ressources.linemate) + ';'
        + ';' +std::to_string(t.ressources.deraumere) + ';' + std::to_string(t.ressources.sibur) + ';'
        + std::to_string(t.ressources.mendiane) + ';' + std::to_string(t.ressources.thystame) + ';'
        + std::to_string(t.ressources.phiras) + ';' + std::to_string(t.ressources.thystame)
        + "};";
        packed.append(tmp);
        for (int i = 0; i < t.nb_eggs; i++) {
            auto tmp = "egg{" + std::to_string(t.eggs[i].life) + ';' + t.eggs[i].team + "};";
            packed.append(tmp);
        }
    }
    return packed;
};