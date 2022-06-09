/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** rcodes
*/

/// \file src/zappy_server_src/core/include/rcodes.h

#ifndef RCODES_H_
    #define RCODES_H_

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include "fd_set_manage.h"

/// \brief The retcodes_s structure contains the representation of the return
/// code as char *, an int which represent the return code, and a array of
/// char * which contains the arguments to be used.
typedef struct retcodes_s {

    /// \brief char * The name of the return code.
    char *repr;

    /// \brief int The return code.
    int code;

    /// \brief char ** The arguments of the return code.
    char **params;
} retcodes_t;

/// \brief The retcodes_s structure contains the representation of the return
static const retcodes_t retcodes[] = {
    {.repr = "200 Success\n",
    .code = 200,
    .params = NULL},
    {.repr = "201 Authentification succeed as : %s\n",
    .code = 201,
    .params = NULL},
    {.repr = "202 Logout succeed as : %s\n",
    .code = 202,
    .params = NULL},
    {.repr = "402 Authentification failed as : %s\n",
    .code = 402,
    .params = NULL},
    {.repr = "501 Command not found : %s\n",
    .code = 501,
    .params = NULL},
    {.repr = "502 Invalid format : %s\n",
    .code = 502,
    .params = NULL},
    {0, 0, 0}
};

/// \brief Get a retcodes_t structure depending on the code passed as
/// parameter.
/// \param int The code to be send.
/// \return A new instance of retcodes_t.
static inline retcodes_t *create_new_repcode(int code)
{
    retcodes_t *retcode = (retcodes_t *) malloc(sizeof(retcodes_t));

    if (!retcode)
        return NULL;
    for (int i = 0; retcodes[i].repr; i++) {
        if (retcodes[i].code == code) {
            memcpy(retcode, &retcodes[i], sizeof(retcodes_t));
            return retcode;
        }
    }
    free(retcode);
    return NULL;
}

/// \brief Print the message code depending on the code passed as parameter.
/// \param int The return code value.
/// \param char **Arguments to be passed to the retcodes_t structure if it is
/// necessary.
static inline bool print_retcode(int code, char *arg, peer_t *peer, bool res)
{
    retcodes_t *retcode = create_new_repcode(code);
    char *command = malloc(sizeof(char) * ((arg) ? strlen(arg) +
    strlen(retcode->repr) - 1 : strlen(retcode->repr) + 1));

    if (command == NULL)
        return res;
    if (arg)
        sprintf(command, retcode->repr, arg);
    else
        sprintf(command, retcode->repr);
    client_set_output_buffer(peer, command);
    free(command);
    free(retcode);
    return res;
}

/// \brief Compute all the rcodes args to a char *
/// \param param Args to compute
/// \return char* Newly created string
static inline char *cretcodes(char **param)
{
    int size = 0;
    char *res = NULL;
    int total_size = 0;

    for (; param[size] != NULL; size++);
    for (int i = 0; i < size; i++)
        total_size += strlen(param[i]);
    res = malloc(sizeof(char) * (total_size + 2 * size));
    if (res == NULL)
        return NULL;
    res[0] = '\0';
    for (int i = 0; i < size - 1; i++) {
        strcat(res, param[i]);
        res[strlen(res) + 1] = '\0';
        res[strlen(res)] = ':';
    }
    strcat(res, param[size - 1]);
    return res;
}

#endif /* !RCODES_H_ */