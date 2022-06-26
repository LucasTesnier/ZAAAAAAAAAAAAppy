from collections import namedtuple

from ai_function_wrapper import ServerWrapper
from ai_handle_response import Inventory, Map, Tile
from ai_safe_error import safeExitError
from ai_broadcast_to_object import BroadcastInfo
from ai_strategy_mode import AiStrategy
from time import time
import random

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

MAX_TEAM_PLAYER = 6

LEVEL_MAX = 8

"""Player is starting the game with 10 food which represents 1260 unit of time
    like you probably know 1 food == 126 units of time
    Value is given in units of time
"""
FOOD_START = 1260

"""This static member represents a safety margin when call action,
    its warns of an imminent death of the player just after the execution of an action
"""
SAFETY_MARGIN = 600

"""This is indication for the AI to switch to survival strategy under or equal to 300 units of time"""
FOOD_LIMIT = 1000

"""This is indication for the AI that it can stop taking food and go farm another component"""
ENOUGH_FOOD = 1200

"""This is the limit before the next try of elevation"""
ELEVATION_LIMIT = 200

"""This is the limit before the next update of the mapVision"""
MAP_VISION_UPDATE_LIMIT = 500

"""This is the limit before the next update of the inventory"""
INVENTORY_UPDATE_LIMIT = 500

DONT_MOVE_LIMIT = 500

"""This is the indication for the AI that it can reach its teammates for elevation or something else"""
CAN_REACH_TEAMMATE = 1000

"""This static array provides information of the density of the components in the map
    Values are given as a percentage
"""
COMPONENT_LIST = [
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
]

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
PATH_REFERENCES = [PathVector(0, 0),  # UNUSED LEVEL 0
                   PathVector(2, 3),  # LEVEL 1
                   PathVector(6, 8),  # LEVEL 2
                   PathVector(12, 15),  # LEVEL 3
                   PathVector(20, 24),  # LEVEL 4
                   PathVector(30, 35),  # LEVEL 5
                   PathVector(42, 48),  # LEVEL 6
                   PathVector(56, 63),  # LEVEL 7
                   PathVector(72, 80),  # LEVEL 8
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

        """This private member represents the time to know when the temporary inventory should be updated"""
        self.__inventoryTime = 0

        """This private member represents the time to know when the temporary mapVision should be updated"""
        self.__mapVisionTime = 0

        """This private member represents the time to know when AI can try an elevation"""
        self.__elevationTime = 0

        self.__dontMoveTime = 0

        """This private member informs if the player is able
            to move or not, to participate of teamCall of something else
        """
        self.__ableToMove = True

        """This private member informs the AI is in survival mode and need to take only food"""
        self.__survivalModeOn = False

        self.__strategyMode = AiStrategy.SURVIVAL

        """This private member informs the AI a stock of food that it needs to take before doing any other actions
            This can be useful to prepare elevation of other big actions like reach another teamMate
        """
        self.__foodStockCpt = 0

    def __del__(self):
        """Default Destructor of the AI class"""
        self.running = False

    """----------------------------------------Getter and Setter for AI class----------------------------------------"""

    def __decrAvailableSlots(self):
        self.__availableSlots -= 1

    def __setIsRunning(self, is_running: bool):
        self.__isRunning = is_running

    def __setInventory(self, inventory_response: str):
        if inventory_response == "":
            return
        self.__inventory.fillInventory(inventory_response)

    def __setVisionOfTheMap(self, look_response: str):
        if look_response == "":
            return
        self.__visionOfTheMap.fillMap(look_response)

    def __setTargetTile(self, index: int):
        self.__targetTileIndex = index

    def __setTargetTileReached(self, status: bool):
        self.__targetTileReached = status

    def __setTargetComponent(self, target_component: str):
        self.__targetComponent = target_component

    def __setAbleToMove(self, ability: bool):
        self.__ableToMove = ability

    def __setAvailableSlots(self, nb_available_slots: int):
        self.__availableSlots = nb_available_slots

    def __incrPlayerCurrentLevel(self):
        self.__playerCurrentLevel += 1

    def __resetInventoryTime(self):
        self.__inventoryTime = time()

    def __resetMapVisionTime(self):
        self.__mapVisionTime = time()

    def __resetElevationTime(self):
        self.__elevationTime = time()

    def __resetDontMoveTime(self):
        self.__dontMoveTime = time()

    def __setFrequency(self, frequency: int):
        self.__frequency = frequency

    def __setStrategyMode(self, mode: AiStrategy):
        self.__strategyMode = mode

    def __setFoodStock(self, stock: int):
        self.__foodStockCpt = stock

    def __decrFoodStock(self):
        self.__foodStockCpt -= 1

    def __getAvailableSlots(self) -> int:
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

    def __getInventoryTime(self) -> float:
        return self.__inventoryTime

    def __getMapVisionTime(self) -> float:
        return self.__mapVisionTime

    def __getElevationTime(self) -> float:
        return self.__elevationTime

    def __getDontMoveTime(self) -> float:
        return self.__dontMoveTime

    def __getAbleToMove(self) -> bool:
        return self.__ableToMove

    def __getPlayerMaxRange(self) -> int:
        """This is used to know the maximal range of the player's vision depending on his level
                The player range could be calculate as follow : maxRange = (x+1)²
                    where x is the level of the player
            """
        playerLevel = self.__playerCurrentLevel + 1
        return playerLevel * playerLevel

    def __getFoodStock(self):
        return self.__foodStockCpt

    """ -------------------------------------------Public members functions------------------------------------------"""

    def start(self):
        """Starting the main loop of the AI
            This is infinity loop while :
                - player is alive
                - client is connected
        """
        self.__initAI()
        self.__fork()
        while True:
            self.__playerStrategyManagement()
            self.__actionsProceed()
            self.__timeManagement()

    """ -------------------------------------------Private members functions---------------------------------------- """

    def __initAI(self):
        """This is used at start of the AI loop to initialize inventory and vision to have a base"""
        if self.__lib.getNecessaryFunctions():
            print("[AI] libzappy_ai_api charged, SUCCESS!")
        else:
            safeExitError(84, "[AI] cannot charge libzappy_ai_api, ERROR!")
        self.__initFrequency()

    def __initFrequency(self):
        """This is used by Ai to initialize the frequency which is very useful in decision-making"""
        if not self.__lib.askLook():
            safeExitError()
        self.__waitServerResponse()
        self.__setVisionOfTheMap(self.__lib.getRepLook())
        tmp_food = self.__inventory.GetFood()
        if not self.__lib.askInventory():
            safeExitError()
        self.__waitServerResponse()
        self.__setInventory(self.__lib.getRepInventory())
        frequency = int((tmp_food - self.__inventory.GetFood()) / 2)
        self.__setFrequency(1 if frequency <= 0 else frequency)

    def __waitServerResponse(self):
        """This is used by AI to wait until the server's response, managing unexpected responses in the same time"""
        while True:
            while not self.__lib.getResponseState():
                pass
            if self.__lib.getUnexpectedResponseState():
                self.__unexpectedResponseManagement()
            else:
                return

    def __unexpectedResponseManagement(self):
        """This is used by AI to manage every unexpected response send by the server like :
                - Death of the player
                - Eject from another player
                - Broadcast, sending message from another player
        """
        response: str = self.__lib.getUnexpectedResponse()
        if response == "" or response == None:
            return
        if "dead" in response:
            safeExitError(84, "Player is dead, disconnected.")
        if "eject" in response:
            self.__ejectManagement(response.split(": ")[1])
        if "message" in response:
            if self.__getInventory().GetFood() >= CAN_REACH_TEAMMATE:
                bc_infos = self.__broadCastResponseManagement(response)
                if bc_infos == None:
                    return
                self.__reachTeammate(self.__getMovementArrayFromBroadcast(bc_infos.pos))

    def __ejectManagement(self, orientation: str):
        """This function occurs when the player got ejected by another player"""
        pass

    def __getDirectionOfTeammate(self, x: int, y: int) -> str:
        """This function is used by AI to know the direction to go to join the teammate"""
        if y >= x and y > 0:
            return "north"
        if y <= x and y < 0:
            return "south"
        if y < x < 0:
            return "west"
        if x > y and x > 0:
            return "east"

    def __forward(self):
        if not self.__lib.askForward():
            safeExitError()
        self.__waitServerResponse()
        self.__lib.getRepForward()

    def __turnRight(self):
        if not self.__lib.askTurnRight():
            safeExitError()
        self.__waitServerResponse()
        self.__lib.getRepTurnRight()

    def __turnLeft(self):
        if not self.__lib.askTurnLeft():
            safeExitError()
        self.__waitServerResponse()
        self.__lib.getRepTurnLeft()

    def __northTravel(self, x: int, y: int):
        for _ in range(y):
            self.__forward()
        if x < 0:
            self.__turnLeft()
            x *= -1
            for _ in range(x):
                self.__forward()
        elif x > 0:
            self.__turnRight()
            for _ in range(x):
                self.__forward()
        else:
            pass

    def __southTravel(self, x: int, y: int):
        for _ in range(2):
            self.__turnLeft()
        y *= -1
        for _ in range(y):
            self.__forward()
        if x < 0:
            self.__turnRight()
            x *= -1
            for _ in range(x):
                self.__forward()
        elif x > 0:
            self.__turnLeft()
            for _ in range(x):
                self.__forward()
        else:
            pass

    def __westTravel(self, x: int, y: int):
        self.__turnLeft()
        x *= -1
        for _ in range(x):
            self.__forward()
        if y < 0:
            self.__turnLeft()
            y *= -1
            for _ in range(y):
                self.__forward()
        elif y > 0:
            self.__turnRight()
            for _ in range(y):
                self.__forward()
        else:
            pass

    def __eastTravel(self, x: int, y: int):
        self.__turnRight()
        for _ in range(x):
            self.__forward()
        if y < 0:
            self.__turnRight()
            y *= -1
            for _ in range(y):
                self.__forward()
        elif y > 0:
            self.__turnLeft()
            for _ in range(y):
                self.__forward()
        else:
            pass

    def __reachTeammate(self, movements):
        """This function is used by AI to reach its teammate from array of coordinates
            params : movements : is and array of coordinates [x, y] representing the movements to do to reach teammate
                    where   x is the x-axis
                            y is the y-axis
        """
        if not self.__ableToMove:
            return False
        x = movements[0]
        y = movements[1]
        direction = self.__getDirectionOfTeammate(x, y)

        if direction == "south":
            self.__southTravel(x, y)
        elif direction == "west":
            self.__westTravel(x, y)
        elif direction == "east":
            self.__eastTravel(x, y)
        self.__setAbleToMove(False)

    def __getMovementArrayFromBroadcast(self, broadCastIndex: int):
        """This function is used by AI to know which movements to do to reach its teammate
            return : movement_res[x, y]
                        where   x is the x-axis of the call
                                y is the y-axis of the call
        """
        X = 0
        Y = 1
        current_index = 0
        y = 0
        x = 0
        delta_y = 0
        delta_x = -1
        movement_res = [X, Y]
        while current_index != broadCastIndex + 1:
            movement_res[X] = x * -1
            movement_res[Y] = y
            if y == x or (y < 0 and y == -x) or (y > 0 and y == 1 - x):
                temp = delta_y
                delta_y = -delta_x
                delta_x = temp
            x += delta_x
            y += delta_y
            current_index += 1
        return movement_res

    def __broadCastResponseManagement(self, response: str):
        """This is used to parse the response of the broadcast
            Notice that all players receiving every broadcast, so it could be possible to intercept enemies'
            broadcast and try to deny their actions
        """
        POS = 0
        TEAM_NAME = 1
        NB_PLAYERS = 2
        ACTION = 3
        REQUIRED_LEVEL = 4
        if response.startswith("message"):
            response = response.split("message ")[1]
            infos = response.split(", ")
            pos = int(infos[POS])
            team_name = infos[TEAM_NAME]
            action = infos[ACTION]
            if team_name != self.__getTeamName():
                return None
            if action == "incantation":
                return BroadcastInfo(action, team_name, pos, int(infos[REQUIRED_LEVEL]), int(infos[NB_PLAYERS]), "")

    def __mapVisionTimeManagement(self):
        delta_time = time() - self.__getMapVisionTime()
        if delta_time >= MAP_VISION_UPDATE_LIMIT / self.__getFrequency():
            self.__look()

    def __inventoryTimeManagement(self):
        delta_time = time() - self.__getInventoryTime()
        if delta_time >= INVENTORY_UPDATE_LIMIT / self.__getFrequency():
            if not self.__lib.askInventory():
                safeExitError()
            self.__waitServerResponse()
            self.__inventory.fillInventory(self.__lib.getRepInventory())
            self.__resetInventoryTime()

    def __elevationManagement(self):
        """This is used by AI to know when is the best moment to try an elevation"""
        if self.__getTargetComponent() != "nothing":
            return
        delta_time = time() - self.__getElevationTime()
        if delta_time >= ELEVATION_LIMIT / self.__getFrequency():
            self.__tryElevation()
            self.__resetElevationTime()

    def __dontMoveManagement(self):
        """This is used to manage the not moving AI during incantation"""
        delta_time = time() - self.__getDontMoveTime()
        if delta_time >= DONT_MOVE_LIMIT / self.__getFrequency():
            self.__setAbleToMove(True)

    def __timeManagement(self):
        """This is used by AI to manage useful time recorder
            at each turn of the loop, Ai increments mapVisionTime & inventoryTime
            and when (limit * f) is reached, it triggers the update action
                where f is the frequency
        """
        if self.__getFoodStock():
            return
        self.__inventoryTimeManagement()
        self.__elevationManagement()
        if not self.__getAbleToMove():
            self.__dontMoveManagement()

    """-------------------------------------------------DETAILS---------------------------------------------------------
        These functions are common in every strategies
        These functions are considered as actions
    """

    def __playerStrategyManagement(self):
        """Main function of the AI Class
            Used to determine which strategy is better to use depending on the current situation of the player
        """
        if self.__getFoodStock():
            return
        if self.__getInventory().GetFood() <= FOOD_LIMIT:
            self.__survive()
        elif self.__getPlayerCurrentLevel() > 7:
            self.__deny()
        else:
            self.__farming()

    def __look(self):
        """This is a wrapper for look command on server, asking server and waiting for the answer"""
        if not self.__lib.askLook():
            safeExitError()
        self.__waitServerResponse()
        self.__visionOfTheMap.fillMap(self.__lib.getRepLook())
        self.__resetMapVisionTime()

    def __actionsProceed(self):
        """This is used to trigger actions depending on previous configuration of the strategy
            Like getting the most required component at a time T
        """
        component = COMPONENT_LIST[random.randint(0, 6)] \
            if self.__getTargetComponent() == "nothing" \
            else self.__getTargetComponent()
        self.__reachSpecificTile(self.__findClosestTileFromComponent(component))
        if not self.__lib.askTakeObject(component):
            safeExitError()
        self.__waitServerResponse()
        if not self.__lib.getRepTakeObject():
            if self.__getAbleToMove():
                self.__forward()
            self.__look()
            self.__reachSpecificTile(self.__findClosestTileFromComponent(component))
        if component == "food" and self.__getFoodStock():
            self.__decrFoodStock()

    def __isThereComponentOnThisTile(self, component: str, tile: Tile) -> bool:
        """This is used by AI to know if the specific component is present on the specific tile
            Param   :     component:  str,    representing the specific component needed by the AI
            Param   :     tile:       Tile,   representing the specific tile where AI search component
            return  :     True if component is present
                          False otherwise
        """
        component_template = {
            'food': tile.food,
            'sibur': tile.sibur,
            'phiras': tile.phiras,
            'linemate': tile.linemate,
            'deraumere': tile.deraumere,
            'mendiane': tile.mendiane,
            'thystame': tile.thystame
        }
        return component_template[component] != 0

    def __isThisActionRealisable(self, action: str) -> bool:
        """This is used by the AI to know if the action is realisable or not depending on its food"""
        return self.__getInventory().GetFood() + SAFETY_MARGIN >= TIME_LIMIT.get(action) * (self.__getFrequency() / 10)

    def __forkManagement(self, needed_players: int):
        player_on_map = MAX_TEAM_PLAYER - self.__getAvailableSlots()
        if needed_players > player_on_map:
            self.__fork()
        else:
            self.__teamCall("incantation")

    def __tryElevation(self) -> bool:
        """This is used when the AI thinks it's the good timing to level up
            return :    True if successfully asked the server
                        False otherwise
        """
        if self.__getRequiredComponent() != "nothing":
            return False
        if not self.__isThisActionRealisable("incantation"):
            return False
        level_of_player = self.__getPlayerCurrentLevel()
        required_player: int = LEVEL_UP_REQUIREMENTS[level_of_player].get("player")
        self.__look()
        if self.__getVisionOfTheMap().GetTile(0).player < required_player:
            self.__teamCall("incantation")
            self.__setAbleToMove(False)
            return False
        if not self.__lib.askIncantation():
            safeExitError()
        self.__waitServerResponse()
        if self.__lib.getRepIncantation() > 0:
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
        level_of_player = self.__getPlayerCurrentLevel()
        nb_player = LEVEL_UP_REQUIREMENTS[level_of_player].get('player') if action == "incantation" else 1
        required_level = self.__getPlayerCurrentLevel() if action == "incantation" else 1
        if not self.__lib.askBroadcastText(f"{self.__getTeamName()}, {nb_player}, {action}, {required_level}\n"):
            safeExitError()
        self.__waitServerResponse()
        self.__lib.getRepBroadcastText()
        return True

    def __fork(self) -> bool:
        """This is used by the AI to authorize a new connection
            return :    True if the request successfully send to the server
                        False Otherwise
        """
        self.__lib.askConnectNbr()
        self.__waitServerResponse()
        self.__setAvailableSlots(self.__lib.getRepConnectNbr())
        if not self.__isThisActionRealisable("fork"):
            return False
        if self.__getAvailableSlots() == 0:
            return False
        if not self.__lib.askFork():
            safeExitError()
        self.__waitServerResponse()
        self.__lib.getRepFork()
        return True

    def __reachSpecificTile(self, index: int):
        """This is used by AI to reach a specific tile depending on the index given as argument
            This function can be very useful in many cases like get a specific component for elevation
            or maybe to join teamMates to help them for elevation
            This function will request ask methods of the API and then wait the response to proceed
            Param :     index: int, representing the index of the tile you want to reach
        """
        if index == -1 or index == 0 or not self.__getAbleToMove():
            return
        nb_forward_steps = 0
        front_tile_index = 0
        for vector in reversed(PATH_REFERENCES[1:]):
            if index <= vector.maxIndexInLine:
                front_tile_index = vector.frontTileIndex
                nb_forward_steps = vector
        for _ in range(0, nb_forward_steps):
            self.__forward()
        nb_forward_steps = index - front_tile_index
        if nb_forward_steps < 0:
            self.__turnLeft()
            nb_forward_steps *= -1
        elif nb_forward_steps == 0:
            return
        else:
            self.__turnRight()
        for _ in range(0, nb_forward_steps):
            self.__forward()

    """-------------------------------------------------DETAILS---------------------------------------------------------
        These functions are used by survival strategy
        These functions are considered as decisions
    """

    def __survive(self):
        """This is used by the AI to find food and get food as fast as possible"""
        if not self.__getFoodStock():
            self.__setFoodStock(20)
        self.__setTargetComponent("food")
        self.__setStrategyMode(AiStrategy.SURVIVAL)
        self.__setAbleToMove(False)

    """-------------------------------------------------DETAILS---------------------------------------------------------
        These functions are used by aggressive strategy
        These functions are considered as actions
    """

    def __deny(self):
        """This is the main function of aggressive strategy, it manages all actions to deny other teams
            and then avoid their win
        """
        self.__setStrategyMode(AiStrategy.AGGRESSIVE)
        self.__setAbleToMove(True)

    def __interceptEnemiesMessage(self, tile_index: int):
        """This function is used by AI when a broadcast occurs, after getting the position of the call
            it's possible for the AI to go on the tile and eject players trying to elevate or something else
        """
        callPos = self.__getMovementArrayFromBroadcast(tile_index)
        if (callPos[0] + callPos[1] + 2) * (7 / self.__frequency) <= self.__getInventory().GetFood() + SAFETY_MARGIN:
            self.__reachSpecificTile(tile_index)
            self.__lib.askEject()
            return True

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
        for i in range(8):
            component = self.__getRequiredComponent(i)
            if component != "nothing":
                break
        self.__setTargetComponent(self.__getRequiredComponent())

    def __findClosestTileFromComponent(self, component: str) -> int:
        """This is used by AI to find the closest tile depending on the component requested
            param   : component: str, representing the required component
            return  : int, representing the index of the closest tile including the component (ref: map Class)
        """
        for i in range(self.__visionOfTheMap.GetMapSize()):
            if self.__visionOfTheMap.GetTile(i)[component] > 0:
                return i
        return -1

    def __getRequiredComponent(self, next_level: int = 0) -> str:
        """This is used by the AI to know what is the required component missing for elevation
            Ordered from rarest to the least rare component
            return : the required component or nothing if all requirements are met
        """
        playerLevel = self.__getPlayerCurrentLevel() + next_level
        if playerLevel > 8:
            playerLevel = 8
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
