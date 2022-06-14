/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** pack_utils
*/

/// \file src/zappy_server_src/core/entity/pack_utils.c

#include <stdlib.h>

char *pack_int(int val)
{
    char *tmp;
    char str[80];
    memset(str, 0, 80);

    sprintf(str, "%d", val);
    tmp = (char*)malloc(sizeof(char) * (strlen(str) + 2));
    strcpy(tmp, str);
    strcat(tmp, ";");
    tmp[strlen(str) + 1] = 0;
    return tmp;
}

char *pack_str(char *val)
{
    char *tmp;

    tmp = (char*)malloc(sizeof(char) * (strlen(val) + 2));
    strcpy(tmp, val);
    strcat(tmp, ";");
    tmp[strlen(val) + 1] = 0;
    return tmp;
}

int get_int_len(int val)
{
    char str[80];

    memset(str, 0, 80);
    sprintf(str, "%d", val);
    return strlen(str);
}