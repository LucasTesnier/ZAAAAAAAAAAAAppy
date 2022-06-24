/*
** EPITECH PROJECT, 2022
** Project
** File description:
** incantation_command
*/

/// \file src/zappy_server_src/core/commands/incantation_command.c

#include "command_hold.h"
#include "rcodes.h"
#include "team.h"
#include "entity/player.h"
#include "entity/tile.h"
#include "incantation.h"

/// \brief List of all the incantation data
static const incantation_level_t inc_lvl[] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
};

/// \brief Add the inventory content to the global container
/// \param cont The global container
/// \param inventory The inventory of the player
static void add_inventory_to_container(container_t *cont,
container_t *inventory)
{
    cont->linemate += inventory->linemate;
    cont->deraumere += inventory->deraumere;
    cont->sibur += inventory->sibur;
    cont->mendiane += inventory->mendiane;
    cont->phiras += inventory->phiras;
    cont->thystame += inventory->thystame;
}

/// \brief Verif the state of the incantation
/// \param tile The current tile
/// \param level The level of incantation
/// \return true When operation succeed
/// \return false When operation failed
static bool incantation_verif(entity_wrapper_t *wrapper, unsigned int level,
position_t player_pos)
{
    int total_player = 0;
    container_t cont = {0, 0, 0, 0, 0, 0, 0};
    entity_t *entity = NULL;

    TAILQ_FOREACH(entity, &wrapper->players, entities) {
        if (entity->position.x != player_pos.x
            && entity->position.y != player_pos.y)
            continue;
        if (((player_t *)entity->data)->level >= level)
            total_player++;
        add_inventory_to_container(&cont,
        ((player_t *)entity->data)->inventory);
    }
    if (total_player < inc_lvl[level - 1].player)
        return false;
    if (!comp_inc_lvl_cont(inc_lvl[level - 1], cont))
        return false;
    return true;
}

bool command_incantation(char *arg, player_list_t *player,
server_data_t *serv)
{
    entity_t *player_entity = NULL;
    player_t *player_data = NULL;

    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    player_entity = (entity_t *)player->player_data;
    player_data = (player_t *)player_entity->data;
    if (!incantation_verif(serv->entities, player_data->level,
        player_entity->position))
        return print_retcode(316, NULL, player->player_peer, false);
    if (!scheduler_schedule_event(serv->scheduler,
    ((player_t *)player->player_data->data)->uuid, 300))
        return false;
    player->scheduled_action = find_ai_command_end("/incantation", NULL);
    if (player->scheduled_action == NULL)
        return false;
    player->incantation_position = player_entity->position;
    return true;
}

/// \brief Process 
/// \param serv The server informations
/// \param player The player informations
/// \param tile The current tile
/// \param start_pos The starting position of the incatation
/// \return char* The newly level
static char *incantation_action(server_data_t *serv,
player_t *player, position_t player_pos, position_t start_pos)
{
    char *res = malloc(sizeof(char) * 2);

    if (res == NULL)
        return NULL;
    if (!incantation_verif(serv->entities, player->level, player_pos) ||
    start_pos.x != player_pos.x || start_pos.y != player_pos.y)
        return NULL;
    remove_ressource_randomly(serv->entities, player_pos,
    (container_t) {0, inc_lvl[player->level - 1].linemate,
        inc_lvl[player->level - 1].deraumere, inc_lvl[player->level - 1].sibur,
        inc_lvl[player->level - 1].mendiane,
        inc_lvl[player->level - 1].phiras,
        inc_lvl[player->level - 1].thystame},
    player->level);
    player->level += 7;
    res[0] = '\0';
    sprintf(res, "%i", player->level);
    send_entities_list_info(serv);
    victory_detection(serv, player->team);
    return res;
}

bool command_incantation_end(char *arg, player_list_t *player,
server_data_t *serv)
{
    entity_t *player_entity = NULL;
    player_t *player_data = NULL;
    char *res = NULL;

    if (!player->player_data)
        return print_retcode(401, arg, player->player_peer, false);
    player_entity = (entity_t *)player->player_data;
    player_data = (player_t *)player_entity->data;
    res = incantation_action(serv, player_data, player_entity->position,
    player->incantation_position);
    pop_message(player->player_peer);
    if (res != NULL)
        print_retcode(222, res, player->player_peer, true);
    else
        print_retcode(316, NULL, player->player_peer, false);
    free(res);
    return true;
}
