/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** Unpack
*/

#include <map>
#include <string>
#include <vector>

namespace gui {
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

class Unpack {
   public:
    /// \brief split a string into a vector
    /// \param str the string to split
    /// \param separator the character spliting the string
    /// \param pushEmptyStrings bool if need to push empty strings
    /// \return a vector containing strings splitted by the separator
    std::vector<std::string>
    stov(const std::string &str, char separator, bool pushEmptyStrings = false);

    /// \brief Unpack an inventory
    /// \param inv the string of inventory to Unpack
    void UnpackInventory(std::string &inv);

    /// \brief Unpack an player
    /// \param unpacked the vector of strings to Unpack strings
    void UnpackPlayer(std::vector<std::string> &unpacked);

    /// \brief Unpack an tile
    /// \param unpacked the vector of strings to Unpack strings
    void UnpackTile(std::vector<std::string> &unpacked);

    /// \brief Unpack an tile
    /// \param unpacked the vector of strings to Unpack strings
    void UnpackEgg(std::vector<std::string> &unpacked);
};
}  // namespace gui