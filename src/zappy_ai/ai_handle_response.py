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
        self.__thysmane : int = 0
        if not self.__fillInventory(inventoryResponse):
            print("The given string cannot be used to create an inventory", file=stderr)

    def __fillInventory(self, inventoryStr : str) -> bool:
        """ PRIVATE METHOD """
        """ Parse the string given in parameter and fill the Inventory object """
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

    def GetThysmane(self) -> int:
        """ Getter for the Thysmane """
        return self.__thysmane