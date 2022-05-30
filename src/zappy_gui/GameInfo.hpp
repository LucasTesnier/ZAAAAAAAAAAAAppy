/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** GameInfo
*/

#ifndef GAMEINFO_HPP_
#define GAMEINFO_HPP_

#include <string>

namespace gui {
    class GameInfo {
        public:
            GameInfo(int port, std::string machine);
            ~GameInfo();

        protected:
        private:
            size_t _width;
            size_t _height;
            int _port;
            std::string _machine;
            size_t _nb_team;
            size_t _nb_max_player;
            float _time_unit;
    };
}

#endif /* !GAMEINFO_HPP_ */
