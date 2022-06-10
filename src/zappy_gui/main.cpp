/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** main
*/

#include <iostream>
#include "data_game.h"
#include <string.h>

std::string pack(data_t data);

int main(void)
{
    data_t data;
    data.nb_players = 2;
    data.nb_tiles = 1;
    data.game_time = 42;
    data.players = (player_t *)malloc(sizeof(player_t) * 2);
    data.players[0].x = 2;
    data.players[0].y = 4;
    data.players[0].action_time = 9000;
    data.players[0].team_name = strdup("team guigui");
    data.players[0].level = LEVEL5;
    data.players[0].life = 44;
    data.players[0].orientation = SOUTH;
    data.players[0].status_player = TAKE_OBJECT;
    data.players[0].inventory.food = 1888;
    data.players[0].inventory.linemate = 18;
    data.players[0].inventory.mendiane = 18;
    data.players[0].inventory.deraumere = 18;
    data.players[0].inventory.thystame = 18;
    data.players[0].inventory.sibur = 18;
    data.players[0].inventory.phiras = 18;
    data.players[1].x = 2;
    data.players[1].y = 4;
    data.players[1].action_time = 9000;
    data.players[1].team_name = strdup("team guigui");
    data.players[1].level = LEVEL5;
    data.players[1].life = 44;
    data.players[1].orientation = SOUTH;
    data.players[1].status_player = TAKE_OBJECT;
    data.players[1].inventory.food = 1888;
    data.players[1].inventory.linemate = 18;
    data.players[1].inventory.mendiane = 18;
    data.players[1].inventory.deraumere = 18;
    data.players[1].inventory.thystame = 18;
    data.players[1].inventory.sibur = 18;
    data.players[1].inventory.phiras = 18;
    data.status = PAUSE;
    data.tiles = (tile_t *)malloc(sizeof(tile_t));
    data.tiles->eggs = (egg_t *)malloc(sizeof(egg_t));
    data.tiles[0].nb_eggs = 1;
    data.tiles[0].eggs[0].life = 0;
    data.tiles[0].eggs[0].team = strdup("lala");
    std::string t;
    t = pack(data);
    std::cout << t << std::endl;
}