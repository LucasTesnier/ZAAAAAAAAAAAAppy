#!/usr/bin/python3
from ai_handle_response import Inventory

def InventoryTest(testStr : str) -> Inventory:
    """ Transfom a str in Inventory Object """
    InventoryObject : Inventory = Inventory(testStr)
    return InventoryObject

def test_basic_inventory():
    Test1 : Inventory = InventoryTest("food 3000, linemate 10, deraumere 12, sibur 100, mendiane 15, phiras 5, thystame 67")
    assert(Test1.GetFood() == 3000 and Test1.GetLinemate() == 10 and Test1.GetDeraumere() == 12 \
        and Test1.GetSibur() == 100 and Test1.GetMendiane() == 15 and Test1.GetPhiras() == 5 and Test1.GetThystame() == 67)

def test_decrease_inventory():
	Test2 : Inventory = InventoryTest("food 1, linemate 1, deraumere 1, sibur 1, mendiane 1, phiras 1, thystame 1")
	assert(Test2.GetFood() == 1 and Test2.GetLinemate() == 1 and Test2.GetDeraumere() == 1 \
					and Test2.GetSibur() == 1 and Test2.GetMendiane() == 1 and Test2.GetPhiras() == 1 and Test2.GetThystame() == 1)
	Test2.DecreaseFood(1)
	Test2.DecreaseLinemate(1)
	Test2.DecreaseDeraumere(1)
	Test2.DecreaseSibur(1)
	Test2.DecreaseMendiane(1)
	Test2.DecreasePhiras(1)
	Test2.DecreaseThystame(1)
	assert(Test2.GetFood() == 0 and Test2.GetLinemate() == 0 and Test2.GetDeraumere() == 0 \
					and Test2.GetSibur() == 0 and Test2.GetMendiane() == 0 and Test2.GetPhiras() == 0 and Test2.GetThystame() == 0)
