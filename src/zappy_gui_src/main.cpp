// /*
// ** EPITECH PROJECT, 2022
// ** zappy
// ** File description:
// ** main
// */

// /// \file src/zappy_gui_src/main.cpp

// #include "ZappyGuiException.hpp"
// #include "Core.hpp"
// #include <iostream>
// #include <string>

// using namespace gui;

// static int usage(int ac, char **av)
// {
//     if (ac == 2 && (std::string(av[1]) == "-h" || std::string(av[1]) == "--help")) {
//         std::cerr << "USAGE: ./zappy_ai -p port -h machine\n\tport\t is the port number\n\tmachine\t is the name of the machine; localhost by default" << std::endl;
//         return -1;
//     }
//     return 0;
// }

// int main(int ac, char **av)
// {
//     Core core;

//     if (usage(ac, av) < 0)
//         return 0;
//     try {
//         core.setup(ac, av);
//         core.run();
//     } catch (CoreException &e) {
//         std::cerr << e.what() << std::endl;
//         return 84;
//     }
//     return 0;
// }

#include <iostream>
#include <string>
#include "entity.h"
#include "tile.h"
#include "player.h"
#include "container.h"

char *pack(entity_t *);

int main(int ac, char **av)
{
    player_t *player = create_player(strdup("guigui"));
    tile_t *tile = create_new_tile();
    player->inventory = new_container();
    entity_t *e = (entity_t*)malloc(sizeof(entity_t));
    entity_t *g = (entity_t*)malloc(sizeof(entity_t));
    e->type = ENTITY_TILE_TYPE;
    e->position = {.x = 24, .y = 42};
    e->data = tile;
    g->type = ENTITY_PLAYER_TYPE;
    g->position = {.x = 12, .y = 22};
    g->data = player;
    char *t = pack(g);
    char *test = pack(e);
    std::cout << "here:" << std::endl;
    std::cout << test << std::endl;
    std::cout << t << std::endl;
}

