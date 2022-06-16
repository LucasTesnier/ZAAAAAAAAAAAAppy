from numpy import std
from ai_function_wrapper import ServerWrapper
from sys import stderr

class ClientCore:
    def __init__(self, teamName : str, ip : str, port : int):
        """ Constructor of the ClientCore Class """
        self.__teamName : str = teamName
        self.__ip  : str = ip
        self.__port : int = port
        self.serverInterface : ServerWrapper = ServerWrapper("./src/zappy_ai_src/libzappy_ai_api.so")
        self.__mapY : int
        self.__mapX : int

        """ This private member is used to know if at the begin of the AI you need to have more players """
        self.__placesLeft : int

    def connectToServer(self) -> bool:
        """
        Connect the Client to the server
        Return True if success
        Return False Otherwise
        """
        if not self.serverInterface.getNecessaryFunctions():
            return False

        self.serverInterface.ConnectToServer(self.__ip, self.__port)
        while not self.serverInterface.GetResponseState():
            pass
        if not self.serverInterface.GetRepConnectToServer():
            print("Failed to connect to server", file=stderr)
            return False

        self.serverInterface.AskJoinTeam(self.__teamName)
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
        """ BEWARE : You must call connectToServer() first or it will lead to undefined behavior """
        pass
