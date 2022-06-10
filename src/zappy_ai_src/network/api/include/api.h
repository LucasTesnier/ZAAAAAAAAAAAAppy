/*
** EPITECH PROJECT, 2022
** Project
** File description:
** api
*/

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

#endif /* !API_H_ */
