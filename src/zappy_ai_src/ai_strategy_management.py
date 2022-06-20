from ai_function_wrapper import ServerWrapper
from ai_handle_response import Inventory, Map, Tile

"""---------------------------------------------FILE BRIEF-----------------------------------------------------------"""
"""
    The goal of the AI it's obviously to win the game.
    To achieve it, AI making its own choices divided in 3 big groups of actions called strategy
    We can see 3 different strategies :
        - Survival strategy: Consisting of getting only food to survive.
            The goal of this strategy is to stay alive.
        - Farming strategy : Consisting of getting the most of components in a period P of time,
            making sure the team is always full of players
            The goal of this strategy is to farm and level up as fast as possible
            We can see this strategy in early/mid game (Level 1-6).
        - Aggressive strategy : Consisting of denying the others teams, bumping enemies, intercept enemies call...
            The goal of this strategy is to avoid enemy teams to win the game
            We can see this strategy in very late game (Level 7-8).
"""

"""---------------------------------------------Static variables-----------------------------------------------------"""

LEVEL_MAX = 8

"""Player is starting the game with 120 food which represents 1200 unit of time
    like you probably know 1 food == 10 units of time
"""
FOOD_START = 1260

"""This static member represents a safety margin when call action,
    its warns of an imminent death of the player just after the execution of an action
"""
SAFETY_MARGIN = 300

"""This is this indication for the AI to switch to survival strategy under or equal to 300 units of time"""
FOOD_LIMIT = 300

"""This static array provides information of the density of the components in the map
    Values are given as a percentage
"""
COMPONENT_DENSITY = {
    "food": 50,
    "linemate": 30,
    "deraumere": 15,
    "sibur": 10,
    "mendiane": 10,
    "phiras": 8,
    "thystame": 5
}

"""This static array provides information of the scheduling for each command
    Keys represents the command and values represents time/f to execute the command
        where f is the time units
"""
TIME_LIMIT = {
    "forward": 7,
    "right": 7,
    "left": 7,
    "look": 7,
    "inventory": 1,
    "broadcast": 7,
    "fork": 42,
    "eject": 7,
    "take": 7,
    "set": 7,
    "incantation": 300
}

"""This static array is used to know every requirements for elevation
    - Player represents the amount of player needed for elevation
    - From Linemate to thystame are the name of component and the amount needed for elevation per level
"""
LEVEL_UP_REQUIREMENTS = [{},
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
                             "player": 2,  # LEVEL 3
                             "linemate": 1,
                             "deraumere": 1,
                             "sibur": 1,
                             "mendiane": 0,
                             "phiras": 0,
                             "thystame": 0
                         },
                         {
                             "player": 2,  # LEVEL 4
                             "linemate": 2,
                             "deraumere": 0,
                             "sibur": 1,
                             "mendiane": 0,
                             "phiras": 2,
                             "thystame": 0
                         },
                         {
                             "player": 4,  # LEVEL 5
                             "linemate": 1,
                             "deraumere": 1,
                             "sibur": 2,
                             "mendiane": 0,
                             "phiras": 1,
                             "thystame": 0
                         },
                         {
                             "player": 4,  # LEVEL 6
                             "linemate": 1,
                             "deraumere": 2,
                             "sibur": 1,
                             "mendiane": 3,
                             "phiras": 0,
                             "thystame": 0
                         },
                         {
                             "player": 6,  # LEVEL 7
                             "linemate": 1,
                             "deraumere": 2,
                             "sibur": 3,
                             "mendiane": 0,
                             "phiras": 1,
                             "thystame": 0
                         },
                         {
                             "player": 6,  # LEVEL 8
                             "linemate": 2,
                             "deraumere": 2,
                             "sibur": 2,
                             "mendiane": 2,
                             "phiras": 2,
                             "thystame": 1
                         }
                         ]

"""-------------------------------------------AI Class---------------------------------------------------------"""

class Ai:
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
        self.__inventory = Inventory("food 1260, linemate 0, deraumere 0, sibur 0, mendiane 0, phiras 0, thystame 0")

        """This is an ephemeral representation of the player's view of the map.
            Of course, the player's vision depends on his current level
            Initialized with blank string by default.
            This private member can be useful to develop and use relevant action from the AI
        """
        self.__visionOfTheMap = Map("")

        """This private member represents the index of the current target tile of the AI.
            It can be useful to use relevant action from the AI in component research as example.
            Set as int: -1 by default.
        """
        self.__targetTileIndex = -1

        """This private member represents the currently most needed component by the AI.
            It can be useful to use relevant action from the AI in component research as example.
            Set as str: 'food' by default
        """
        self.__targetComponent = "food"

        """This private member represents the current level of the player
            It impacts on his vision of the map and his requirements of elevation
            Set as int: 1 by default and can reach level 8 maximum
        """
        self.__playerCurrentLevel = 1

    def __del__(self):
        """Default Destructor of the Core class"""
        self.running = False

    """----------------------------------------Getter and Setter for AI class----------------------------------------"""

    def __decrAvailableSlots(self):
        self.__availableSlots -= 1

    def __setIsRunning(self, isRunning: bool):
        self.__isRunning = isRunning

    def __setInventory(self, inventoryResponse: str):
        self.__inventory.fillInventory(inventoryResponse)

    def __setVisionOfTheMap(self, lookResponse: str):
        self.__visionOfTheMap.fillMap(lookResponse)

    def __setTargetTile(self, index: int):
        self.__targetTileIndex = index

    def __setTargetComponent(self, targetComponent: str):
        self.__targetComponent = targetComponent

    def __incrPlayerCurrentLevel(self):
        self.__playerCurrentLevel += 1

    def __getAvailableSlots(self):
        return self.__availableSlots

    def __getTeamName(self) -> str:
        return self.__teamName

    def __getIsRunning(self) -> bool:
        return self.__isRunning

    def __getInventory(self) -> Inventory:
        return self.__inventory

    def __getVisionOfTheMap(self) -> Map:
        return self.__visionOfTheMap

    def __getTargetTileIndex(self) -> int:
        return self.__targetTileIndex

    def __getTargetComponent(self) -> str:
        return self.__targetComponent

    def __getPlayerCurrentLevel(self) -> int:
        return self.__playerCurrentLevel

    """This is used to know the maximal range of the player's vision depending on his level
        The player range could be calculate as follow : maxRange = (x+1)²
            where x is the level of the player
    """
    def __getPlayerMaxRange(self) -> int:
        playerLevel = self.__playerCurrentLevel + 1
        return (playerLevel * playerLevel)

    """ -------------------------------------------Public members functions------------------------------------------"""

    def start(self) -> int:
        """Starting the main loop of the AI
            This is infinity loop while :
                - player is alive
                - client is connected
        """
        self.__setIsRunning(True)
        self.__initAI()
        while self.__getIsRunning():
            self.__playerStrategyManagement()
            if self.__lib.GetUnexpectedResponseState():
                self.__unexpectedResponseManagement()
        self.__lib.DLLibWrapper.closeLibray()
        return 0

    """ -------------------------------------------Private members functions---------------------------------------- """

    """This is used at start of the AI loop to initialize inventory and vision to have a base"""
    def __initAI(self):
        if self.__lib.getNecessaryFunctions():
            print("[AI] libzappy_ai_api charged, SUCCESS!")
        else:
            print("[AI] cannot charge libzappy_ai_api, ERROR!")
        self.__lib.AskLook()
        while 1:
            if self.__lib.GetResponseState():
                break
        self.__setVisionOfTheMap(self.__lib.GetRepLook())

    """This is used by AI to manage every unexpected response send by the server like :
        - Death of the player
        - Eject from another player (not implemented at the moment)
        - Broadcast, sending message from another player (not implemented at the moment)
    """
    def __unexpectedResponseManagement(self):
        response = self.__lib.GetUnexpectedResponse()
        if response == "dead":
            self.__setIsRunning(False)

    """-------------------------------------------------DETAILS---------------------------------------------------------
        These functions are common in every strategies
        These functions are considered as actions
    """

    def __playerStrategyManagement(self):
        """Main function of the AI Class
            Used to determine which strategy is better to use depending on the current situation of the player
        """
        if self.__getInventory().GetFood() <= FOOD_LIMIT:
            self.__survive()
        elif self.__getPlayerCurrentLevel() >= 7:
            self.__deny()
        else:
            self.__farming()
        self.__actionsProceed()

    def __actionsProceed(self):
        """This is used to trigger actions depending on previous configuration of the strategy
            Like getting the most required component at a time T
        """
        component = self.__getTargetComponent()
        for i in range(self.__getPlayerMaxRange()):
            if self.__isThereComponentOnThisTile(component, self.__visionOfTheMap.GetTile(i + 2)):
                self.__setTargetTile(i + 2)
                break
        if self.__getTargetTileIndex() == 2:
            self.__lib.AskTakeObject(component)
            while 1:
                if self.__lib.GetResponseState():
                    break
            self.__lib.GetRepTakeObject()
        self.__lib.AskForward()
        while 1:
            if self.__lib.GetResponseState():
                break
        self.__lib.GetRepForward()
        self.__lib.AskLook()
        while 1:
            if self.__lib.GetResponseState():
                break
        self.__setVisionOfTheMap(self.__lib.GetRepLook())

    def __isThereComponentOnThisTile(self, component: str, tile: Tile, x=None) -> bool:
        """This is used by AI to know if the specific component is present on the specific tile
            Param   :     component:  str,    representing the specific component needed by the AI
            Param   :     tile:       Tile,   representing the specific tile where AI search component
            return  :     True if component is present
                          False otherwise
        """
        result = {
            'food': lambda x: tile.food,
            'sibur': lambda x: tile.sibur,
            'phiras': lambda x: tile.phiras,
            'linemate': lambda x: tile.linemate,
            'deraumere': lambda x: tile.deraumere,
            'mendiane': lambda x: tile.mendiane,
            'thystame': lambda x: tile.thystame
        }[component](x)
        if (result):
            return True
        return False

    def __isThisActionRealisable(self, action: str):
        """This is used by the AI to know if the action is realisable or not depending on its food"""
        if not self.__getInventory().GetFood() + SAFETY_MARGIN >= TIME_LIMIT.get(action):
            return False
        return True

    def __tryElevation(self) -> bool:
        """This is used when the AI thinks it's the good timing to level up
            return :    True if successfully asked the server
                        False otherwise
        """
        levelOfPlayer = self.__getPlayerCurrentLevel()
        if not self.__getInventory().GetFood() >= TIME_LIMIT.get("incantation"):
            return False
        if not self.__getRequiredComponent() == "nothing":
            return False
        if not self.__getVisionOfTheMap().GetTile(0).player == LEVEL_UP_REQUIREMENTS[levelOfPlayer].get("player"):
            return False
        if not self.__isThisActionRealisable("incantation"):
            return False
        self.__lib.AskIncantation()
        while 1:
            if self.__lib.GetResponseState():
                break
        if not self.__lib.GetRepIncantation():
            return False
        self.__incrPlayerCurrentLevel()
        return True

    def __teamCall(self, action: str) -> bool:
        """This is used by the AI to call 'nbPlayers' of the team in order to elevation
            To emit a message, the client must send the following command to the server:
            'Broadcast message\n'
                where message is following this format : 'teamName;amountOfPlayer;action'
            return :    True if the request successfully send to the server
                        False Otherwise
        """
        if not self.__isThisActionRealisable("broadcast"):
            return False
        levelOfPlayer = self.__getPlayerCurrentLevel()
        if action == "elevation":
            nbPlayer = LEVEL_UP_REQUIREMENTS[levelOfPlayer].get('player')
        else:
            nbPlayer = 1
        message = self.__getTeamName() + ';' + str(nbPlayer) + ';' + action + '\n'
        self.__lib.AskBroadcastText("Broadcast " + message)
        return True

    def __fork(self) -> bool:
        """This is used by the AI to authorize a new connection
            return :    True if the request successfully send to the server
                        False Otherwise
        """
        if not self.__isThisActionRealisable("fork"):
            return False
        if self.__getAvailableSlots() == 0:
            return False
        self.__lib.AskFork()
        while 1:
            if self.__lib.GetResponseState():
                break
        if not self.__lib.GetRepFork():
            return False
        self.__decrAvailableSlots()
        return True

    """-------------------------------------------------DETAILS---------------------------------------------------------
        These functions are used by survival strategy
        These functions are considered as decisions
    """

    def __survive(self):
        """This is used by the AI to find food and get food as fast as possible"""
        self.__setTargetComponent("food")

    """-------------------------------------------------DETAILS---------------------------------------------------------
        These functions are used by aggressive strategy
        These functions are considered as actions
    """

    def __deny(self):
        """This is the main function of aggressive strategy, it manages all actions to deny other teams
            and then avoid their win
        """
        pass

    def __takeSpecificComponent(self):
        """This is used by the AI in case of needing a specific component and get it
            Here, the AI is making a risky bet because it doesn't do anything else than get the specific component
            Make sure to have enough food before calling this function
        """
        pass

    def __denyComponents(self):
        """This is used by high level player in the game (7, 8)
            The AI consider a higher or lower value of the objects depending on their density in the map
            The higher the value, the more likely is that the AI will pick up the object
        """
        pass

    def __requestComponentFromTeam(self, component: str):
        """This is used by the AI to request specific components from the team
            Param : component: str, representing the specific component needed by the AI
        """
        pass

    """-------------------------------------------------DETAILS---------------------------------------------------------
                These functions are used by farming strategy
                These functions are considered as utils
    """

    def __farming(self):
        """This is the main function of farming strategy, it manages all actions to get components as fast as possible
        """
        self.__setTargetComponent(self.__getRequiredComponent())

    def __findClosestTileFromComponent(self, component: str) -> int:
        """This is used by AI to find the closest tile depending on the component requested
            param   : component: str, representing the required component
            return  : int, representing the index of the closest tile including the component (ref: map Class)
        """
        pass

    def __getRequiredComponent(self) -> str:
        """This is used by the AI to know what is the required component missing for elevation
            Ordered from rarest to the least rare component
            return : the required component or nothing if all requirements are met
        """
        playerLevel = self.__getPlayerCurrentLevel()
        if self.__getInventory().GetThystame() < LEVEL_UP_REQUIREMENTS[playerLevel].get("thystame"):
            return "thystame"
        if self.__getInventory().GetPhiras() < LEVEL_UP_REQUIREMENTS[playerLevel].get("phiras"):
            return "phiras"
        if self.__getInventory().GetMendiane() < LEVEL_UP_REQUIREMENTS[playerLevel].get("mendiane"):
            return "mendiane"
        if self.__getInventory().GetSibur() < LEVEL_UP_REQUIREMENTS[playerLevel].get("sibur"):
            return "sibur"
        if self.__getInventory().GetDeraumere() < LEVEL_UP_REQUIREMENTS[playerLevel].get("deraumere"):
            return "deraumere"
        if self.__getInventory().GetLinemate() < LEVEL_UP_REQUIREMENTS[playerLevel].get("linemate"):
            return "linemate"
        return "nothing"
