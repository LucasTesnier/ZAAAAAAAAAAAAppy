/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** tcp_server
*/

/// \file server/net_utils/tcp_server.c

#include "net_utils.h"

/// \brief bind the socket to the port
/// \param srv the server to update
/// \param port the port to bind
/// \param size_queue the size of the listen queue
/// \return true if the bind is successful, false otherwise
static bool bind_and_listen_on_socket(tcp_server_t *srv, long port,
int size_queue)
{
    srv->sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (srv->sock_fd < 0) {
        ZAPPY_LOG("socket");
        return false;
    }
    memset(&srv->self, 0, sizeof(srv->self));
    srv->self.sin_family = AF_INET;
    srv->self.sin_port = htons(port);
    srv->self.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(srv->sock_fd, (struct sockaddr *) &srv->self,
        sizeof(struct sockaddr)) < 0) {
        ZAPPY_LOG("bind");
        return false;
    }
    if (listen(srv->sock_fd, size_queue) < 0) {
        ZAPPY_LOG("listen");
        return false;
    }
    return true;
}

tcp_server_t *create_tcp_server(long port, int size_queue)
{
    tcp_server_t *server = malloc(sizeof(tcp_server_t));

    if (!server)
        ZAPPY_LOG("malloc");
    server->port = htons(port);
    if (!bind_and_listen_on_socket(server, port, size_queue)) {
        free(server);
        return (NULL);
    }
    FD_ZERO(&server->read_fds);
    FD_ZERO(&server->write_fds);
    FD_ZERO(&server->err_fds);
    FD_SET(server->sock_fd, &server->read_fds);
    FD_SET(server->sock_fd, &server->write_fds);
    CIRCLEQ_INIT(&server->peers_head);
    server->state = true;
    return (server);
}
