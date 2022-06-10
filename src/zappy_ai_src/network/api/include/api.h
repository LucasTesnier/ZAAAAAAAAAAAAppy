/*
** EPITECH PROJECT, 2022
** Project
** File description:
** api
*/

/// \file src/zappy_ai_src/network/api/include/api.h

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

/// \brief Ask to join a team in the server
/// \param team_name Name of the team to join
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_ask_join(char *team_name);

/// \brief Return the state of the precedend response of the server
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_get_response_sate(void);

#endif /* !API_H_ */
