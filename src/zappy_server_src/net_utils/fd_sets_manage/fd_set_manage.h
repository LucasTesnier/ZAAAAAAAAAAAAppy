/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** fd_set_manage
*/

/// \file server/net_utils/fd_sets_manage/fd_set_manage.h

#ifndef FD_SET_MANAGE_H
    #define FD_SET_MANAGE_H

    #include "net_utils.h"

/// \brief Accepts a new client
/// \param srv The server
/// \return true if the client was accepted, false otherwise
bool server_accept_new_client(tcp_server_t *srv);

/// \brief Reads an incoming message from a client,
/// fills the peer_t::input_buffer
/// \param srv The server
/// \param tmp The peer
/// \return true if the message was read, false otherwise
bool server_read_client(tcp_server_t *srv, peer_t *tmp);

/// \brief Writes a message to a client,
/// uses the peer_t::output_buffer
/// \param srv The server
/// \param tmp The peer
bool server_write_client(tcp_server_t *srv, peer_t *tmp);

/// \brief Closes a connection to a client
/// \param srv The server
/// \param tmp The peer
bool server_close_client(tcp_server_t *srv, peer_t *tmp);

/// \brief Sets the peer_t::output_buffer to the current message
/// \param tmp the peer to set the output buffer to
/// \param message the message to set into the buffer
/// \return true if the message was set, false otherwise
bool client_set_output_buffer(peer_t *tmp, char const *message);

/// \brief Fetch the last message from the peer_t::input_buffer
/// \param tmp the peer to fetch the message from
/// \return A pointer to the message, or NULL if there is no message
/// \warning The return pointer is allocated, you must free it
char *fetch_message(peer_t *peer);

#endif /* FD_SET_MANAGE_H */
