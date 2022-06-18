/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** net_utils
*/

/// \file server/net_utils/include/net_utils.h

#ifndef NET_UTILS_H
    #define NET_UTILS_H

    #include <sys/socket.h>
    #include <sys/select.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/queue.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <unistd.h>
    #include <errno.h>

    /// Defines the maximum size of a message
    #define MAX_MSG 55555

/// \brief Represents a client connection
typedef struct peer_s {
    /// The file descriptor for the socket
    int sock_fd;

    /// The address of the client
    struct sockaddr_in peer_addr;

    /// Indicates if the client is connected
    /// This filed is usefull for any wrapper that needs to know if the client
    /// is still connected or not
    bool connected;

    /// Represents the state of an incoming message
    /// true if the transaction as been started but not finished
    /// false if the transaction has been finished or not started
    /// defaulted to false
    int pending_read;

    /// Represents the state of an outcoming message
    /// true if the transaction as been started but not finished
    /// false if the transaction has been finished or not started
    /// defaulted to false
    bool pending_write;

    /// The buffer for the incoming message
    char input_buffer[10][MAX_MSG];

    /// The buffer for the outcoming message
    char output_buffer[MAX_MSG];

    /// A pointer to the next/prev peer
    CIRCLEQ_ENTRY(peer_s) peers;
} peer_t;

/// \brief Initializes a circular queue of peers
CIRCLEQ_HEAD(peers_head, peer_s);

/// \brief Represents a basic tcp server
typedef struct tcp_server_s {
    /// The file descriptor of the server socket
    int sock_fd;

    /// The port of the server
    uint16_t port;

    /// The address representation of the server
    struct sockaddr_in self;

    /// The collection of clients (network side)
    struct peers_head peers_head;

    /// The collection of file descriptor set that are ready to be read
    fd_set read_fds;

    /// The collection of file descriptor set that are ready to be written
    fd_set write_fds;

    /// The collection of errored file descriptor set
    fd_set err_fds;

    /// The state of the server
    /// true == running / false == stopped
    bool state;

} tcp_server_t;

/// \brief DO NOT USE THIS FUNCTION, USE THE `ZAPPY_LOG` MACRO INSTEAD
static inline void log_error(int line __attribute__((unused)),
    const char *file __attribute__((unused)),
    const char *func __attribute__((unused)),
    const char *msg __attribute__((unused)))
{
    char *errmsg = strerror(errno);

    if (strcmp(errmsg, "Success") == 0)
        dprintf(2, "%s:%d:%s():\n\t%s: %s\n", file, line, func, msg, errmsg);
}

    /// \brief Simple macro used to log a message
    #define ZAPPY_LOG(msg) \
        do {log_error(__LINE__, \
strrchr(__FILE__, '/') + 1, __func__, msg);} while (0)

/// \brief Creates a new client
/// \param sock_fd The client file descriptor
/// \param peer_addr The client address informations
/// \return The new peer
peer_t *new_peer(int fd, struct sockaddr_in addr);

/// \brief Util function to display currently connected clients
/// \param peers_head The head of the circular queue of peers
void display_clients(struct peers_head *peers_head);

/// \brief Create a TCP server
/// \param port Port to listen on
/// \param size_queue The size of the listen queue
/// \return The tcp server
tcp_server_t *create_tcp_server(long port, int size_queue);

/// \brief Add a user to the server.
/// \param srv The server to add the user to.
/// \param username The username of the user to add.
/// \param password The password of the user to add.
/// \warning The password is inserted 'as is' inside the server
/// \return true if the user was added, false otherwise.
bool add_user_to_server(tcp_server_t *srv, char *username, char *password);

/// \brief Update the read and write fd sets according to
/// peer_t::pending_read of every peers connected
/// \param srv The tcp server containing the peers and the w/r/err fd sets
void server_fill_fd_sets(tcp_server_t *srv);

/// \brief Wait for a client update
/// \note This function is a wrapper around select()
/// \param src The tcp server containing the peers and the w/r/err fd sets
/// \param time Select timing 
/// \return 0 if no error, -1 if an error occured
int server_wait(tcp_server_t *srv, struct timeval time);

/// \brief Handle a client update
/// \param srv The tcp server containing the peers and the w/r/err fd sets
/// \return true if a new connection was instanciated false otherwise
bool server_manage_fd_update(tcp_server_t *srv);

/// \brief Retrieve the last added peer to the server
/// \param srv the tcp server containing the peers
static inline peer_t *fetch_last_added_peer(tcp_server_t *srv)
{
    if (!srv)
        return NULL;
    return CIRCLEQ_FIRST(&srv->peers_head);
}

#endif //NET_UTILS_H
