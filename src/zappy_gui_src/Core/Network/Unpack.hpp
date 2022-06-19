/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** Unpack
*/

#include <map>
#include <string>
#include <vector>

namespace gui::unpack {
/// \brief orientation of the player
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
std::map<std::string, player_orientation_e> mapOrientation{
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
    std::pair<int, int> getPosition() {
        return _position;
    }
    /// \brief get the inventory
    /// \return a vector containing the inventory
    std::vector<int> getInventory() {
        return _inventory;
    }
    /// \brief get the team name
    /// \return a string containing the name of the team
    std::string getTeamName() {
        return _team_name;
    }
    /// \brief get the level
    /// \return an int containing the level of the player
    int getLevel() {
        return _level;
    }
    /// \brief get the orientation
    /// \return the orientation of the player
    player_orientation_e getOrientation() {
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
    std::pair<int, int> getPosition() {
        return _position;
    }
    /// \brief get the inventory
    /// \return a vector containing the inventory
    std::vector<int> getInventory() {
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
    std::pair<int, int> getPosition() {
        return _position;
    }
    /// \brief get the team name
    /// \return a string containing the name of the team
    std::string getTeamName() {
        return _team_name;
    }
};


class Unpack {
   public:
    Unpack() = default;
    ~Unpack() = default;

    /// \brief split a string into a vector
    /// \param str the string to split
    /// \param separator the character spliting the string
    /// \param pushEmptyStrings bool if need to push empty strings
    /// \return a vector containing strings splitted by the separator
    std::vector<std::string>
    stov(const std::string &str, char separator, bool pushEmptyStrings = false);

    /// \brief Unpack an inventory
    /// \param inv the string of inventory to Unpack
    std::vector<int> UnpackInventory(std::string &inv);

    /// \brief Unpack an player
    //i/ \param unpacked the vector of strings to Unpack strings
    Player UnpackPlayer(std::vector<std::string> &unpacked);

    /// \brief Unpack an tile
    /// \param unpacked the vector of strings to Unpack strings
    Tile UnpackTile(std::vector<std::string> &unpacked);

    /// \brief Unpack an tile
    /// \param unpacked the vector of strings to Unpack strings
    Egg UnpackEgg(std::vector<std::string> &unpacked);

    /// \brief Unpack an entity
    /// \param unpacked the string to unpack
    void UnpackEntity(Player &p, std::string &packed);

    /// \brief Unpack an entity
    /// \param unpacked the string to unpack
    void UnpackEntity(Tile &t, std::string &packed);

    /// \brief Unpack an entity
    /// \param unpacked the string to unpack
    void UnpackEntity(Egg &e, std::string &packed);

   private:
};
}  // namespace gui