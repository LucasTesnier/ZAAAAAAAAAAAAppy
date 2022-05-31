/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** enum
*/

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
typedef enum player_status_e player_status;

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
typedef enum player_level_e player_level;

enum player_orientation_e{
    ORIENTATIONUNDEFINED = 0,
    NORTH,
    SOUTH,
    EAST,
    WEST
};
typedef enum player_orientation_e player_orientation;

enum game_status_e{
    GAMESTATUSUNDEFINED = 0,
    PAUSE,
    WIN,
    LOOSE
};
typedef enum game_status_e game_status;

struct ressource_s{
    char *name;
    int quantity;
};
typedef struct ressource_s ressource_t;

// static const ressource_t ressources[] = {
//     {.name = "linemate", .quantity = 0},
//     {.name = "deraumere", .quantity = 0},
//     {.name = "sibur", .quantity = 0},
//     {.name = "mendiane", .quantity = 0},
//     {.name = "phiras", .quantity = 0},
//     {.name = "thystame", .quantity = 0},
//     {.name = 0, .quantity = 0},
// };

struct egg_s{
    char *team;
    int life;
};
typedef struct egg_s egg_t;

struct player_s {
    int x;
    int y;
    int life;
    int action_time;
    player_status status_player;
    ressource_t *inventory;
    char *team_name;
    player_level level;
    player_orientation orientation;
};
typedef struct player_s player_t;

struct tile_s {
    int x;
    int y;
    ressource_t *ressources;
    egg_t *eggs;
};
typedef struct tile_s tile_t;

struct data_s {
    player_t *players;
    tile_t *tiles;
    game_status status;
    int game_time;
};
typedef struct data_s data_t;
