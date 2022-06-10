/*
** EPITECH PROJECT, 2022
** Project
** File description:
** intern_data
*/

#ifndef INTERN_DATA_H_
    #define INTERN_DATA_H_

    #include "client_utils.h"

/// \brief Wraps the appplication and network sidde of the zappy server
typedef struct zappy_client_s {
    /// The network layer, imported from client_net_utils
    client_net_server_t *net_srv;

    /// Runs a connected client by sending and
    /// receiving messages to the associated server
    void (*run)(struct zappy_client_s *);

    /// Stop a connected client and destroy all associated ressources
    void (*stop)(struct zappy_client_s *);

    /// Display prompt
    bool prompt_display;
} zappy_client_t;

/// Pointer to the client network data
extern volatile zappy_client_t *client_data;

/// \brief Initializes the zappy client with the given ip and port
/// \param ip The dotted, null terminated ip address of the server
/// \param port The port number of the server
/// \return A pointer to the zappy client
/// or NULL if the connection to the server failed
zappy_client_t *zappy_client_create(const char *ip, long port);

/// \brief Runs a connected client by sending and
/// receiving messages to the associated server
/// \param server The zappy client to run
void run_zappy_client(zappy_client_t *server);

/// \brief Stop a connected client and destroy all associated ressources
/// \param server The zappy client to stop
void stop_zappy_client(zappy_client_t *server);

#endif /* !INTERN_DATA_H_ */
