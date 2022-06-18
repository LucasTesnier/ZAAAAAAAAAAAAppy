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
    {.repr = "211 Successufly joined the game : %s\n",
    .code = 211,
    .params = NULL},
    {.repr = "212 Inventory content : %s\n",
    .code = 212,
    .params = NULL},
    {.repr = "213 Move Forward ok.\n",
    .code = 213,
    .params = NULL},
    {.repr = "214 Turn %s : ok.\n",
    .code = 214,
    .params = NULL},
    {.repr = "215 Look : %s\n",
    .code = 215,
    .params = NULL},
    {.repr = "216 Broadcast %s : ok.\n",
    .code = 216,
    .params = NULL},
    {.repr = "217 Connectnbr : %s\n",
    .code = 217,
    .params = NULL},
    {.repr = "218 Fork : ok.\n",
    .code = 218,
    .params = NULL},
    {.repr = "219 Eject : ok.\n",
    .code = 219,
    .params = NULL},
    {.repr = "220 Take %s : ok.\n",
    .code = 220,
    .params = NULL},
    {.repr = "221 Place %s : ok.\n",
    .code = 221,
    .params = NULL},
    {.repr = "222 Incantation succeed : %s\n",
    .code = 222,
    .params = NULL},
    {.repr = "301 Internal error.\n",
    .code = 301,
    .params = NULL},
    {.repr = "312 Invalid team name : %s\n",
    .code = 312,
    .params = NULL},
    {.repr = "313 No rooms left inside the team : %s\n",
    .code = 313,
    .params = NULL},
    {.repr = "314 Take : ko.\n",
    .code = 314,
    .params = NULL},
    {.repr = "315 Place : ko.\n",
    .code = 315,
    .params = NULL},
    /// ADD HERE RETCODE FOR ERROR
    {.repr = "401 Please login.\n",
    .code = 401,
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
    {.repr = "601 Player dead.\n",
    .code = 601,
    .params = NULL},
    {.repr = "602 Eject : %s\n",
    .code = 602,
    .params = NULL},
    {.repr = "603 Message : %s\n",
    .code = 603,
    .params = NULL},
    {.repr = "700 GUI Message !\n",
    .code = 700,
    .params = NULL},
    {.repr = "701 Start informations : %s\n",
    .code = 701,
    .params = NULL},
    {.repr = "702 Game paused : %s\n",
    .code = 702,
    .params = NULL},
    {.repr = "703 Game start : %s\n",
    .code = 703,
    .params = NULL},
    {.repr = "705 Team Win : %s\n",
    .code = 705,
    .params = NULL},
    {.repr = "706 Team Lose : %s\n",
    .code = 706,
    .params = NULL},
    {.repr = "707 Entity List : %s\n",
    .code = 707,
    .params = NULL},
    {.repr = "708 Map info : %s\n",
    .code = 708,
    .params = NULL},
    {.repr = "710 Restart the game : %s\n",
    .code = 710,
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
