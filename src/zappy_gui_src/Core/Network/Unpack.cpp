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

/// \file src/zappy_gui_src/Core/Network/Unpack.cpp

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
        p._uuid = player[2];
        player.clear();
        player = stov(unpacked[2], '}');
        p._inventory = UnpackInventory(player[0]);
        auto p_end = stov(player[1], ';');
        p._team_name = p_end[0];
        p._level = std::stoi(p_end[1]);
        p._orientation = gui::entity::mapOrientation.find(p_end[2])->second;
    } catch(...) {
        throw (std::invalid_argument("Player invalid parsing"));
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
        throw (std::invalid_argument("Tile invalid parsing"));
    }
    return t;
}

gui::entity::Egg Unpack::UnpackEgg(std::vector<std::string> &unpacked)
{
    gui::entity::Egg e;
    try {
        auto egg = stov(unpacked[1], ';');
        e._position = std::make_pair(std::stoi(egg[0]), std::stoi(egg[1]));
        std::size_t pos = egg[2].find("}");
        std::string team_name = egg[2].substr(0, pos);
        e._team_name = team_name;
    } catch(...) {
        throw (std::invalid_argument("Egg invalid parsing"));
    }
    return e;
}

Start Unpack::UnpackStart(std::vector<std::string> &unpacked)
{
    Start start;

    try {
        auto data = stov(unpacked[1], ';');
        start.size_x = std::stoi(data[0]);
        start.size_y = std::stoi(data[1]);
        start.team_number = std::stoi(data[2]);
        data.clear();
        data = stov(unpacked[2], '}');
        auto temp = stov(data[1], ';');
        start.max_player = std::stoi(temp[0]);
    } catch(...) {
        throw (std::invalid_argument("Start invalid parsing"));
    }
    return start;
}

gui::entity::Status Unpack::UnpackStatus(std::vector<std::string> &unpacked)
{
    gui::entity::Status status;

    try
    {
        auto data = stov(unpacked[1], ':');
        status._status = data[0];
        std::size_t pos = data[1].find("}");
        std::string team_name = data[1].substr(0, pos);
        status._team_name = team_name;
    } catch(...) {
        throw (std::invalid_argument("Status invalid parsing"));
    }
    return status;

}

void Unpack::UnpackEntity(gui::entity::Player &p, std::string &packed)
{
    auto unpacked = stov(packed, '{');
    if (unpacked[0] == "player") {
        p = UnpackPlayer(unpacked);
    } else
        throw (std::invalid_argument("Player entity invalid parsing"));
}

void Unpack::UnpackEntity(gui::entity::Tile &t, std::string &packed)
{
    auto unpacked = stov(packed, '{');
    if (unpacked[0] == "tile") {
        t = UnpackTile(unpacked);
    } else
        throw (std::invalid_argument("Tile entity invalid parsing"));
}

void Unpack::UnpackEntity(gui::entity::Egg &e, std::string &packed)
{
    auto unpacked = stov(packed, '{');
    if (unpacked[0] == "egg") {
        e = UnpackEgg(unpacked);
    } else
        throw (std::invalid_argument("Egg entity invalid parsing"));
}

void Unpack::UnpackEntity(Start &e, std::string &packed)
{
    auto unpacked = stov(packed, '{');
    if (unpacked[0] == "start") {
        e = UnpackStart(unpacked);
    } else
        throw (std::invalid_argument("Start entity invalid parsing"));
}

void Unpack::UnpackEntity(gui::entity::Status &s, std::string &packed)
{
    auto unpacked = stov(packed, '{');
    if (unpacked[0] == "status") {
        s = UnpackStatus(unpacked);
    } else
        throw (std::invalid_argument("Start entity invalid parsing"));
}
