#!/usr/bin/python3

from ai_function_wrapper import ServerWrapper
from ai_handle_response import Inventory

"""---------------------------------------------Static variables-----------------------------------------------------"""

LEVEL_MAX = 8
"""Player is starting the game with 120 food which represents 1200 unit of time
    like you probably know 1 food == 10 units of time
"""
FOOD_START = 120


"""This static array is used to know every requirements for elevations"""
""" - Player represents de amount of player needed for elevation
    - From Linemate to thystame are the name of component and the amount needed for elevation per level
"""
levelUpRequirements = [{},
                       {
                           "player": 1,  # LEVEL 2
                           "linemate": 1,
                           "deraumere": 0,
                           "sibur": 0,
                           "mendiane": 0,
                           "phiras": 0,
                           "thystame": 0
                       },
                       {
                           "player": 2,  ##LEVEL 3
                           "linemate": 1,
                           "deraumere": 1,
                           "sibur": 1,
                           "mendiane": 0,
                           "phiras": 0,
                           "thystame": 0
                       },
                       {
                           "player": 2, #LEVEL 4
                           "linemate": 2,
                           "deraumere": 0,
                           "sibur": 1,
                           "mendiane": 0,
                           "phiras": 2,
                           "thystame": 0
                       },
                       {
                           "player": 4, #LEVEL 5
                           "linemate": 1,
                           "deraumere": 1,
                           "sibur": 2,
                           "mendiane": 0,
                           "phiras": 1,
                           "thystame": 0
                       },
                       {
                           "player": 4, #LEVEL 6
                           "linemate": 1,
                           "deraumere": 2,
                           "sibur": 1,
                           "mendiane": 3,
                           "phiras": 0,
                           "thystame": 0
                       },
                       {
                           "player": 6, #LEVEL 7
                           "linemate": 1,
                           "deraumere": 2,
                           "sibur": 3,
                           "mendiane": 0,
                           "phiras": 1,
                           "thystame": 0
                       },
                       {
                           "player": 6, #LEVEL 8
                           "linemate": 2,
                           "deraumere": 2,
                           "sibur": 2,
                           "mendiane": 2,
                           "phiras": 2,
                           "thystame": 1
                       }
                       ]

"""-------------------------------------------Strategy Class---------------------------------------------------------"""
class Strategy:
    def __init__(self, availableSlots: int, teamName: str):
        """ Default Constructor of the Core class"""

        """This is used to know how many player can still join the game/team
            When availableSlots == 0 it means that the team is full and cannot accept more connection.
        """
        self.__availableSlots = availableSlots

        """Every team got a name which is used to separate different player in different group"""
        self.__teamName = teamName

        """This is the wrapper of the library used to communicate with the server"""
        self.__lib = ServerWrapper("./libzappy_ai_api.so")

        """This boolean is used to know the current state of the AI
            True if the AI is looping and making some actions
            False if the player died or client disconnected
        """
        self.__isRunning = False

        """This is a temporary inventory used in strategies to plan actions of player in different way
            As an example if a player runs out of food, the survival action will take priority
        """
        self.__inventory = Inventory("food 120, linemate 0, deraumere 0, sibur 0, mendiane 0, phiras 0, thystame 0")

    def __del__(self):
        """Default Destructor of the Core class"""
        self.running = False

    """--------------------------------Getter and Setter for Core Strategy class------------------------------------ """

    def __setAvailableSlots(self, availableSlots: int):
        __availableSlots = availableSlots

    def __setIsRunning(self, isRunning: bool):
        __isRunning = isRunning

    def __getAvailableSlots(self):
        return self.__availableSlots

    def __getTeamName(self):
        return self.__teamName

    def __getIsRunning(self):
        return self.__isRunning

    """ -------------------------------------------Public members functions------------------------------------------"""
    def start(self) -> int:
        """Starting the main loop of the AI
            This is infinity loop while :
                - player is alive
                - client is connected
        """
        self.__setIsRunning(True)
        while self.__getIsRunning():
            self.__playerStrategyManagement()
            if not self.__isPlayerAlive:
                self.__setIsRunning(False)
                print("Player just died. Disconnected\n")
        return 0

    """ -------------------------------------------Private members functions---------------------------------------- """
    """ These functions are common in every strategies"""

    def __playerStrategyManagement(self):
        """Main function of the Core
            Used to determine which action is better to do depending on the current situation of the player
        """
    def __survive(self):
        """This is used by the AI to find food and get food as fast as possible"""

    def __elevation(self):
        """This is used when the AI thinks it's the good timing to level up"""

    def __teamCall(self, nbPlayers: int):
        """This is used by the AI to call 'nbPlayers' of the team in order to elevation
            Param : nbPlayers : int, the amount of player needed for the elevation
        """

    def __fork(self):
        """This is used by the AI to authorize a new connection"""

    def __isPlayerAlive(self) -> bool:
        """This function call the server to know if the player is alive or not
            Return : True if the player is alive
                     False otherwise
        """
        return True

    """These functions are used by medium strategy"""
    def __getSpecificComponent(self):
        """This is used by the AI in case of needing a specific component and get it
            Here, the AI is making a risky bet because it doesn't do anything else than get the specific component
            Make sure to have enough food before calling this function
        """
    def __denyComponents(self):
        """This is used by high level player in the game (7, 8)
            The AI consider a higher or lower value of the objects depending on their density in the map
            The higher the value, the more likely is that the AI will pick up the object
        """
    def __requestComponentFromTeam(self, component: str):
        """This is used by the AI to request specific components from the team
            Param : component : str, representing the specific needed by the AI
        """
