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

/// \brief Ask to see the inventory of a player
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_ask_inventory(void);

/// \brief Ask to move forward
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_ask_forward(void);

/// \brief Ask to turn right
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_ask_right(void);

/// \brief Ask to turn left
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_ask_left(void);

/// \brief Ask to look
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_ask_look(void);

/// \brief Ask to broadcast
/// \param message The message to send
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_ask_broadcast(char *message);

/// \brief Ask to get the connectable
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_ask_connectable(void);

/// \brief Ask to fork
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_ask_fork(void);

/// \brief Ask to eject
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_ask_eject(void);

/// \brief Ask to take
/// \param object The object to take
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_ask_take(char *object);

/// \brief Ask to place
/// \param object The object to place
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_ask_place(char *object);

/// \brief Ask to start an incantation
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_ask_incantation(void);

/// \brief Return the state of the precedend response of the server
/// \return true When operation succeed
/// \return false When operation failed
bool c_interface_get_response_state(void);

/// \brief Get the type of a response. Call after get_response_state
/// \return true If the response is unexpected
/// \return false If the response is expected
bool c_interface_get_unexpected_response_state(void);

/// \brief Flush the asked data. Call after a ask function
/// \return true When the asked data has been send to the server
/// \return false When the ased data has not been send
bool c_interface_flush_asked_data(void);

/// \brief Return the state of the network connection
/// \return true When everything is alright
/// \return false When the network connexion hase been closed
bool c_interface_get_network_state(void);

/// \brief Get the response for the connect command
/// \return true If connection is okay
/// \return false If connection failed
bool c_interface_get_connect_to_server_response(void);

/// \brief Get the response for the join command
/// \return The game parameters
char *c_interface_get_join_response(void);

/// \brief Get the response for the inventory command
/// \return The inventory content, NULL otherwise
char *c_interface_get_inventory_response(void);

/// \brief Get the response for the forward command
/// \return true If connection is okay
/// \return false If connection failed
bool c_interface_get_forward_response(void);

/// \brief Get the response for the right command
/// \return true If connection is okay
/// \return false If connection failed
bool c_interface_get_right_response(void);

/// \brief Get the response for the left command
/// \return true If connection is okay
/// \return false If connection failed
bool c_interface_get_left_response(void);

/// \brief Get the response for the look command
/// \return The look content, NULL otherwise
char *c_interface_get_look_response(void);

/// \brief Get the response for the broadcast command
/// \return true If connection is okay
/// \return false If connection failed
bool c_interface_get_broadcast_response(void);

/// \brief Get the response for the connectable command
/// \return The connectnbr value
int c_interface_get_connectable_response(void);

/// \brief Get the response for the fork command
/// \return true If connection is okay
/// \return false If connection failed
bool c_interface_get_fork_response(void);

/// \brief Get the response for the eject command
/// \return true If connection is okay
/// \return false If connection failed
bool c_interface_get_eject_response(void);

/// \brief Get the response for the take command
/// \return true If connection is okay
/// \return false If connection failed
bool c_interface_get_take_response(void);

/// \brief Get the response for the place command
/// \return true If connection is okay
/// \return false If connection failed
bool c_interface_get_place_response(void);

/// \brief Get the response for the incantation command
/// \return The connectnbr value
int c_interface_get_incantation_response(void);

/// \brief Get the content of an unexpected response
/// \return The unexpected response content, NULL otherwise
char *c_interface_get_unexpected_response(void);

#endif /* !API_H_ */
