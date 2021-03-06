/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** teams_remove
*/

/// \file src/zappy_server_src/core/teams_remove.c

#include "team.h"
#include <stdlib.h>

bool remove_team(team_t *team, struct teams_list_s *teams)
{
    team_t *tmp = NULL;

    if (!team || !teams)
        return false;
    TAILQ_FOREACH(tmp, teams, teams)
        if (strcmp(tmp->name, team->name) == 0)
            break;
    if (!tmp)
        return false;
    TAILQ_REMOVE(teams, team, teams);
    free(team->name);
    free(team->members_uuid);
    free(team);
    return true;
}

void delete_teams(struct teams_list_s *teams)
{
    team_t *team = NULL;
    team_t *tmp = NULL;

    if (!teams)
        return;
    team = TAILQ_FIRST(teams);
    while (team != NULL) {
        tmp = TAILQ_NEXT(team, teams);
        free(team->name);
        free(team->members_uuid);
        free(team);
        team = tmp;
    }
    TAILQ_INIT(teams);
}
