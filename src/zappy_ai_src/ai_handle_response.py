from sys import stderr

class Inventory:
    def __init__(self, inventoryResponse : str):
        """ Constructor of the Inventory Class """
        self.__food : int = 0
        self.__linemate : int = 0
        self.__deraumere : int = 0
        self.__sibur : int = 0
        self.__mendiane : int = 0
        self.__phiras : int = 0
        self.__thystame : int = 0
        if not self.__fillInventory(inventoryResponse):
            print("The given string cannot be used to create an inventory", file=stderr)

    def __fillInventory(self, inventoryStr : str) -> bool:
        """ PRIVATE METHOD """
        """ Parse the string given in parameter and fill the Inventory object """
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


class Tile:
    def __init__(self, player : int = 0, linemate : int = 0, deraumere : int = 0, sibur : int = 0, mendiane : int = 0, phiras : int = 0, thystame : int = 0):
        """ Constructor of the Tile Class """
        self.player : int = player
        self.linemate : int = linemate
        self.deraumere : int = deraumere
        self.sibur : int = sibur
        self.mendiane : int = mendiane
        self.phiras : int = phiras
        self.thystame : int = thystame


class Map:
    def __init__(self, lookResponse : str):
        """ Constructor of the Tile Class """
        self.__map = [] ## Map of Tile ##
        self.__fillMap(lookResponse)

    def __fillMap(self, lookStr : str) -> None:
        """ PRIVATE METHOD """
        """ Parse the string given in parameter and fill the Map object """
        mapTab = []
        mapTab = lookStr.split(", ")
        for x in range(0, len(mapTab)):
            player = self.__countItem(mapTab[x], "player")
            linemate = self.__countItem(mapTab[x], "linemate")
            deraumere = self.__countItem(mapTab[x], "deraumere")
            sibur = self.__countItem(mapTab[x], "sibur")
            mendiane = self.__countItem(mapTab[x], "mendiane")
            phiras = self.__countItem(mapTab[x], "player")
            thystame = self.__countItem(mapTab[x], "thystame")
            newTile = Tile(player, linemate, deraumere, sibur, mendiane, phiras, thystame)
            self.__map.append(newTile)

    def __countItem(self, tileStr : str, searchedItem : str) -> int:
        """ PRIVATE METHOD """
        """ Count the occurence of the Item in the Tile """
        return tileStr.count(searchedItem)

    def GetTile(self, x : int, y : int = 0) -> Tile:
        """" Get one Tile of the Map """
        return self.__map[((y - 1) * 2) + 1 + x]