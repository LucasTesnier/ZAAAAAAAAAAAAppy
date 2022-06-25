/*
** EPITECH PROJECT, 2022
** Project
** File description:
** density_flutter
*/

/// \file src/zappy_server_src/core/include/density_flutter.h

#ifndef DENSITY_FLUTTER_H_
    #define DENSITY_FLUTTER_H_

    #include "command_hold.h"
    #include "rcodes.h"
    #include "team.h"
    #include "entity/entity.h"
    #include "entity/player.h"
    #include <stdlib.h>

/// \brief Get the default density array
/// \return float* The newly created density array
float *get_default_density_value(void)
{
    float *density = malloc(sizeof(float) * 7);

    if (density == NULL)
        return NULL;
    density[0] = 0.5;
    density[1] = 0.3;
    density[2] = 0.15;
    density[3] = 0.1;
    density[4] = 0.1;
    density[5] = 0.08;
    density[6] = 0.05;
    return density;
}

bool command_get_density(char *arg __attribute__((unused)),
player_list_t *player, server_data_t *serv)
{
    char *res = malloc(sizeof(char) * 1000);
    float *temp = serv->arguments->generation_density;

    if (res == NULL)
        return false;
    res[0] = '\0';
    sprintf(res, "[%f,%f,%f,%f,%f,%f,%f]", temp[0], temp[1], temp[2],
    temp[3], temp[4], temp[5], temp[6]);
    pop_message(player->player_peer);
    print_retcode(801, res, player->player_peer, true);
    free(res);
    return true;
}

/// \brief Parse a string and get the density value stored in it
/// \param arg The string to parse
/// \param density The density value array
static void parse_string_to_density(char *arg, float *density)
{
    char *ptr = arg;

    for (; ptr && *ptr != '\0' && *ptr != '['; ptr++);
    density[0] = atof(ptr + 1);
    for (ptr += 1; ptr && *ptr != '\0' && *ptr != ','; ptr++);
    density[1] = atof(ptr + 1);
    for (ptr += 1; ptr && *ptr != '\0' && *ptr != ','; ptr++);
    density[2] = atof(ptr + 1);
    for (ptr += 1; ptr && *ptr != '\0' && *ptr != ','; ptr++);
    density[3] = atof(ptr + 1);
    for (ptr += 1; ptr && *ptr != '\0' && *ptr != ','; ptr++);
    density[4] = atof(ptr + 1);
    for (ptr += 1; ptr && *ptr != '\0' && *ptr != ','; ptr++);
    density[5] = atof(ptr + 1);
    for (ptr += 1; ptr && *ptr != '\0' && *ptr != ','; ptr++);
    density[6] = atof(ptr + 1);
}

bool command_push_density(char *arg,
player_list_t *player, server_data_t *serv)
{
    float *temp = serv->arguments->generation_density;

    parse_string_to_density(arg, temp);
    dprintf(2, "Change the generation density:\nFood -> %f\nLinemate -> %f\n\
    Deraumere -> %f\nSibur -> %f\nMendiane -> %f\nPhiras -> %f\n\
    Thystame -> %f\n", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5],
    temp[6]);
    pop_message(player->player_peer);
    return print_retcode(802, NULL, player->player_peer, true);
}

#endif /* !DENSITY_FLUTTER_H_ */
