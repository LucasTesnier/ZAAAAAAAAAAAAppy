/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** main
*/
/// \file src/zappy_gui/main.cpp

#include <iostream>
#include <string>
#include "entity.h"
#include "player.h"
#include "container.h"

char *pack(entity_t *);

int main(int ac, char **av)
{
    player_t *player = create_player(strdup("guigui"));
    player->inventory = new_container();
    entity_t *e = (entity_t*)malloc(sizeof(entity_t));
    e->type = 0;
    e->position = {.x = 24, .y = 42};
    // e->entities = NULL;
    e->data = player;
    char *test = pack(e);
    std::cout << "here:" << std::endl;
    std::cout << test << std::endl;
    if (ac == 2 && (std::string(av[1]) == "-h" || std::string(av[1]) == "--help")) {
        std::cerr << "USAGE: ./zappy_ai -p port -h machine" <<
        std::endl << "\tport\t is the port number" <<std::endl <<
        "\tmachine\t is the name of the machine; localhost by default" <<
        std::endl;
        return 84;
    }
    return 0;
}
