/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** GameInfo
*/

/// \file src/zappy_gui/GameInfo.hpp
/// \brief Game Info class

#ifndef GAMEINFO_HPP_
#define GAMEINFO_HPP_

#include <string>

namespace gui {
class GameInfo {
   public:
    /// \brief Construct a new Game Info object
    ///
    /// \param port port of the server
    /// \param machine machine of the server
    GameInfo(int port, std::string machine);
    /// \brief Destructor of a Game Info object
    ~GameInfo();

   protected:
   private:
    /// \brief width of the map
    size_t _width;
    /// \brief height of the map
    size_t _height;
    /// \brief port of the server
    int _port;
    /// \brief machine of the server
    std::string _machine;
    /// \brief number of team
    size_t _nb_team;
    /// \brief number player maximum by team
    size_t _nb_max_player;
    /// \brief unit of time
    float _time_unit;
};
}  // namespace gui

#endif /* !GAMEINFO_HPP_ */
