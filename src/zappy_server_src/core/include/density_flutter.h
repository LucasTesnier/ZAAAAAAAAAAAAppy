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
    (void) serv;
    pop_message(player->player_peer);
    return print_retcode(801, "[...]", player->player_peer, true);
}

bool command_push_density(char *arg __attribute__((unused)),
player_list_t *player, server_data_t *serv)
{
    (void) serv;
    pop_message(player->player_peer);
    return print_retcode(802, "[...]", player->player_peer, true);
}

#endif /* !DENSITY_FLUTTER_H_ */
