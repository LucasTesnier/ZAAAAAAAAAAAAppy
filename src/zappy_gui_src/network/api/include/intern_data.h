/*
** EPITECH PROJECT, 2022
** Project
** File description:
** intern_data
*/

/// \file src/zappy_gui_src/network/api/include/intern_data.h

#ifndef INTERN_DATA_H_
    #define INTERN_DATA_H_

    #include "client_utils.h"

/// \brief Wraps the appplication and network sidde of the zappy server
typedef struct zappy_client_s {
    /// The network layer, imported from client_net_utils
    client_net_server_t *net_srv;
    /// Stop a connected client and destroy all associated ressources
    void (*stop)(void);
    /// Current response from the server
    char *current_response;
} zappy_client_t;

/// \brief Diferent type of retcode 
typedef enum retcode_type_s {
    /// When the retcode is from an expected response
    EXPECTED,
    /// When the retcode is from a non expected response
    UNEXPECTED
} retcode_type_t;

/// \brief Define all the data in a retcode
typedef struct retcodes_s {
    /// Number of the retcodes
    int number;
    /// Number of arguments
    int arg_n;
    /// Type of the retcodes
    retcode_type_t type;
} retcodes_t;

/// \brief Get the retcode of the current response
/// \return The matching retcode
retcodes_t get_retcodes(void);

/// \brief Pointer to the network data of the client
extern zappy_client_t *client_data;

/// \brief Stop a connected client and destroy all associated ressources
void stop_zappy_client(void);

/// \brief Return the args after the retcode
/// \param ret The identified retcode
/// \return The parsed arguments remeber to free it (NULL if not)
char *get_retcode_arg(retcodes_t ret);

#endif /* !INTERN_DATA_H_ */