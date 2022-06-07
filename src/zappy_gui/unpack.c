/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** unpack
*/

#include "data_game.h"
#include <stdlib.h>

static const ressource_t inventory[] = {
    {.name = "linemate", .quantity = 0},
    {.name = "deraumere", .quantity = 0},
    {.name = "sibur", .quantity = 0},
    {.name = "mendiane", .quantity = 0},
    {.name = "phiras", .quantity = 0},
    {.name = "thystame", .quantity = 0},
    {.name = "food", .quantity = 0},
    {.name = 0, .quantity = 0},
};

static const ressource_t ressources[] = {
    {.name = "linemate", .quantity = 0},
    {.name = "deraumere", .quantity = 0},
    {.name = "sibur", .quantity = 0},
    {.name = "mendiane", .quantity = 0},
    {.name = "phiras", .quantity = 0},
    {.name = "thystame", .quantity = 0},
    {.name = "food", .quantity = 0},
    {.name = 0, .quantity = 0},
};

static const egg_t eggs[] = {
    {.team = 0, .life = 0},
};

data_t unpack(char *data_string)
{
    data_t data;
    return data;
}