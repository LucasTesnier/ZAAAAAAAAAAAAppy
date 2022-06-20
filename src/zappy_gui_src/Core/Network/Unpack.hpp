/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** Unpack
*/

#include <map>
#include <string>
#include <vector>
#include "Entity.hpp"

namespace gui::unpack {
/// \brief orientation of the player

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
    gui::entity::Player UnpackPlayer(std::vector<std::string> &unpacked);

    /// \brief Unpack an tile
    /// \param unpacked the vector of strings to Unpack strings
    gui::entity::Tile UnpackTile(std::vector<std::string> &unpacked);

    /// \brief Unpack an tile
    /// \param unpacked the vector of strings to Unpack strings
    gui::entity::Egg UnpackEgg(std::vector<std::string> &unpacked);

    /// \brief Unpack an entity
    /// \param unpacked the string to unpack
    void UnpackEntity(gui::entity::Player &p, std::string &packed);

    /// \brief Unpack an entity
    /// \param unpacked the string to unpack
    void UnpackEntity(gui::entity::Tile &t, std::string &packed);

    /// \brief Unpack an entity
    /// \param unpacked the string to unpack
    void UnpackEntity(gui::entity::Egg &e, std::string &packed);

   private:
};
}  // namespace gui