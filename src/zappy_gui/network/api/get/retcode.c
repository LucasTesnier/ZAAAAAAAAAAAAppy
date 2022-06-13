/*
** EPITECH PROJECT, 2022
** Project
** File description:
** retcode
*/

/// \file src/zappy_gui_src/network/api/get/retcode.c

#include "intern_data.h"
#include "api.h"
#include <stdlib.h>

/// Representation of an invalid retcodes
static const retcodes_t invalid_retcode = {-1, -1, EXPECTED};

/// List of all the possible retcodes
static const retcodes_t retcodes[] = {
    {200, 0, EXPECTED},
    {201, 1, EXPECTED},
    {202, 1, EXPECTED},
    {402, 1, EXPECTED},
    {501, 1, EXPECTED},
    {502, 1, EXPECTED},
    {-1, -1, EXPECTED}
};

retcodes_t get_retcodes(void)
{
    char *temp = NULL;

    if (client_data == NULL || !client_data->current_response)
        return invalid_retcode;
    temp = strndup(client_data->current_response, 3);
    if (temp == NULL)
        return invalid_retcode;
    for (int i = 0; retcodes[i].number != -1; i++) {
        if (atoi(temp) == retcodes[i].number) {
            free(temp);
            return retcodes[i];
        }
    }
    free(temp);
    return invalid_retcode;
}

char *get_retcode_arg(retcodes_t ret)
{
    size_t size = 0;

    if (client_data == NULL || !client_data->current_response)
        return NULL;
    if (ret.arg_n == 0)
        return NULL;
    for (; size < strlen(client_data->current_response); size++)
        if (client_data->current_response[size] == ':')
            break;
    return strdup(client_data->current_response + size + 1);
}