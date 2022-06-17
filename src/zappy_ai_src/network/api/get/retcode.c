/*
** EPITECH PROJECT, 2022
** Project
** File description:
** retcode
*/

/// \file src/zappy_ai_src/network/api/get/retcode.c

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
    {211, 1, EXPECTED},
    {212, 1, EXPECTED},
    {213, 0, EXPECTED},
    {214, 0, EXPECTED},
    {215, 1, EXPECTED},
    {216, 0, EXPECTED},
    {217, 1, EXPECTED},
    {218, 0, EXPECTED},
    {219, 0, EXPECTED},
    {220, 0, EXPECTED},
    {301, 0, EXPECTED},
    {312, 1, EXPECTED},
    {313, 1, EXPECTED},
    {314, 0, EXPECTED},
    {401, 0, EXPECTED},
    {402, 1, EXPECTED},
    {501, 1, EXPECTED},
    {502, 1, EXPECTED},
    {-1, -1, EXPECTED}
};

char *retcode_get_arg(void)
{
    size_t pos = 0;
    char *res = NULL;

    if (client_data == NULL || !client_data->current_response)
        return NULL;
    for (; pos < strlen(client_data->current_response) - 1; pos++)
        if (client_data->current_response[pos] == ':')
            break;
    if (client_data->current_response[pos + 1] == '\0')
        return NULL;
    res = strdup(client_data->current_response + pos + 2);
    if (res == NULL)
        return NULL;
    res[strlen(res) - 1] = '\0';
    return res;
}

bool retcode_exit(bool state)
{
    if (!client_data || !client_data->current_response)
        return state;
    free(client_data->current_response);
    client_data->current_response = NULL;
    return state;
}

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