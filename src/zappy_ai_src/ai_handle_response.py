from dataclasses import dataclass
from sys import stderr

class Inventory:
    def __init__(self, inventoryResponse : str):
        """ Constructor of the Inventory Class """
        self.__food: int = 0
        self.__linemate: int = 0
        self.__deraumere: int = 0
        self.__sibur: int = 0
        self.__mendiane: int = 0
        self.__phiras: int = 0
        self.__thystame: int = 0
        if not self.fillInventory(inventoryResponse):
            print("The given string cannot be used to create an inventory", file=stderr)

    def __getitem__(self, item):
        return getattr(self, item)

    def fillInventory(self, inventoryStr : str) -> bool:
        """ PRIVATE METHOD """
        """ Parse the string given in parameter and fill the Inventory object """
        if str is "":
            return False
        inventorySplit = inventoryStr.split(", ")
        try:
            self.__food = int(inventorySplit[0].split(" ")[1])
            self.__linemate = int(inventorySplit[1].split(" ")[1])
            self.__deraumere = int(inventorySplit[2].split(" ")[1])
            self.__sibur = int(inventorySplit[3].split(" ")[1])
            self.__mendiane = int(inventorySplit[4].split(" ")[1])
            self.__phiras = int(inventorySplit[5].split(" ")[1])
            self.__thystame = int(inventorySplit[6].split(" ")[1])
        except ValueError:
            return False
        return True

    def GetFood(self) -> int:
        """ Getter for the food """
        return self.__food

    def GetLinemate(self) -> int:
        """ Getter for the Linemate """
        return self.__linemate

    def GetDeraumere(self) -> int:
        """ Getter for the Deraumere """
        return self.__deraumere

    def GetSibur(self) -> int:
        """ Getter for the Sibur """
        return self.__sibur

    def GetMendiane(self) -> int:
        """ Getter for the Mendiane """
        return self.__mendiane

    def GetPhiras(self) -> int:
        """ Getter for the Phiras """
        return self.__phiras

    def GetThystame(self) -> int:
        """ Getter for the thystame """
        return self.__thystame

    def DecreaseFood(self, nbFood: int):
        """ Decrease the food in the Object by nbFood """
        self.__food = self.__food - nbFood

    def DecreaseLinemate(self, nbLinemate : int) -> int:
        """ Decrease the linemate in the Object by nbLinemate """
        self.__linemate = self.__linemate - nbLinemate

    def DecreaseDeraumere(self, nbDeraumere : int) -> int:
        """ Decrease the Deraumere in the Object by nbDeraumere """
        self.__deraumere = self.__deraumere - nbDeraumere

    def DecreaseSibur(self, nbSibur : int) -> int:
        """ Decrease the Sibur in the Object by nbSibur """
        self.__sibur = self.__sibur - nbSibur

    def DecreaseMendiane(self, nbMendiane : int) -> int:
        """ Decrease the Mendiane in the Object by nbMendiane """
        self.__mendiane = self.__mendiane - nbMendiane

    def DecreasePhiras(self, nbPhiras : int) -> int:
        """ Decrease the Phiras in the Object by nbPhiras """
        self.__phiras = self.__phiras - nbPhiras

    def DecreaseThystame(self, nbThystame : int) -> int:
        """ Decrease the Thystame in the Object by nbThystame """
        self.__thystame = self.__thystame - nbThystame

@dataclass
class Tile:
    """ Dataclass for the Map Class """
    player: int
    food: int
    linemate: int
    deraumere: int
    sibur: int
    mendiane: int
    phiras: int
    thystame: int

    def __getitem__(self, item):
        return getattr(self, item)

class Map:
    def __init__(self, lookResponse: str):
        """ Constructor of the Tile Class """
        self.__map = []
        self.fillMap(lookResponse)

    def fillMap(self, lookStr : str) -> None:
        """ Parse the string given in parameter and fill the Map object """
        if str is "":
            return
        mapTab = []
        self.__map.clear()
        mapTab = lookStr.split(", ")
        for x in range(0, len(mapTab)):
            player = self.__countItem(mapTab[x], "player")
            food = self.__countItem(mapTab[x], "food")
            linemate = self.__countItem(mapTab[x], "linemate")
            deraumere = self.__countItem(mapTab[x], "deraumere")
            sibur = self.__countItem(mapTab[x], "sibur")
            mendiane = self.__countItem(mapTab[x], "mendiane")
            phiras = self.__countItem(mapTab[x], "phiras")
            thystame = self.__countItem(mapTab[x], "thystame")
            newTile = Tile(player, food, linemate, deraumere, sibur, mendiane, phiras, thystame)
            self.__map.append(newTile)

    def __countItem(self, tileStr : str, searchedItem : str) -> int:
        """ PRIVATE METHOD """
        """ Count the occurence of the Item in the Tile """
        return tileStr.count(searchedItem)

    def GetTile(self, x) -> Tile:
        """"
        Get one Tile of the Map
        by accessing at his index in a classic way
        """
        return self.__map[x]

    def GetMapSize(self) -> int:
        """" Get the size of the Map """
        return len(self.__map)
