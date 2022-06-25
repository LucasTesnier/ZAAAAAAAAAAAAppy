/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** Entity
*/

/// \file src/zappy_gui_src/Core/Entity/Entity.hpp

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <map>
#include <string>
#include <vector>

namespace gui::entity {
    enum player_orientation_e {
        /// North orientation
        NORTH,
        /// South orientation
        SOUTH,
        /// East orientation
        EAST,
        /// West orientation
        WEST
    };

    /// \brief map linking a string to an orientaion
    static std::map<std::string, player_orientation_e> mapOrientation{
        {"0", NORTH},
        {"1", SOUTH},
        {"2", EAST},
        {"3", WEST},
    };

    class Player {
    public:
        /// \brief defaut Constructor
        Player() = default;
        /// \brief defaut Destructor
        ~Player() = default;
        /// \brief vector of pair containing the position x and y
        std::pair<int, int> _position;
        /// \brief vector of int representating the inventory
        std::vector<int> _inventory;
        /// \brief string representating the team
        std::string _team_name;
        /// \brief level of the player
        int _level;
        /// \brief orientation of the player
        player_orientation_e _orientation;
        /// \brief get the position
        /// \return a pair containing the position x and y
        inline const std::pair<int, int> &getPosition() const {
            return _position;
        }
        /// \brief get the inventory
        /// \return a vector containing the inventory
        inline const std::vector<int> &getInventory() const {
            return _inventory;
        }
        /// \brief get the team name
        /// \return a string containing the name of the team
        inline const std::string &getTeamName() const {
            return _team_name;
        }
        /// \brief get the level
        /// \return an int containing the level of the player
        inline const int &getLevel() const {
            return _level;
        }
        /// \brief get the orientation
        /// \return the orientation of the player
        inline const player_orientation_e &getOrientation() const {
            return _orientation;
        }
    };

    class Tile {
    public:
        /// \brief defaut Constructor
        Tile() = default;
        /// \brief defaut Destructor
        ~Tile() = default;
        /// \brief vector of pair containing the position x and y
        std::pair<int, int> _position;
        /// \brief vector of int representating the inventory
        std::vector<int> _inventory;
        /// \brief get the position
        /// \return a pair containing the position x and y
        inline const std::pair<int, int> &getPosition() const {
            return _position;
        }
        /// \brief get the inventory
        /// \return a vector containing the inventory
        inline const std::vector<int> &getInventory() const {
            return _inventory;
        }
    };

    class Egg {
    public:
        /// \brief defaut Constructor
        Egg() = default;
        /// \brief defaut Destructor
        ~Egg() = default;
        /// \brief vector of pair containing the position x and y
        std::pair<int, int> _position;
        /// \brief string representating the team
        std::string _team_name;
        /// \brief get the position
        /// \return a pair containing the position x and y
        inline const std::pair<int, int> &getPosition() const {
            return _position;
        }
        /// \brief get the team name
        /// \return a string containing the name of the team
        inline const std::string &getTeamName() const {
            return _team_name;
        }
    };

    struct Status {
        public:
        /// \brief The status of the game win or loose
        std::string _status;
        /// \brief the name of the team who won or lost
        std::string _team_name;
        /// \brief get the status
        /// \return a string containing the status win or lost
        inline const std::string &getStatus() const {
            return _status;
        }
        /// \brief get the team name
        /// \return a string containing the name of the team
        inline const std::string &getTeamName() const {
            return _team_name;
        }
    };
}  // namespace gui::entity

#endif /* !ENTITY_HPP_ */
