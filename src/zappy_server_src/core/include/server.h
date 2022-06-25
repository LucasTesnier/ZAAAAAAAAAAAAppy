/*
** EPITECH PROJECT, 2022
** Project
** File description:
** server
*/

/// \file src/zappy_server_src/core/include/server.h

#ifndef SERVER_H_
    #define SERVER_H_

    #include "my_zappy_server.h"
    #include "entity/entity.h"
    #include "map.h"
    #include "scheduler/scheduler.h"
    #include "team.h"

    /// \brief Return value when operation success
    #define SUCCESS 0

    /// \brief Return value when operation failed
    #define FAILED 84

/// \brief Pointer to the server state for sigint handle
extern volatile bool *server_state;

/// \brief List of all the different client types
typedef enum client_type_s {
    /// Type for the Graphic Interface
    GUI,
    /// Type for the player
    AI,
    /// Type not defined yet
    UNKNOWN
} client_type_t;

/// \brief Enumeration of the different states of the server
typedef enum player_state_e {
    /// When a player is connected
    CONNECTED,
    /// When a player request the logout command
    TO_LOGOUT,
    /// When the player is logout
    LOGOUT
} player_state_t;

/// \brief Node of a player list
typedef struct player_list_s {
    /// Peer of the network client
    peer_t *player_peer;
    /// State of the client
    bool is_auth;
    /// Login status
    player_state_t disconnected;
    /// Type of the client
    client_type_t type;
    /// Player data
    entity_t *player_data;
    /// Scheduled action
    struct command_data_s *scheduled_action;
    /// Position for incantation
    position_t incantation_position;
} player_list_t;

/// \brief Different settings of the game
typedef struct argument_s {
    /// Port of the server
    long port;
    /// Width of the map
    int width;
    /// Height of the map
    int height;
    /// List of all the teams name
    char **team_list;
    /// Max client number authorized
    int client_nb;
    /// Inverse multiplicative of the time in seconds, (1 / time)
    float freq;
} argument_t;

/// \brief Major data for the server
typedef struct server_data_s {
    /// Network instance of NetUtils
    zappy_server_t *server;
    /// List of all the active players
    player_list_t **active_players;
    /// Size of the list
    size_t active_player_n;
    /// Arguments list
    argument_t *arguments;
    /// Map of the game
    map_t *map;
    /// The internal scheduler
    scheduler_t *scheduler;
    /// All of the entities
    entity_wrapper_t *entities;
    /// List of all the teams
    struct teams_list_s teams;
    /// List of the modified entities that will be sent to the GUI client
    entity_diff_t *modified_entities;
} server_data_t;

/// \brief Command information's and data
typedef struct command_data_s {
    /// Name of the command
    char *name;
    /// Arg of the command (Possibly NULL)
    char *arg;
    /// Function pointer to the command
    bool (*ptr)(char *, player_list_t *, server_data_t *);
} command_data_t;

/// \brief Init the server data structure
/// \param port Port to setup the server
/// \return server_data_t* Newly created server_data
server_data_t *init_server_data(int ac, char **av);

/// \brief Destroy the server_data
/// \param server_data Server_data to destroy
void destroy_server_data(server_data_t *server_data);

/// \brief Add a new player to the server data
/// \param server_data Server data info
/// \return true When operation success
/// \return false When operation failed
bool server_add_player(server_data_t *server_data);

/// \brief Remove a player from the connection list
/// \param server_data Server data info
/// \param player_info player info
void server_remove_player(server_data_t *server_data,
player_list_t *player_info);

/// \brief Remove all the disconnected player
/// \param server_data Server data info
/// \param comp Value to compare the state connexion
void remove_disconnected_player(server_data_t *server_data,
player_state_t comp);

/// \brief Hold the server global loop
/// \param server_data The server informations and data
void server_loop(server_data_t *server_data);

#endif /* !SERVER_H_ */
