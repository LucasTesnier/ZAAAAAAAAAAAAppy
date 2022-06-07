from ai_DLLib_wrapper import WrapperAI
import ctypes
import numpy

class ServerWrapper:
    def __init__(self, libName : str):
        """ Constructor of the ServerWrapper class """
        self.DLLibWrapper : WrapperAI = WrapperAI(libName)
        self.DLLibWrapper.openLibrary()

        """ Private members functions pointer """
        self.__ConnectToServer = None
        self.__AskJoinTeam = None
        self.__GetRepJoinTeam = None
        self.__GetResponseState = None
        self.__GetUnexpectedResponseState = None
        self.__GetUnexpectedResponse = None

        """ Ask an action for the AI to the server """
        self.__AskForward = None
        self.__AskTurnRight = None
        self.__AskTurnLeft = None
        self.__AskLook = None
        self.__AskInventory = None
        self.__AskBroadcastText = None
        self.__AskConnectNbr = None
        self.__AskFork = None
        self.__AskEject = None
        self.__AskTakeObject = None
        self.__AskPlaceObject = None
        self.__AskIncantation = None

        """ Get the result of the ask function from the server """
        self.__GetRepForward = None
        self.__GetRepTurnRight = None
        self.__GetRepTurnLeft = None
        self.__GetRepLook = None
        self.__GetRepInventory = None
        self.__GetRepBroadcastText = None
        self.__GetRepConnectNbr = None
        self.__GetRepFork = None
        self.__GetRepEject = None
        self.__GetRepTakeObject = None
        self.__GetRepPlaceObject = None
        self.__GetRepIncantation = None


    def __del__(self):
        """ Destructor of the ServerWrapper class """
        self.DLLibWrapper.closeLibray()


    def getNecessaryFunctions(self) -> bool:
        """
        Get all the functions from the library to have a working AI
        Return True if all the functions exist, false otherwise
        """
        try:
            self.__ConnectToServer = self.DLLibWrapper.getFunctionFromLibrary("c_interface_try_to_connect_to_server")
            self.__AskJoinTeam = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_join")
            self.__GetRepJoinTeam = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_join_response")
            self.__GetResponseState = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_response_state")
            self.__GetUnexpectedResponseState = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_unexpected_response_state")
            self.__GetUnexpectedResponse = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_unexpected_response")
            self.__AskForward = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_forward")
            self.__AskTurnRight = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_right")
            self.__AskTurnLeft = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_left")
            self.__AskLook = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_look")
            self.__AskInventory = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_inventory")
            self.__AskBroadcastText = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_broadcast")
            self.__AskConnectNbr = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_connectable")
            self.__AskFork = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_fork")
            self.__AskEject = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_eject")
            self.__AskTakeObject = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_take")
            self.__AskPlaceObject = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_place")
            self.__AskIncantation = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_incantation")
            self.__GetRepForward = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_forward_response")
            self.__GetRepTurnRight = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_right_response")
            self.__GetRepTurnLeft = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_left_response")
            self.__GetRepLook = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_look_response")
            self.__GetRepInventory = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_inventory_response")
            self.__GetRepBroadcastText = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_broadcast_response")
            self.__GetRepConnectNbr = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_connectable_response")
            self.__GetRepFork = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_fork_response")
            self.__GetRepEject = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_eject_response")
            self.__GetRepTakeObject = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_take_response")
            self.__GetRepPlaceObject = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_place_response")
            self.__GetRepIncantation = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_incantation_response")
        except:
            return False
        return True


    def ConnectToServer(self, machineName : str, port : int):
        """ Wrapped Function : Try to connect the AI to the server """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        b_machineName = machineName.encode("UTF-8")
        c_port = ctypes.c_int(port)
        self.__ConnectToServer(b_machineName, c_port)

    def AskJoinTeam(self, teamName : str) -> None:
        """ Wrapped Function : Try to join a Team """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        b_teamName = teamName.encode("UTF-8")
        self.__AskJoinTeam(ctypes.c_char_p(b_teamName))

    def GetRepJoinTeam(self) -> str:
        """ Wrapped Function : Get the response about joining a team """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__GetRepJoinTeam.restype = ctypes.c_char_p
        c_value = self.__GetRepJoinTeam()
        return c_value.decode("UTF-8")

    def GetResponseState(self) -> bool:
        """ Wrapped Function : Return true if a response is available, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__GetResponseState.restype = ctypes.c_bool
        c_value = self.__GetResponseState()
        return c_value

    def GetUnexpectedResponseState(self) -> bool:
        """ Wrapped Function : Return true if a response is available, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__GetUnexpectedResponseState.restype = ctypes.c_bool
        c_value = self.__GetUnexpectedResponseState()
        return c_value

    def GetUnexpectedResponse(self) -> str:
        """ Wrapped Function : Return the unexpected message """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__GetUnexpectedResponse.restype = ctypes.c_char_p
        c_value = self.__GetUnexpectedResponse()
        return c_value.decode("UTF-8")