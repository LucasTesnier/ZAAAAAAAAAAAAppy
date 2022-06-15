/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** unpack
*/

#include <string>
#include <vector>
#include <map>

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
std::map<std::string, player_orientation_e> mapOrientation {
        {"0", NORTH},
        {"1", SOUTH},
        {"2", EAST},
        {"3", WEST},
};

/// \brief split a string into a vector
/// \param str the string to split
/// \param separator the character spliting the string
/// \param pushEmptyStrings bool if need to push empty strings
/// \return a vector containing strings splitted by the separator
std::vector <std::string> stov(const std::string &str, char separator, bool pushEmptyStrings = false);

/// \brief unpack an inventory
/// \param inv the string of inventory to unpack
void unpack_inventory(std::string &inv);

/// \brief unpack an player
/// \param unpacked the vector of strings to unpack strings
void unpack_player(std::vector<std::string> &unpacked);

/// \brief unpack an tile
/// \param unpacked the vector of strings to unpack strings
void unpack_tile(std::vector<std::string> &unpacked);