/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** team
*/

/// \file src/zappy_server_src/core/include/team.h

#ifndef TEAM_H
    #define TEAM_H

    #include <string.h>
    #include <uuid/uuid.h>
    #include <sys/queue.h>
    #include <stdbool.h>

/// \brief Represents a team in the server
typedef struct team_s {
    /// Team name
    char *name;
    /// Max number of players in the team
    int max_members;
    /// The current amount of member in the team
    int current_members;
    /// The unique id of each team member
    uuid_t *members_uuid;
    /// teams list
    TAILQ_ENTRY(team_s) teams;
} team_t;

TAILQ_HEAD(teams_list_s, team_s);

/// \brief Create a new team
/// \param name The name of the team
/// \param max_members The maximum number of members in the team
/// \return The new team or NULL if an error occured
team_t *create_team(char *name, int max_members);

/// \brief Add a new team to the list
/// \param team The team to add
/// \param teams The list of teams
/// \return true if the team was added, false otherwise
bool add_team(team_t *team, struct teams_list_s *teams);

/// \brief Add user to the team
/// \param team The team to add the user to
/// \param uuid The user's uuid
/// \return true if the user was added, false otherwise
bool add_user_to_team(team_t* team, uuid_t user_uuid);

/// \brief Get a team by it's name
/// \param teams The list of teams
/// \param name The name of the team to get
/// \return The team or NULL if an error occured
team_t *get_team_by_name(char *name, struct teams_list_s *teams);

/// \brief Remove a user from the team
/// \param team The team to remove the user from
/// \param uuid The user's uuid
/// \return true if the user was removed, false otherwise
bool remove_user_from_team(team_t* team, uuid_t user_uuid);

/// \brief Remove a team from the list
/// \param team The team to remove
/// \param teams The list of teams
/// \return true if the team was removed, false otherwise
bool remove_team(team_t *team, struct teams_list_s *teams);

/// \brief Destroy a team
/// \param team The team to destroy
void delete_teams(struct teams_list_s *teams);

#endif /* TEAM_H */
