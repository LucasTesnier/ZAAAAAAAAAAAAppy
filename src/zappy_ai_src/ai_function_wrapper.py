from ai_DLLib_wrapper import DLLibWrapper
import ctypes
from sys import stderr
from ai_safe_error import safeExitError

class ServerWrapper:
    def __init__(self, libName : str):
        """ Constructor of the ServerWrapper class """
        self.DLLibWrapper : DLLibWrapper = DLLibWrapper(libName)

        """ Private members functions pointer """
        self.__ConnectToServer = None
        self.__GetRepConnectToServer = None
        self.__AskJoinTeam = None
        self.__GetRepJoinTeam = None
        self.__GetResponseState = None
        self.__GetUnexpectedResponseState = None
        self.__GetUnexpectedResponse = None
        self.__GetNetworkState = None

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

    def getNecessaryFunctions(self) -> bool:
        """
        Open the libray
        Get all the functions from the library to have a working AI
        Close the library
        Return True if all the functions exist, false otherwise
        """
        try:
            self.DLLibWrapper.openLibrary()
            self.__ConnectToServer = self.DLLibWrapper.getFunctionFromLibrary("c_interface_try_to_connect_to_server")
            self.__GetRepConnectToServer = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_connect_to_server_response")
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
            self.__GetNetworkState = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_network_state")
        except Exception as ex:
            print(ex, file=stderr)
            return False
        return True


    def ConnectToServer(self, machineName : str, port : int):
        """ Wrapped Function : Try to connect the AI to the server
            Return True if a server has been found
            Return False otherwise
        """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        b_machineName = machineName.encode("UTF-8")
        c_port = ctypes.c_int(port)
        self.__ConnectToServer.restype = ctypes.c_bool
        c_value = self.__ConnectToServer(b_machineName, c_port)
        return c_value

    def GetRepConnectToServer(self) -> bool:
        """ Wrapped Function : Get the response of ConnectToServer() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetRepConnectToServer.restype = ctypes.c_bool
        c_value = self.__GetRepConnectToServer()
        return c_value

    def AskJoinTeam(self, teamName : str) -> bool:
        """ Wrapped Function : Try to join a Team """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        b_teamName = teamName.encode("UTF-8")
        self.__AskJoinTeam.restype = ctypes.c_bool
        c_value = self.__AskJoinTeam(ctypes.c_char_p(b_teamName))
        return c_value

    def GetRepJoinTeam(self) -> str:
        """ Wrapped Function : Get the response about joining a team """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetRepJoinTeam.restype = ctypes.c_char_p
        c_value = self.__GetRepJoinTeam()
        return c_value.decode("UTF-8")

    def GetResponseState(self) -> bool:
        """ Wrapped Function : Return true if a response is available, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetResponseState.restype = ctypes.c_bool
        c_value = self.__GetResponseState()
        return c_value

    def GetUnexpectedResponseState(self) -> bool:
        """ Wrapped Function : Return true if a response is available, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetUnexpectedResponseState.restype = ctypes.c_bool
        c_value = self.__GetUnexpectedResponseState()
        return c_value

    def GetUnexpectedResponse(self) -> str:
        """ Wrapped Function : Return the unexpected message """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetUnexpectedResponse.restype = ctypes.c_char_p
        c_value = self.__GetUnexpectedResponse()
        return c_value.decode("UTF-8")

    def AskForward(self) -> bool:
        """ Wrapped Function : Move the client forward """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskForward.restype = ctypes.c_bool
        c_value = self.__AskForward()
        return c_value

    def AskTurnRight(self) -> bool:
        """ Wrapped Function : Turn the client to the right """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskTurnRight.restype = ctypes.c_bool
        c_value = self.__AskTurnRight()
        return c_value

    def AskTurnLeft(self) -> bool:
        """ Wrapped Function : Turn the client to the left """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskTurnLeft.restype = ctypes.c_bool
        c_value = self.__AskTurnLeft()
        return c_value

    def AskLook(self) -> bool:
        """ Wrapped Function : Look around the client """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskLook.restype = ctypes.c_bool
        c_value = self.__AskLook()
        return c_value

    def AskInventory(self) -> bool:
        """ Wrapped Function : Ask for the client inventory """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskInventory.restype = ctypes.c_bool
        c_value = self.__AskInventory()
        return c_value

    def AskBroadcastText(self, message : str) -> bool:
        """ Wrapped Function : Broadcast a text """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        b_message = message.encode("UTF-8")
        self.__AskBroadcastText.restype = ctypes.c_bool
        c_value = self.__AskBroadcastText(ctypes.c_char_p(b_message))
        return c_value

    def AskConnectNbr(self) -> bool:
        """ Wrapped Function : Ask for the place left on the client's team """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskConnectNbr.restype = ctypes.c_bool
        c_value = self.__AskConnectNbr()
        return c_value

    def AskFork(self) -> bool:
        """ Wrapped Function : Fork the client to lay an egg """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskFork.restype = ctypes.c_bool
        c_value = self.__AskFork()
        return c_value

    def AskEject(self) -> bool:
        """ Wrapped Function : Eject the other clients of the client's tile """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskEject.restype = ctypes.c_bool
        c_value = self.__AskEject()
        return c_value

    def AskTakeObject(self, object : str) -> bool:
        """ Wrapped Function : Take an object on the client tile """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        b_object = object.encode("UTF-8")
        self.__AskTakeObject.restype = ctypes.c_bool
        c_value = self.__AskTakeObject(ctypes.c_char_p(b_object))
        return c_value

    def AskPlaceObject(self, object : str) -> bool:
        """ Wrapped Function : Place an object on the client tile """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        b_object = object.encode("UTF-8")
        self.__AskPlaceObject.restype = ctypes.c_bool
        c_value = self.__AskPlaceObject(ctypes.c_char_p(b_object))
        return c_value

    def AskIncantation(self) -> bool:
        """ Wrapped Function : Start an incantation on the client tile """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__AskIncantation.restype = ctypes.c_bool
        c_value = self.__AskIncantation()
        return c_value

    def GetRepForward(self) -> bool:
        """ Wrapped Function : Get the reponse of AskForward() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetRepForward.restype = ctypes.c_bool
        c_value = self.__GetRepForward()
        return c_value

    def GetRepTurnRight(self) -> bool:
        """ Wrapped Function : Get the reponse of AskTurnRight() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetRepTurnRight.restype = ctypes.c_bool
        c_value = self.__GetRepTurnRight()
        return c_value

    def GetRepTurnLeft(self) -> bool:
        """ Wrapped Function : Get the reponse of AskTurnLeft() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetRepTurnLeft.restype = ctypes.c_bool
        c_value = self.__GetRepTurnLeft()
        return c_value

    def GetRepLook(self) -> str:
        """ Wrapped Function : Get the reponse of AskLook() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetRepLook.restype = ctypes.c_char_p
        c_value = self.__GetRepLook()
        return c_value.decode("UTF-8")

    def GetRepInventory(self) -> str:
        """ Wrapped Function : Get the reponse of AskInventory() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetRepInventory.restype = ctypes.c_char_p
        c_value = self.__GetRepInventory()
        return c_value.decode("UTF-8")

    def GetRepBroadcastText(self) -> bool:
        """ Wrapped Function : Get the reponse of AskBroadcastText() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetRepBroadcastText.restype = ctypes.c_bool
        c_value = self.__GetRepBroadcastText()
        return c_value

    def GetRepConnectNbr(self) -> bool:
        """ Wrapped Function : Get the reponse of AskConnectNbr() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetRepConnectNbr.restype = ctypes.c_bool
        c_value = self.__GetRepConnectNbr()
        return c_value

    def GetRepFork(self) -> bool:
        """ Wrapped Function : Get the reponse of AskFork() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetRepFork.restype = ctypes.c_bool
        c_value = self.__GetRepFork()
        return c_value

    def GetRepEject(self) -> bool:
        """ Wrapped Function : Get the reponse of AskEject() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetRepEject.restype = ctypes.c_bool
        c_value = self.__GetRepEject()
        return c_value

    def GetRepTakeObject(self) -> bool:
        """ Wrapped Function : Get the reponse of AskTakeObject() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetRepTakeObject.restype = ctypes.c_bool
        c_value = self.__GetRepTakeObject()
        return c_value

    def GetRepPlaceObject(self) -> bool:
        """ Wrapped Function : Get the reponse of AskPlaceObject() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetRepPlaceObject.restype = ctypes.c_bool
        c_value = self.__GetRepPlaceObject()
        return c_value

    def GetRepIncantation(self) -> int:
        """ Wrapped Function : Get the reponse of AskIncantation() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.GetNetworkState():
            safeExitError()
        self.__GetRepIncantation.restype = ctypes.c_int
        c_value = self.__GetRepIncantation()
        return c_value

    def GetNetworkState(self) -> bool:
        """ Wrapped Function : Get the Network State, return true is everything ok, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__GetNetworkState.restype = ctypes.c_bool
        c_value = self.__GetNetworkState()
        return c_value
