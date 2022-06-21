from ai_function_wrapper import ServerWrapper
from sys import stderr
from ai_strategy_management import Ai
from ai_safe_error import safeExitError

class ClientCore:
    def __init__(self, teamName : str, ip : str, port : int):
        """ Constructor of the ClientCore Class """
        self.__teamName : str = teamName
        self.__ip  : str = ip
        self.__port : int = port
        self.serverInterface : ServerWrapper = ServerWrapper("./src/zappy_ai_src/libzappy_ai_api.so")
        self.__mapY : int = 0
        self.__mapX : int = 0
        self.__placesLeft : int = 0

    def connectToServer(self) -> bool:
        """
        Connect the Client to the server
        Return True if success
        Return False Otherwise
        """
        if not self.serverInterface.getNecessaryFunctions():
            return False

        if not self.serverInterface.ConnectToServer(self.__ip, self.__port):
            print("There is no server at this ip / port.", file=stderr)
            return False

        while not self.serverInterface.GetResponseState():
            pass
        if not self.serverInterface.GetRepConnectToServer():
            print("Failed to connect to server", file=stderr)
            return False

        if not self.serverInterface.AskJoinTeam(self.__teamName):
            safeExitError()
        while not self.serverInterface.GetResponseState():
            pass
        info : str = self.serverInterface.GetRepJoinTeam()
        infos = info.split(",")
        try:
            self.__mapX = int(infos[0])
            self.__mapY = int(infos[1])
            self.__placesLeft = int(infos[2])
        except ValueError:
            print("The values of the GetRepJoinTeam() aren't integers", file=stderr)
            return False
        return True

    def run(self) -> None:
        """ Main Loop of the ClientCore """
        if not self.connectToServer():
            return
        newIA : Ai = Ai(self.__placesLeft, self.__teamName)
        newIA.start()
        pass