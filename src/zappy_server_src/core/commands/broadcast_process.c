/*
** EPITECH PROJECT, 2022
** Project
** File description:
** broadcast_process
*/

/// \file src/zappy_server_src/core/commands/broadcast_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/entity.h"
#include "broadcast.h"

static int broadcast_directionnal_end(broadcast_data_t *broad_data)
{
    free(broad_data->direction_list);
    free(broad_data->movement_list);
    return broad_data->count;
}

static bool broadcast_do_a_movement(broadcast_data_t *broad_data,
position_t dest, position_t map_size, int count)
{
    for (int i = 0; i < broad_data->movement_list[count]; i++) {
        broad_data->count++;
        broadcast_apply_direction_on_position(&broad_data->current_pos,
        broad_data->direction_list[count]);
        if (resolve_directionnal_position(dest, broad_data->current_pos,
        map_size))
            return true;
    }
    return false;
}

static bool broadcast_do_movement(broadcast_data_t *broad_data,
position_t dest, position_t map_size)
{
    for (int i = 0; i < 5; i++) {
        if (broadcast_do_a_movement(broad_data, dest, map_size, i))
            return true;
        if (resolve_directionnal_position(dest, broad_data->current_pos,
        map_size))
            return true;
    }
    broad_data->turn_number += 1;
    return false;
}

int get_directionnal_value(position_t player, position_t map_size,
position_t dest, enum player_orientation_e orientation)
{
    broadcast_data_t broad_data;

    if (resolve_directionnal_position(dest, player, map_size))
        return 0;
    broad_data.count = 0;
    broad_data.turn_number = 1;
    broad_data.current_pos = player;
    broad_data.direction_list = broadcast_get_direction_list(orientation);
    if (broad_data.direction_list == NULL)
        return - 1;
    while (1) {
        broad_data.movement_list = get_movement_list(broad_data.turn_number);
        if (broadcast_do_movement(&broad_data, dest, map_size))
            break;
        free(broad_data.movement_list);
    }
    return broadcast_directionnal_end(&broad_data);
}