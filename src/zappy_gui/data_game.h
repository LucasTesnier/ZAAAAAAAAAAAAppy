/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** enum
*/

/// \file src/zappy_gui/data_game.h
/// \brief data_game : struct and enum shared between server and gui

/// \brief status of the player
enum player_status_e {
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
typedef enum player_status_e player_status;

/// \brief level of the player from 0 to 8
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

/// \brief orientation of the player
enum player_orientation_e{
    ORIENTATIONUNDEFINED = 0,
    NORTH,
    SOUTH,
    EAST,
    WEST
};
typedef enum player_orientation_e player_orientation;

/// \brief status of the game
enum game_status_e{
    GAMESTATUSUNDEFINED = 0,
    PAUSE,
    WIN,
    LOOSE
};
typedef enum game_status_e game_status;

/// \brief ressources of a player or of a tile
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

/// \brief player
struct player_s {
    /// \brief position x of the player
    int x;
    /// \brief position y of the player
    int y;
    /// \brief life of the player
    int life;
    /// \brief name of the player team
    char *team_name;
    /// \brief time of the player action
    int action_time;
    /// \brief info the the player action
    char *action_info;
    /// \brief status of the player
    player_status status_player;
    /// \brief inventory of the player
    ressource_t inventory;
    /// \brief level of the player
    player_level level;
    /// \brief orientation of the player
    player_orientation orientation;
};
typedef struct player_s player_t;

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
    /// \brief number of player on the game
    int nb_players;
    /// \brief all players of the game
    player_t *players;
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
