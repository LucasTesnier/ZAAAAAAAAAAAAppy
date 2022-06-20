/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** Unpack
*/

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include "Unpack.hpp"
#include "ZappyGuiException.hpp"

using namespace gui::unpack;

std::vector <std::string> Unpack::stov(const std::string &str, char separator, bool pushEmptyStrings)
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

std::vector<int> Unpack::UnpackInventory(std::string &inv)
{
    auto inventory = stov(inv, ';');
    std::vector<int> int_ventory;
    std::transform(inventory.begin(), inventory.end(), std::back_inserter(int_ventory),
        [&](std::string s) {
            return stoi(s);
        });
    return int_ventory;
}

gui::entity::Player Unpack::UnpackPlayer(std::vector<std::string> &unpacked)
{
    gui::entity::Player p;
    try {
        auto player = stov(unpacked[1], ';');
        p._position = std::make_pair(std::stoi(player[0]), std::stoi(player[1]));
        player.clear();
        player = stov(unpacked[2], '}');
        p._inventory = UnpackInventory(player[0]);
        auto p_end = stov(player[1], ';');
        p._team_name = p_end[0];
        p._level = std::stoi(p_end[1]);
        p._orientation = gui::entity::mapOrientation.find(p_end[2])->second;
    } catch(...) {
        throw (UnpackException("Unpack player" "Invalid packed string"));
    }
    return p;
}

gui::entity::Tile Unpack::UnpackTile(std::vector<std::string> &unpacked)
{
    gui::entity::Tile t;
    try {
        auto tile = stov(unpacked[1], ';');
        t._position = std::make_pair(std::stoi(tile[0]), std::stoi(tile[1]));
        tile.clear();
        tile = stov(unpacked[2], '}');
        t._inventory = UnpackInventory(tile[0]);
    } catch(...) {
        throw(UnpackException("Unpack tile" "Invalid packed string"));
    }
    return t;
}

gui::entity::Egg Unpack::UnpackEgg(std::vector<std::string> &unpacked)
{
    gui::entity::Egg e;
    try {
        auto egg = stov(unpacked[1], ';');
        e._position = std::make_pair(std::stoi(egg[0]), std::stoi(egg[1]));
        egg[2].pop_back();
        e._team_name = egg[2];
    } catch(...) {
        throw(UnpackException("Unpack egg" "Invalid packed string"));
    }
    return e;
}

void Unpack::UnpackEntity(gui::entity::Player &p, std::string &packed)
{
    auto unpacked = stov(packed, '{');
    if (unpacked[0] == "player") {
        p = UnpackPlayer(unpacked);
    } else
        throw(UnpackException("Unpack" "Invalid packed type player"));
}

void Unpack::UnpackEntity(gui::entity::Tile &t, std::string &packed)
{
    auto unpacked = stov(packed, '{');
    if (unpacked[0] == "tile") {
        t = UnpackTile(unpacked);
    } else
        throw(UnpackException("Unpack" "Invalid packed type tile"));
}

void Unpack::UnpackEntity(gui::entity::Egg &e, std::string &packed)
{
    auto unpacked = stov(packed, '{');
    if (unpacked[0] == "egg") {
        e = UnpackEgg(unpacked);
    } else
        throw(UnpackException("Unpack" "Invalid packed type egg"));
}
