from collections import namedtuple

from ai_function_wrapper import ServerWrapper
from ai_handle_response import Inventory, Map, Tile
from sys import stderr
from ai_safe_error import safeExitError
from ai_queue_wrapper import AIQueues
from ai_broadcast_to_object import BroadcastInfo

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

"""Player is starting the game with 10 food which represents 1260 unit of time
    like you probably know 1 food == 126 units of time
    Value is given in units of time
"""
FOOD_START = 1260

"""This static member represents a safety margin when call action,
    its warns of an imminent death of the player just after the execution of an action
"""
SAFETY_MARGIN = 300

"""This is indication for the AI to switch to survival strategy under or equal to 300 units of time"""
FOOD_LIMIT = 300

"""This is the limit before the next update of the mapVision"""
MAP_VISION_UPDATE_LIMIT = 50

"""This is the limit before the next update of the inventory"""
INVENTORY_UPDATE_LIMIT = 50

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

"""This static array provides information for moving in the map
    It lists the tiles that are front of the player depending on the index of the tile you want to reach
    - First element represents the indexes of the tiles that will always be in front of the player
        It calculates with the following thinking :
        x = n² + n
            where n is the level of player and x the index we are looking for
    - Second element represents the maximum index of the line containing the target tile
        It calculates with the following thinking :
        x = n² + 2n
"""

PathVector = namedtuple("PathVector", ["frontTileIndex", "maxIndexInLine"])
PATH_REFERENCES = [PathVector(0, 0),       # UNUSED LEVEL 0
                   PathVector(2, 3),       # LEVEL 1
                   PathVector(6, 8),       # LEVEL 2
                   PathVector(12, 15),     # LEVEL 3
                   PathVector(20, 24),     # LEVEL 4
                   PathVector(30, 35),     # LEVEL 5
                   PathVector(42, 48),     # LEVEL 6
                   PathVector(56, 63),     # LEVEL 7
                   PathVector(72, 80),     # LEVEL 8
                   ]

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
        self.__lib = ServerWrapper("./src/zappy_ai_src/libzappy_ai_api.so")

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

        """This is used by AI to know if it reached the tile targeted previously, in order to set another one"""
        self.__targetTileReached = True

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

        """This private member represents the frequency of time units used in scheduling management on server"""
        self.__frequency = 0

        """This private member represents the counter of ticks to know when the temporary inventory should be updated"""
        self.__inventoryTicksCpt = 0

        """This private member represents the counter of ticks to know when the temporary mapVision should be updated"""
        self.__mapVisionTicksCpt = 0

        """This private member informs if the player is able
            to move or not, to participate of teamCall of something else
        """
        self.__ableToMove = True

        self.__Queues : AIQueues = AIQueues(10)


    def __del__(self):
        """Default Destructor of the AI class"""
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

    def __setTargetTileReached(self, status: bool):
        self.__targetTileReached = status

    def __setTargetComponent(self, targetComponent: str):
        self.__targetComponent = targetComponent

    def __setAbleToMove(self, ability: bool):
        self.__ableToMove = ability

    def __incrPlayerCurrentLevel(self):
        self.__playerCurrentLevel += 1

    def __incrInventoryTicksCpt(self):
        self.__inventoryTicksCpt += 1

    def __resetInventoryTicksCpt(self):
        self.__inventoryTicksCpt = 0

    def __incrMapVisionTicksCpt(self):
        self.__mapVisionTicksCpt += 1

    def __resetMapVisionTicksCpt(self):
        self.__mapVisionTicksCpt = 0

    def __setFrequency(self, frequency: int):
        self.__frequency = frequency

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

    def __getTargetTileReached(self) -> bool:
        return self.__targetTileReached

    def __getTargetComponent(self) -> str:
        return self.__targetComponent

    def __getPlayerCurrentLevel(self) -> int:
        return self.__playerCurrentLevel

    def __getFrequency(self) -> int:
        return self.__frequency

    def __getInventoryTicksCpt(self) -> int:
        return self.__inventoryTicksCpt

    def __getMapVisionTicksCpt(self) -> int:
        return self.__mapVisionTicksCpt

    def __getAbleToMove(self) -> bool:
        return self.__ableToMove

    def __getPlayerMaxRange(self) -> int:
        """This is used to know the maximal range of the player's vision depending on his level
                The player range could be calculate as follow : maxRange = (x+1)²
                    where x is the level of the player
            """
        playerLevel = self.__playerCurrentLevel + 1
        return playerLevel * playerLevel

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
            self.__ticksCptManagement()
        return 0

    """ -------------------------------------------Private members functions---------------------------------------- """

    def __initAI(self):
        """This is used at start of the AI loop to initialize inventory and vision to have a base"""
        if self.__lib.getNecessaryFunctions():
            print("[AI] libzappy_ai_api charged, SUCCESS!")
        else:
            print("[AI] cannot charge libzappy_ai_api, ERROR!")
        self.__initFrequency()

    def __initFrequency(self):
        """This is used by Ai to initialize the frequency which is very useful in decision-making"""
        if not self.__lib.AskLook():
            safeExitError()
        while 1:
            if self.__lib.GetResponseState():
                break
        self.__setVisionOfTheMap(self.__lib.GetRepLook())
        tmpFood = self.__inventory.GetFood()
        self.__lib.AskInventory()
        while not self.__lib.GetResponseState():
            pass
        self.__setInventory(self.__lib.GetRepInventory())
        self.__setFrequency(int((tmpFood - self.__inventory.GetFood()) / 2))

    def __unexpectedResponseManagement(self):
        """This is used by AI to manage every unexpected response send by the server like :
                - Death of the player
                - Eject from another player (not implemented at the moment)
                - Broadcast, sending message from another player (not implemented at the moment)
        """
        pos = 0
        response : str = self.__lib.GetUnexpectedResponse()
        if response == "dead":
            self.__setIsRunning(False)
            return
        if response.startswith("message"):
            infos = response.split(", ")
            teamName = infos[1]
            if teamName != self.__teamName:
                ## DENY ## TO IMPLEMENT ##
                return
            try:
                pos = int(infos[0].split(" ")[1])
            except ValueError as e:
                print(e)
            action = infos[2]
            if action == "incantation":
                return BroadcastInfo(action, teamName, pos, int(infos[3]), int (infos[4]), "")
            if action == "give":
                return BroadcastInfo(action, teamName, pos, 0, 0, infos[2])


    def __ticksCptManagement(self):
        """This is used by AI to manage useful ticks counter
            at each turn of the loop, Ai increments mapVisionTicksCpt & inventoryTicksCpt
            and when (limit * f) is reached, it triggers the update action
                where f is the frequency
        """
        self.__incrMapVisionTicksCpt()
        self.__incrInventoryTicksCpt()
        if self.__getInventoryTicksCpt() >= INVENTORY_UPDATE_LIMIT * self.__getFrequency():
            self.__lib.AskInventory()
            self.__resetInventoryTicksCpt()
            if self.__waitForAction():
                return
            self.__inventory.fillInventory(self.__lib.GetRepInventory())
        if self.__getMapVisionTicksCpt() >= MAP_VISION_UPDATE_LIMIT * self.__getFrequency():
            self.__lib.AskLook()
            self.__resetMapVisionTicksCpt()
            if self.__waitForAction():
                return
            self.__inventory.fillInventory(self.__lib.GetRepLook())
    """-------------------------------------------------DETAILS---------------------------------------------------------
        These functions are common in every strategies
        These functions are considered as actions
    """

    def __playerStrategyManagement(self):
        """Main function of the AI Class
            Used to determine which strategy is better to use depending on the current situation of the player
        """
        self.__setStrategy()
        self.__actionsProceed()

    def __setStrategy(self):
        """This is used by Ai on each tick of loop to define the best strategy applied"""
        if self.__getInventory().GetFood() <= FOOD_LIMIT:
            self.__survive()
        elif self.__getPlayerCurrentLevel() >= 7:
            self.__deny()
        else:
            self.__farming()

    def __waitForAction(self) -> bool:
        """
        Wait for a launched action and handle the possible unexpected responses
        Return true if the Client is running
        Otherwise return False
        """
        while not self.__lib.GetResponseState():
            pass
        if self.__lib.GetUnexpectedResponseState():
            self.__unexpectedResponseManagement()
            return self.__getIsRunning()
        else:
            return True

    def __setAnotherTargetTile(self, component: str):
        """"This is used to set another target as a tile if the first one got reached by the player"""
        for i in range(0, self.__getPlayerMaxRange()):
            if self.__isThereComponentOnThisTile(component, self.__visionOfTheMap.GetTile(i)):
                self.__setTargetTile(i)
                break
        self.__setTargetTileReached(False)

    def __handleQueuesResponses(self, response) -> None:
        """
        From the response object given by self.__Queues.emptyServerQueue()
        Find the correct way to get the response and process it
        Only the getter of Forwarf, Right, Left, Take/Place Object, Eject, Fork and Incantation are handled
        """
        responseTreated : bool = False

        while not responseTreated and self.__getIsRunning():
            if not self.__lib.GetResponseState():
                continue
            if self.__lib.GetUnexpectedResponseState():
                self.__unexpectedResponseManagement()
                continue
            if response in [self.__lib.GetRepForward, self.__lib.GetRepTurnLeft, self.__lib.GetRepTurnRight]:
                self.__Queues.decMov() if response() else self.__setTargetTileReached(True)
            if response in [self.__lib.GetRepTakeObject, self.__lib.GetRepPlaceObject, self.__lib.GetRepEject]:
                pass
            if response == self.__lib.GetRepFork and not self.__lib.GetRepFork():
                self.__availableSlots += 1
            if response == self.__lib.GetRepIncantation and self.__lib.GetRepIncantation() > 0:
                self.__incrPlayerCurrentLevel()
            responseTreated = True
        if not self.__Queues.isMovementLeft():
            self.__setTargetTileReached(True)

    def __actionsProceed(self):
        """This is used to trigger actions depending on previous configuration of the strategy
            Like getting the most required component at a time T
        """
        component = self.__getTargetComponent()
        if self.__getTargetTileReached():
            self.__setAnotherTargetTile(component)
        else:
            if not self.__lib.AskTakeObject(component):
                safeExitError()
            if not self.__waitForAction():
                return
            self.__lib.GetRepTakeObject()
        self.__reachSpecificTile(self.__getTargetTileIndex())
        if self.__Queues.isServerQueueFull():
            response = self.__Queues.emptyServerQueue()
            self.__handleQueuesResponses(response)
        self.__Queues.addInServerQueue()

    def __isThereComponentOnThisTile(self, component: str, tile: Tile) -> bool:
        """This is used by AI to know if the specific component is present on the specific tile
            Param   :     component:  str,    representing the specific component needed by the AI
            Param   :     tile:       Tile,   representing the specific tile where AI search component
            return  :     True if component is present
                          False otherwise
        """
        componentTemplate = {
            'food': tile.food,
            'sibur': tile.sibur,
            'phiras': tile.phiras,
            'linemate': tile.linemate,
            'deraumere': tile.deraumere,
            'mendiane': tile.mendiane,
            'thystame': tile.thystame
        }
        return componentTemplate[component] != 0

    def __isThisActionRealisable(self, action: str) -> bool:
        """This is used by the AI to know if the action is realisable or not depending on its food"""
        return self.__getInventory().GetFood() + SAFETY_MARGIN >= TIME_LIMIT.get(action)

    def __tryElevation(self) -> bool:
        """This is used when the AI thinks it's the good timing to level up
            return :    True if successfully asked the server
                        False otherwise
        """
        levelOfPlayer = self.__getPlayerCurrentLevel()
        if self.__getInventory().GetFood() < TIME_LIMIT.get("incantation"):
            return False
        if self.__getRequiredComponent() != "nothing":
            return False
        if self.__getVisionOfTheMap().GetTile(0).player != LEVEL_UP_REQUIREMENTS[levelOfPlayer].get("player"):
            return False
        if not self.__isThisActionRealisable("incantation"):
            return False
        if not self.__lib.AskIncantation():
            safeExitError()
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
        nbPlayer = LEVEL_UP_REQUIREMENTS[levelOfPlayer].get('player') if action == "elevation" else 1
        if not self.__lib.AskBroadcastText(f"Broadcast {self.__getTeamName()}, {action}, {nbPlayer}\n"):
            safeExitError()
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
        if not self.__lib.AskFork():
            safeExitError()
        while 1:
            if self.__lib.GetResponseState():
                break
        if not self.__lib.GetRepFork():
            return False
        self.__decrAvailableSlots()
        return True

    def __reachSpecificTile(self, index: int):
        """This is used by AI to reach a specific tile depending on the index given as argument
            This function can be very useful in many cases like get a specific component for elevation
            or maybe to join teamMates to help them for elevation
            This function will set the move queue with getMethods after calling asking methods of the API
            Param :     index: int, representing the index of the tile you want to reach
        """
        nbForwardSteps = 0
        frontTileIndex = 0
        for vector in reversed(PATH_REFERENCES[1:]):
            if index <= vector.maxIndexInLine:
                frontTileIndex = vector.frontTileIndex
                nbForwardSteps = PATH_REFERENCES.index(vector)
        for _ in range(0, nbForwardSteps):
            self.__lib.AskForward()
            self.__Queues.addInAiQueue(self.__lib.GetRepForward)
            self.__Queues.incrMov()
        nbForwardSteps = index - frontTileIndex
        if nbForwardSteps < 0:
            self.__lib.AskTurnLeft()
            nbForwardSteps *= -1
            self.__Queues.addInAiQueue(self.__lib.GetRepTurnLeft)
            self.__Queues.incrMov()
        elif nbForwardSteps == 0:
            return
        else:
            self.__lib.AskTurnRight()
            self.__Queues.addInAiQueue(self.__lib.GetRepTurnRight)
            self.__Queues.incrMov()
        for _ in range(0, nbForwardSteps):
            self.__lib.AskForward()
            self.__Queues.addInAiQueue(self.__lib.GetRepForward)
            self.__Queues.incrMov()
    """-------------------------------------------------DETAILS---------------------------------------------------------
        These functions are used by survival strategy
        These functions are considered as decisions
    """

    def __survive(self):
        """This is used by the AI to find food and get food as fast as possible"""
        self.__setTargetComponent("food")
        self.__setAbleToMove(False)

    """-------------------------------------------------DETAILS---------------------------------------------------------
        These functions are used by aggressive strategy
        These functions are considered as actions
    """

    def __deny(self):
        """This is the main function of aggressive strategy, it manages all actions to deny other teams
            and then avoid their win
        """
        self.__setAbleToMove(True)

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
        self.__setAbleToMove(True)

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
        componentList = [
            "thystame",
            "phiras",
            "mendiane",
            "sibur",
            "deraumere",
            "linemate"
        ]
        for component in componentList:
            if self.__getInventory()[component] < LEVEL_UP_REQUIREMENTS[playerLevel].get(component):
                return component
        return "nothing"
