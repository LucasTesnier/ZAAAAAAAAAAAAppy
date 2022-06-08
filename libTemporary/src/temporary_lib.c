/*
** EPITECH PROJECT, 2022
** temporary_lib.cpp
** File description:
** Created by hjulien,
*/

#include "temporary_lib.h"
#include <stdbool.h>
#include <stddef.h>

static const char *look_response = "1:1:1:1:1:1:1;1:1:1:1:1:1:1;1:1:1:1:1:1:1;1:1:1:1:1:1:1";
static const char *inventory_reponse = "2000:100:100:100:100:100:100:100";
static const int new_level = 2;

//------------------------------------------------Python try to connect to the machine and port------------------------------------//

bool c_interface_try_to_connect_to_server(const char *ip, const int port)
{
    (void)(ip);
    (void)(port);
    return true;
}

//------------------------------------------------Python send a demand to C interface----------------------------------------------//

bool c_interface_ask_forward()
{
    return true;
}

bool c_interface_ask_right()
{
    return true;
}

bool c_interface_ask_left()
{
    return true;
}

bool c_interface_ask_look()
{
    return true;
}

bool c_interface_ask_broadcast(const char *message)
{
    (void)(message);
    return true;
}

bool c_interface_ask_connectable()
{
    return true;
}

bool c_interface_ask_fort()
{
    return true;
}

bool c_interface_ask_eject()
{
    return true;
}

bool c_interface_ask_take(const char *resource)
{
    (void)(resource);
    return true;
}

bool c_interface_ask_place(const char *resource)
{
    (void)(resource);
    return true;
}

bool c_interface_ask_incantation()
{
    return true;
}

bool c_interface_ask_join(const char *teamName)
{
    (void)(teamName);
    return true;
}

//------------------------------------------------------Python ask for the response state----------------------------------------//

bool c_interface_get_response_state()
{
    return true;
}

bool c_interface_get_unexpected_response_state()
{
    return false;
}

//------------------------------------------------------Python ask for the response content----------------------------------------//

bool c_interface_get_forward_response()
{
    return true;
}

bool c_interface_get_left_response()
{
    return true;
}

bool c_interface_get_right_response()
{
    return true;
}

/*
 * @brief  : tiles separator ";" / resources seperator ":"
 * @format : "food:linemate:deraumere:sibur:mendiane:phiras:thystame:"
 * @return : In this example we can see 3 tiles with one resource of each component
 */
const char *c_interface_get_look_response()
{
    return look_response;
}

/*
 * @brief  : resources seperator ":"
 * @format : "linemate:deraumere:sibur:mendiane:phiras:thystame:"
 * @return : In this example we can see 3 tiles with one resource of each component
 */
const char *c_interface_get_inventory_response()
{
    return inventory_reponse;
}

bool c_interface_get_broadcast_response()
{
    return true;
}

bool c_interface_get_connectable_response()
{
    return true;
}

bool c_interface_get_fork_response()
{
    return true;
}

bool c_interface_get_eject_response()
{
    return true;
}

bool c_interface_get_take_response()
{
    return true;
}

bool c_interface_get_place_response()
{
    return true;
}

int c_interface_get_incantation_response()
{
    return new_level;
}

char **c_interface_get_join_response()
{
    return NULL;
}

char *c_interface_get_unexpected_response()
{
    return NULL;
}