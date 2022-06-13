/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** enum
*/

/// \file src/zappy_gui/data_game.h
/// \brief data_game : struct and enum shared between server and gui

/// \brief status of the tochange
enum tochange_status_e {
    /// \brief undefined status
    STATUSUNDEFINED = 0,
    /// \brief stationary status
    STATIONARY,
    /// \brief moving status
    MOVING,
    /// \brief rotating status
    ROTATING,
    /// \brief incantation status
    INCANTATION,
    /// \brief laying egg status
    LAYING_EGG,
    /// \brief taking object status
    TAKE_OBJECT,
    /// \brief setting object status
    SET_OBJECT,
    /// \brief dying status
    DYING,
    /// \brief broadcasting status
    BROADCASTING
};
typedef enum tochange_status_e tochange_status;

/// \brief level of the tochange from 0 to 8
enum tochange_level_e{
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
typedef enum tochange_level_e tochange_level;

/// \brief orientation of the tochange
enum tochange_orientation_e{
    ORIENTATIONUNDEFINED = 0,
    NORTH,
    SOUTH,
    EAST,
    WEST
};
typedef enum tochange_orientation_e tochange_orientation;

/// \brief status of the game
enum game_status_e{
    GAMESTATUSUNDEFINED = 0,
    PAUSE,
    WIN,
    LOOSE
};
typedef enum game_status_e game_status;

/// \brief ressources of a tochange or of a tile
struct ressource_s{
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
};
typedef struct ressource_s ressource_t;

/// \brief egg belonging to a team and with a life
struct egg_s{
    /// \brief team of the egg
    char *team;
    /// \brief life of the egg
    int life;
};
typedef struct egg_s egg_t;

/// \brief tochange
struct tochange_s {
    /// \brief position x of the tochange
    int x;
    /// \brief position y of the tochange
    int y;
    /// \brief life of the tochange
    int life;
    /// \brief name of the tochange team
    char *team_name;
    /// \brief time of the tochange action
    int action_time;
    /// \brief info the the tochange action
    char *action_info;
    /// \brief status of the tochange
    tochange_status status_tochange;
    /// \brief inventory of the tochange
    ressource_t inventory;
    /// \brief level of the tochange
    tochange_level level;
    /// \brief orientation of the tochange
    tochange_orientation orientation;
};
typedef struct tochange_s tochange_t;

/// \brief tile
struct tile_s {
    /// \brief position x of the tile
    int x;
    /// \brief position y of the tile
    int y;
    /// \brief ressources of the tile
    ressource_t ressources;
    int nb_eggs;
    /// \brief eggs of the tile
    egg_t *eggs;
};
typedef struct tile_s tile_t;

/// \brief data
struct data_s {
    /// \brief number of tochange on the game
    int nb_tochanges;
    /// \brief all tochanges of the game
    tochange_t *tochanges;
    /// \brief number of tiles on the game
    int nb_tiles;
    /// \brief all tiles of the game
    tile_t *tiles;
    /// \brief status of the game
    game_status status;
    /// \brief time between the start of the game and now
    int game_time;
};
typedef struct data_s data_t;
