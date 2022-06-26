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
    auto bad_egg = std::string("hug{42;24;inventory{1;2;3;4;5;6;7}}");

    cr_assert_throw(unpack.UnpackEntity(egg, bad_egg), std::invalid_argument);
}
