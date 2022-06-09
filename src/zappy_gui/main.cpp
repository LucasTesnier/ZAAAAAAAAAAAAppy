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
    data.game_time = 42;
    data.players = (player_t *)malloc(sizeof(player_t));
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
    data.status = PAUSE;
    std::string t;
    std::cout << "test\n";
    t = pack(data);
    std::cout << t << std::endl;
}