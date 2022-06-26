/*
** EPITECH PROJECT, 2022
** ZAPPYMIRROR
** File description:
** TestsUnpack
*/

#include <criterion/criterion.h>
#include <Unpack.hpp>
#include <iostream>

Test(Unpack, test_unpack_basic_player)
{
    gui::entity::Player player;
    gui::unpack::Unpack unpack;
    auto basic_player = std::string("player{42;24;uuid;0;inventory{1;2;3;4;5;6;7};team_guigui;2;0");

    unpack.UnpackEntity(player, basic_player);
    cr_assert_eq(42, player.getPosition().first);
    cr_assert_eq(24, player.getPosition().second);
    cr_assert_str_eq("uuid", player.getUuid().c_str());
    cr_assert_eq(false, player.getStatusPlayer());
    cr_assert_eq(1, player.getInventory().at(0));
    cr_assert_eq(2, player.getInventory().at(1));
    cr_assert_eq(3, player.getInventory().at(2));
    cr_assert_eq(4, player.getInventory().at(3));
    cr_assert_eq(5, player.getInventory().at(4));
    cr_assert_eq(6, player.getInventory().at(5));
    cr_assert_eq(7, player.getInventory().at(6));
    cr_assert_str_eq("team_guigui", player.getTeamName().c_str());
    cr_assert_eq(2, player.getLevel());
    cr_assert_eq(gui::entity::NORTH, player.getOrientation());
}

Test(Unpack, test_unpack_invalid_player)
{
    gui::entity::Player player;
    gui::unpack::Unpack unpack;
    auto bad_player = std::string("payeur{42;24;uuid;0;inventory{1;2;3;4;5;6;7};team_guigui;2;0}");

    cr_assert_throw(unpack.UnpackEntity(player, bad_player), std::invalid_argument);
}

Test(Unpack, test_unpack_basic_tile)
{
    gui::entity::Tile tile;
    gui::unpack::Unpack unpack;
    auto basic_tile = std::string("tile{42;24;inventory{1;2;3;4;5;6;7}}");

    unpack.UnpackEntity(tile, basic_tile);
    cr_assert_eq(42, tile.getPosition().first);
    cr_assert_eq(24, tile.getPosition().second);
    cr_assert_eq(1, tile.getInventory().at(0));
    cr_assert_eq(2, tile.getInventory().at(1));
    cr_assert_eq(3, tile.getInventory().at(2));
    cr_assert_eq(4, tile.getInventory().at(3));
    cr_assert_eq(5, tile.getInventory().at(4));
    cr_assert_eq(6, tile.getInventory().at(5));
    cr_assert_eq(7, tile.getInventory().at(6));
}

Test(Unpack, test_unpack_invalid_tile)
{
    gui::entity::Tile tile;
    gui::unpack::Unpack unpack;
    auto bad_tile = std::string("tail{42;24;inventory{1;2;3;4;5;6;7}}");

    cr_assert_throw(unpack.UnpackEntity(tile, bad_tile), std::invalid_argument);
}

Test(Unpack, test_unpack_basic_egg)
{
    gui::entity::Egg egg;
    gui::unpack::Unpack unpack;
    auto basic_egg = std::string("egg{42;24;uuid;0;team_guigui_oeuf}");

    unpack.UnpackEntity(egg, basic_egg);
    cr_assert_eq(42, egg.getPosition().first);
    cr_assert_eq(24, egg.getPosition().second);
    cr_assert_str_eq("uuid", egg.getUuid().c_str());
    cr_assert_eq(false, egg._statusEgg);
    cr_assert_str_eq("team_guigui_oeuf", egg.getTeamName().c_str());
}

Test(Unpack, test_unpack_invalid_egg)
{
    gui::entity::Egg egg;
    gui::unpack::Unpack unpack;
    auto bad_egg = std::string("hug{42;24;uuid;0;team_guigui_oeuf}");

    cr_assert_throw(unpack.UnpackEntity(egg, bad_egg), std::invalid_argument);
}

Test(Unpack, test_unpack_basic_start)
{
    gui::unpack::Start start;
    gui::unpack::Unpack unpack;
    auto basic_start = std::string("start{42;24;2;{team_guigui;team_thomas};6}");

    unpack.UnpackEntity(start, basic_start);
    cr_assert_eq(42, start.size_x);
    cr_assert_eq(24, start.size_y);
    cr_assert_eq(2, start.team_number);
    cr_assert_eq(6, start.max_player);
}

Test(Unpack, test_unpack_invalid_start)
{
    gui::unpack::Start start;
    gui::unpack::Unpack unpack;
    auto bad_start = std::string("tarte{42;24;2;{team_guigui;team_thomas};6}");

    cr_assert_throw(unpack.UnpackEntity(start, bad_start), std::invalid_argument);
}

Test(Unpack, test_unpack_basic_status)
{
    gui::entity::Status status;
    gui::unpack::Unpack unpack;
    auto basic_status_win = std::string("status{win:team_guigui}");
    auto basic_status_lose = std::string("status{lose:team_thomas}");

    unpack.UnpackEntity(status, basic_status_win);
    cr_assert_str_eq("win", status.getStatus().c_str());
    cr_assert_str_eq("team_guigui", status.getTeamName().c_str());

    unpack.UnpackEntity(status, basic_status_lose);
    cr_assert_str_eq("lose", status.getStatus().c_str());
    cr_assert_str_eq("team_thomas", status.getTeamName().c_str());
}

Test(Unpack, test_unpack_invalid_status)
{
    gui::entity::Status status;
    gui::unpack::Unpack unpack;
    auto bad_status = std::string("stanus{win:team_guigui}");

    cr_assert_throw(unpack.UnpackEntity(status, bad_status), std::invalid_argument);
}
