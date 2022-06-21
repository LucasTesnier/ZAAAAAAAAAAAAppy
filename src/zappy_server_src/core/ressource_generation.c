/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ressource_generation
*/

/// \file src/zappy_server_src/core/ressource_generation.c

#include "scheduler/scheduler.h"
#include "server.h"
#include "entity/player.h"
#include "command_hold.h"
#include "map.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void scheduler_update_ressource(scheduler_t *self, server_data_t *serv)
{
    time_t now = time(NULL);
    int tick = floor((now - self->ressource) * self->freq);

    if (!self || tick < 20)
        return;
    generate_new_ressource(serv->map);
    send_map_info(serv);
    self->ressource = time(NULL);
}