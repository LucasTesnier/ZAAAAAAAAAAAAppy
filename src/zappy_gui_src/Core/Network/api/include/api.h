/*
** EPITECH PROJECT, 2022
** Project
** File description:
** api
*/

/// \file src/zappy_gui_src/network/api/include/api.h

#ifndef API_H_
    #define API_H_

    #include <stdbool.h>

/// \brief Create a new connection with the server and login it
/// \param host Host address
/// \param port Port to connected
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_try_to_connect_to_server(char *host, long port);

/// \brief Close the current connection with the server
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_try_to_disconnect_to_server(void);

/// \brief Ask the server to do a restart
/// \param configuration New configuration for the restart
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_ask_restart(char *configuration);

/// \brief Return the state of the precedend response of the server
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_get_response_state(void);

/// \brief Get the type of a response. Call after get_response_state
/// \return true If the response is unexpected
/// \return false If the response is expected
bool c_interface_get_unexpected_response_state(void);

/// \brief Return the state of the network connection
/// \return true When everything is alright
/// \return false When the network connexion hase been closed
bool c_interface_get_network_state(void);

/// \brief Get the response for the connect command
/// \return true If connection is okay
/// \return false If connection failed
bool c_interface_get_connect_to_server_response(void);

/// \brief Get the response of the restart command
/// \return true If restart have succeed
/// \return false If restart have failed
bool c_interface_get_restart_response(void);

/// \brief Get the response af an unexpected command
/// \return The parsed string Donc forget to free it (NULL Otherwise)
char *c_interface_get_unexpected_response(void);

#endif /* !API_H_ */
