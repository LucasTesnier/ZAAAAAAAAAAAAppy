/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** internals
*/

/// \file client/client_net_utils/include/internals.h

#ifndef INTERNALS_H
    #define INTERNALS_H

    #include "client_utils.h"

/// \brief Resets all the fd sets and set the remote server fd inside of them
/// \param server the remote server
void fill_fd_sets(client_net_server_t *server);

#endif /* INTERNALS_H */
