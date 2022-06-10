/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** my_zappy_server
*/

/// \file src/zappy_server_src/core/include/my_zappy_server.h

#ifndef MY_ZAPPY_SERVER_H
    #define MY_ZAPPY_SERVER_H

    #include "net_utils.h"
    #include <stdlib.h>
    #include <stdbool.h>

/// \brief Wraps the application and network side of the zappy srever
typedef struct zappy_server_s {

    /// The network layer, imported from net_utils
    tcp_server_t *network_server;

    /// Represents the state of the server (running 1, stopped 0)
    bool state;
} zappy_server_t;

/// \brief creates a new zappy server
/// \param port The port the server will listen to
/// \param size_queue The size of the listen queue
/// \return The newly created server
zappy_server_t *create_new_server(long port, int size_queue);

/// \brief Destroy a zappy server
/// \param server Zappy server to destroy
void destroy_zappy_server(zappy_server_t *server);

#endif /* MY_ZAPPY_SERVER_H */
