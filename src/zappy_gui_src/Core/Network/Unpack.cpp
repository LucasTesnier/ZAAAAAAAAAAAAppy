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

Player Unpack::UnpackPlayer(std::vector<std::string> &unpacked)
{
    Player p;
    try {
        auto player = stov(unpacked[1], ';');
        p._position = std::make_pair(std::stoi(player[0]), std::stoi(player[1]));
        player.clear();
        player = stov(unpacked[2], '}');
        p._inventory = UnpackInventory(player[0]);
        auto p_end = stov(player[1], ';');
        p._team_name = p_end[0];
        p._level = std::stoi(p_end[1]);
        p._orientation = mapOrientation.find(p_end[2])->second;
    } catch(...) {
        return p;
        // throw (UnpackException("Unpack player" "Invalid packed string"));
    }
    return p;
}

Tile Unpack::UnpackTile(std::vector<std::string> &unpacked)
{
    Tile t;
    try {
        auto tile = stov(unpacked[1], ';');
        t._position = std::make_pair(std::stoi(tile[0]), std::stoi(tile[1]));
        tile.clear();
        tile = stov(unpacked[2], '}');
        t._inventory = UnpackInventory(tile[0]);
    } catch(...) {
        return t;
        // throw(UnpackException("Unpack tile" "Invalid packed string"));
    }
    return t;
}

Egg Unpack::UnpackEgg(std::vector<std::string> &unpacked)
{
    Egg e;
    try {
        auto egg = stov(unpacked[1], ';');
        e._position = std::make_pair(std::stoi(egg[0]), std::stoi(egg[1]));
        egg[2].pop_back();
        e._team_name = egg[2];
    } catch(...) {
        return e;
        // throw(UnpackException("Unpack egg" "Invalid packed string"));
    }
    return e;
}

void Unpack::UnpackEntity(Player &p, std::string &packed)
{
    auto unpacked = stov(packed, '{');
    if (unpacked[0] == "player") {
        p = UnpackPlayer(unpacked);
    } else
        return;
        // throw(UnpackException("Unpack" "Invalid packed type player"));
}

void Unpack::UnpackEntity(Tile &t, std::string &packed)
{
    auto unpacked = stov(packed, '{');
    if (unpacked[0] == "tile") {
        t = UnpackTile(unpacked);
    } else
        return;
        // throw(UnpackException("Unpack" "Invalid packed type tile"));
}

void Unpack::UnpackEntity(Egg &e, std::string &packed)
{
    auto unpacked = stov(packed, '{');
    if (unpacked[0] == "egg") {
        e = UnpackEgg(unpacked);
    } else
        return;
        // throw(UnpackException("Unpack" "Invalid packed type egg"));
}

int main(void)
{
    std::string a("player{42;4242;inventory{10;9;8;7;6;5;4};guiguilebg;1;0}");
    std::string b("tile{423;432;inventory{10;0;0;0;0;0;0}}");
    std::string c("egg{42;4242;guiguilebgoeuf}");
    Unpack u;
    Player p;
    u.UnpackEntity(p, a);
    auto v = p.getInventory();
    for (auto &i : v)
        std::cout << i << ' ';
    return 0;
}