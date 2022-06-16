/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** unpack
*/

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include "unpack.hpp"
// #include "ZappyGuiException.hpp"

std::vector <std::string> stov(const std::string &str, char separator, bool pushEmptyStrings)
{
        std::vector<std::string> vector;
        std::string temp;
        size_t len = str.size();

        for (size_t i = 0; i < len; i++) {
            if (str[i] == separator) {
                if (pushEmptyStrings || !temp.empty()) {
                    vector.push_back(temp);
                    temp.clear();
                }
            }
            else
                temp.push_back(str[i]);
        }
        if (pushEmptyStrings || !temp.empty())
            vector.push_back(temp);
        return vector;
}

void unpack_inventory(std::string &inv)
{
    auto inventory = stov(inv, ';');
    // for (auto &i : inventory) {
    //     std::cout << i << ' ';
    // }
    std::vector<int> int_ventory;
    std::transform(inventory.begin(), inventory.end(), std::back_inserter(int_ventory),
        [&](std::string s) {
            return stoi(s);
        });
    for (auto &i : int_ventory) {
        std::cout << i << ' ';
    }
}

void unpack_player(std::vector<std::string> &unpacked)
{
    // try {
        // for (auto &p : unpacked)
        //     std::cout << p << std::endl;

        auto player = stov(unpacked[1], ';');
        std::cout << "x: " << player[0] << std::endl;
        std::cout << "y: " << player[1] << std::endl;
        player.clear();
        player = stov(unpacked[2], '}');
        unpack_inventory(player[0]);
        auto p_end = stov(player[1], ';');
        std::cout << "team: " << p_end[0]
        << " level: " << std::stoi(p_end[1])
        << "  orientation: " <<  mapOrientation.find(p_end[2])->second << std::endl;
    // } throw(UnpackException("Unpack player" "Invalid packed string"));
}

void unpack_tile(std::vector<std::string> &unpacked)
{
    // try {
        auto tile = stov(unpacked[1], ';');
        std::cout << "x: " << tile[0] << std::endl;
        std::cout << "y: " << tile[1] << std::endl;
        // std::cout << unpacked[2] << tile[0] << tile[1] << std::endl;
        tile.clear();
        tile = stov(unpacked[2], '}');
        unpack_inventory(tile[0]);
    // } throw(UnpackException("Unpack tile" "Invalid packed string"));
}

void unpack_egg(std::vector<std::string> &unpacked)
{
    // try {
        auto tile = stov(unpacked[1], ';');
        std::cout << "x: " << tile[0] << std::endl;
        std::cout << "y: " << tile[1] << std::endl;
        tile[2].pop_back();
        std::cout << "team name: " << tile[2] << std::endl;
        // std::cout << unpacked[2] << tile[0] << tile[1] << std::endl;

    // } throw(UnpackException("Unpack tile" "Invalid packed string"));
}

void unpack(std::string &packed)
{
    auto unpacked = stov(packed, '{');
    if (unpacked[0] == "player") {
        std::cout << "test " << unpacked[0] << std::endl;
        unpack_player(unpacked);
    } else if (unpacked[0] == "tile") {
        std::cout << "test " << unpacked[0] << std::endl;
        unpack_tile(unpacked);
    } else if (unpacked[0] == "egg") {
        unpack_egg(unpacked);
    } else
        return;
        // throw(UnpackException("Unpack" "Invalid packed type"));
}

int main(void)
{
    std::string a("player{42;4242;inventory{10;0;0;0;0;0;0};guiguilebg;1;0}");
    std::string b("tile{423;432;inventory{10;0;0;0;0;0;0}}");
    std::string c("egg{42;4242;guiguilebgoeuf}");
    unpack(c);
    return 0;
}