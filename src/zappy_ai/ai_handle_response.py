from sys import stderr

class Inventory:
    def __init__(self, inventoryResponse : str):
        self.__food : int = 0
        self.__linemate : int = 0
        self.__deraumere : int = 0
        self.__sibur : int = 0
        self.__mediane : int = 0
        self.__phiras : int = 0
        self.__thysmane : int = 0
        if not self.__fillInventory(inventoryResponse):
            print("The given string cannot be used to create an inventory", file=stderr)

    def __fillInventory(inventoryStr : str) -> bool:
        return True
