/*
** EPITECH PROJECT, 2022
** mes_equipes
** File description:
** server_read_client
*/

/// \file server/net_utils/fd_sets_manage/server_read_client.c

#include "net_utils.h"
#include "fd_set_manage.h"

char *fetch_message(peer_t *peer)
{
    if (!peer)
        return NULL;
    if (!peer->pending_read)
        return NULL;
    return strdup(peer->input_buffer[0]);
}

void pop_message(peer_t *peer)
{
    if (!peer)
        return;
    if (!peer->pending_read)
        return;
    for (int i = 0; i < peer->pending_read - 1; i++) {
        peer->input_buffer[i][0] = '\0';
        strcat(peer->input_buffer[i], peer->input_buffer[i + 1]);
    }
    peer->pending_read -= 1;
}

/// \brief Get the position of the last second \n when two \n are followed
/// \param buffer The buffer to parse
/// \return int Index of the last second \n when two \n are followed
static int get_command_end_pos(char *buffer)
{
    int pos = -1;

    for (int i = 0; buffer && buffer[i] && buffer[i + 1] != '\0'; i++) {
        if (buffer[i] == '\n' && buffer[i + 1] == '\n') {
            pos = i + 1;
            break;
        }
    }
    return pos;
}

/// \brief Cross and parse a readed data to extract all the command
/// \param read The readed data to parse
/// \param tmp The peer where the info are stored
static void parse_read_for_stack(char *read, peer_t *tmp)
{
    char *buffer = read;
    int count = 0;

    for (; buffer && *buffer != '\0';) {
        if (tmp->pending_read >= 10)
            break;
        count = get_command_end_pos(buffer);
        if (count == -1)
            break;
        strncpy(tmp->input_buffer[tmp->pending_read], buffer, count + 1);
        tmp->input_buffer[tmp->pending_read][count + 1] = '\0';
        tmp->pending_read++;
        buffer += count + 1;
        if (*buffer == '\n')
            buffer += 1;
    }
}

bool server_read_client(tcp_server_t *srv, peer_t *tmp)
{
    ssize_t read_size;
    char temp[MAX_MSG];

    if (!tmp || !srv)
        return false;
    if (tmp->pending_read >= 10)
        return false;
    read_size = read(tmp->sock_fd, temp, MAX_MSG);
    if (read_size < 0)
        return false;
    if (read_size == 0) {
        ZAPPY_LOG("Client disconnected");
        server_close_client(srv, tmp);
        return false;
    }
    temp[read_size] = '\0';
    parse_read_for_stack(temp, tmp);
    return true;
}
