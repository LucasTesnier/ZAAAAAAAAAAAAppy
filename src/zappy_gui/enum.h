/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** enum
*/

typedef enum player_status_e player_status;
typedef enum player_level_e player_level;
typedef enum player_orientation_e player_orientation;
typedef struct inventory_s inventory_t;

enum player_status_e {
    STATUSUNDEFINED = 0,
    STANDSTILL,
    MOVING,
    ROTATING,
    INCANTATION,
    LAYING_EGG,
    TAKE_OBJECT,
    SET_OBJECT,
    DYING,
    BROADCASTING
};

enum player_level_e{
    LEVELUNDEFINED = 0,
    LEVEL1,
    LEVEL2,
    LEVEL3,
    LEVEL4,
    LEVEL5,
    LEVEL6,
    LEVEL7,
    LEVEL8
};

enum player_orientation_e{
    ORIENTATIONUNDEFINED = 0,
    NORTH,
    SOUTH,
    EAST,
    WEST
};

struct inventory_s{
    char *name;
    int quantity;
};

static const inventory_t inventory[] = {
    {.name = "linemate", .quantity = 0},
    {.name = "deraumere", .quantity = 0},
    {.name = "sibur", .quantity = 0},
    {.name = "mendiane", .quantity = 0},
    {.name = "phiras", .quantity = 0},
    {.name = "thystame", .quantity = 0}
};
