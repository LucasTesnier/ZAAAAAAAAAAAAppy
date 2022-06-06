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

    /// \brief Return value when operation success
    #define SUCCESS 0

    /// \brief Return value when operation failed
    #define FAILED 84

///
/// \brief List of all the different client types
///
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
    /// ADD THE GAME DATA OF player HERE
} player_list_t;

/// \brief Major data for the server
typedef struct server_data_s {
    /// Network instance of NetUtils
    zappy_server_t *server;
    /// List of all the active players
    player_list_t **active_players;
    /// Size of the list
    size_t active_player_n;
    /// ADD ALL THE ARGS HERE
} server_data_t;

/// \brief Init the server data structure
/// \param port Port to setup the serveur
/// \return server_data_t* Newly created server_data
server_data_t *init_server_data(long port);

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
