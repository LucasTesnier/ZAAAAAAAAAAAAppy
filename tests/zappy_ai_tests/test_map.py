#!/usr/bin/python3
from ai_handle_response import Map, Tile

def map_test(test_str : str) -> Map:
    """ Transform a str in Map object """
    map_object : Map = Map(test_str)
    return map_object

def test_classic_map():
    Test1 : Map = map_test("player , , , thystame , , food , , , , , thystame , , , , , ,")
    test_tile_1 : Tile = Test1.GetTile(0)
    test_tile_2 : Tile = Test1.GetTile(3)
    test_tile_3 : Tile = Test1.GetTile(5)
    test_tile_4 : Tile = Test1.GetTile(10)
    assert(test_tile_1.player == 1 and test_tile_2.thystame == 1 and test_tile_3.food == 1 and test_tile_4.thystame == 1)

def test_two_object_on_same_tile():
    Test2 : Map = map_test("player , player deraumere , ,")
    test_tile : Tile = Test2.GetTile(1)
    assert(test_tile.player == 1 and test_tile.deraumere == 1)

def test_multiple_objects_on_multiple_tiles():
    Test3 : Map = map_test("player player player deraumere deraumere food food food food food food ,")
    multiple_test_tile : Tile = Test3.GetTile(0)
    assert(multiple_test_tile.player == 3 and multiple_test_tile.deraumere == 2 and multiple_test_tile.food == 6)