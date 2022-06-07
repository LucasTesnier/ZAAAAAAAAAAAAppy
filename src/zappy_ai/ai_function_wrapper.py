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

    def AskForward(self) -> None:
        """ Wrapped Function : Move the client forward """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskForward()

    def AskTurnRight(self) -> None:
        """ Wrapped Function : Turn the client to the right """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskTurnRight()

    def AskTurnLeft(self) -> None:
        """ Wrapped Function : Turn the client to the left """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskTurnLeft()

    def AskLook(self) -> None:
        """ Wrapped Function : Look around the client """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskLook()

    def AskInventory(self) -> None:
        """ Wrapped Function : Ask for the client inventory """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskInventory()

    def AskBroadcastText(self, message : str) -> None:
        """ Wrapped Function : Broadcast a text """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        b_message = message.encode("UTF-8")
        self.__AskBroadcastText(ctypes.c_char_p(b_message))

    def AskConnectNbr(self) -> None:
        """ Wrapped Function : Ask for the place left on the client's team """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskConnectNbr()

    def AskFork(self) -> None:
        """ Wrapped Function : Fork the client to lay an egg """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskFork()

    def AskEject(self) -> None:
        """ Wrapped Function : Eject the other clients of the client's tile """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskEject()

    def AskTakeObject(self, object : str) -> None:
        """ Wrapped Function : Take an object on the client tile """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        b_object = object.encode("UTF-8")
        self.__AskTakeObject(ctypes.c_char_p(b_object))

    def AskPlaceObject(self, object : str) -> None:
        """ Wrapped Function : Place an object on the client tile """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        b_object = object.encode("UTF-8")
        self.__AskPlaceObject(ctypes.c_char_p(b_object))

    def AskIncantation(self) -> None:
        """ Wrapped Function : Start an incantation on the client tile """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskIncantation()

    def GetRepForward(self) -> bool:
        """ Wrapped Function : Get the reponse of AskForward() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__GetRepForward.restype = ctypes.c_bool
        c_value = self.__GetRepForward()
        return c_value

    def GetRepTurnRight(self) -> bool:
        """ Wrapped Function : Get the reponse of AskTurnRight() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__GetRepTurnRight.restype = ctypes.c_bool
        c_value = self.__GetRepTurnRight()
        return c_value

    def GetRepTurnLeft(self) -> bool:
        """ Wrapped Function : Get the reponse of AskTurnLeft() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__GetRepTurnLeft.restype = ctypes.c_bool
        c_value = self.__GetRepTurnLeft()
        return c_value

    def GetRepLook(self) -> str:
        """ Wrapped Function : Get the reponse of AskLook() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__GetRepLook.restype = ctypes.c_char_p
        c_value = self.__GetRepLook()
        return c_value.decode("UTF-8")

    def GetRepInventory(self) -> str:
        """ Wrapped Function : Get the reponse of AskInventory() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__GetRepInventory.restype = ctypes.c_char_p
        c_value = self.__GetRepInventory()
        return c_value.decode("UTF-8")

    def GetRepBroadcastText(self) -> bool:
        """ Wrapped Function : Get the reponse of AskBroadcastText() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__GetRepBroadcastText.restype = ctypes.c_bool
        c_value = self.__GetRepBroadcastText()
        return c_value

    def GetRepConnectNbr(self) -> bool:
        """ Wrapped Function : Get the reponse of AskConnectNbr() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__GetRepConnectNbr.restype = ctypes.c_bool
        c_value = self.__GetRepConnectNbr()
        return c_value

    def GetRepFork(self) -> bool:
        """ Wrapped Function : Get the reponse of AskFork() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__GetRepFork.restype = ctypes.c_bool
        c_value = self.__GetRepFork()
        return c_value