/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** team
*/

#include "team.h"
#include <string.h>
#include <stdlib.h>

team_t *create_team(char *name, int max_members)
{
    team_t *team = malloc(sizeof(team_t));

    if (!team)
        return NULL;
    memset(team, 0, sizeof(team_t));
    if (!(team->name = strdup(name)))
        return NULL;
    team->max_members = max_members;
    if (!(team->members_uuid = malloc(sizeof(uuid_t) * 6)))
        return NULL;
    memset(team->members_uuid, 0, sizeof(uuid_t) * 6);
    for (int i = 0; i < 6; i++)
        uuid_clear(team->members_uuid[i]);
    return team;
}

bool add_team(team_t *team, struct teams_list_s *teams)
{
    team_t *tmp = NULL;

    if (!team || !teams)
        return false;
    TAILQ_FOREACH(tmp, teams, teams)
        if (strcmp(tmp->name, team->name) == 0)
            return false;
    TAILQ_INSERT_TAIL(teams, team, teams);
    return true;
}

bool add_user_to_team(team_t* team, uuid_t user_uuid)
{
    if (!team)
        return false;
    if (team->current_members >= team->max_members)
        return false;
    for (int i = 0; i < 6; i++) {
        if (uuid_compare(team->members_uuid[i], user_uuid) == 0)
            return false;
        if (uuid_is_null(team->members_uuid[i])) {
            uuid_copy(team->members_uuid[i], user_uuid);
            team->current_members++;
            return true;
        }
    }
    return true;
}

team_t *get_team_by_name(char *name, struct teams_list_s *teams)
{
    team_t *tmp = NULL;

    if (!teams || !name)
        return NULL;
    TAILQ_FOREACH(tmp, teams, teams)
        if (strcmp(tmp->name, name) == 0)
            return tmp;
    return NULL;
}

bool remove_user_from_team(team_t* team, uuid_t user_uuid)
{
    if (!team)
        return false;
    for (int i = 0; i< team->current_members; i++) {
        if (uuid_compare(team->members_uuid[i], user_uuid) == 0) {
            uuid_clear(team->members_uuid[i]);
            team->current_members--;
            team->max_members--;
            return true;
        }
    }
    return false;
}
