from ai_DLLib_wrapper import DLLibWrapper
import ctypes
from sys import stderr
from ai_safe_error import safeExitError

class ServerWrapper:
    def __init__(self, libName : str):
        """ Constructor of the ServerWrapper class """
        self.DLLibWrapper : DLLibWrapper = DLLibWrapper(libName)

        """ Private members functions pointer """
        self.__connectToServer = None
        self.__getRepConnectToServer = None
        self.__askJoinTeam = None
        self.__getRepJoinTeam = None
        self.__getResponseState = None
        self.__getUnexpectedResponseState = None
        self.__getUnexpectedResponse = None
        self.__getNetworkState = None
        self.__flushData = None

        """ Ask an action for the AI to the server """
        self.__askForward = None
        self.__askTurnRight = None
        self.__askTurnLeft = None
        self.__askLook = None
        self.__askInventory = None
        self.__askBroadcastText = None
        self.__askConnectNbr = None
        self.__askFork = None
        self.__askEject = None
        self.__askTakeObject = None
        self.__askPlaceObject = None
        self.__askIncantation = None

        """ Get the result of the ask function from the server """
        self.__getRepForward = None
        self.__getRepTurnRight = None
        self.__getRepTurnLeft = None
        self.__getRepLook = None
        self.__getRepInventory = None
        self.__getRepBroadcastText = None
        self.__getRepConnectNbr = None
        self.__getRepFork = None
        self.__getRepEject = None
        self.__getRepTakeObject = None
        self.__getRepPlaceObject = None
        self.__getRepIncantation = None

    def getNecessaryFunctions(self) -> bool:
        """
        Open the libray
        Get all the functions from the library to have a working AI
        Close the library
        Return True if all the functions exist, false otherwise
        """
        try:
            self.DLLibWrapper.openLibrary()
            self.__connectToServer = self.DLLibWrapper.getFunctionFromLibrary("c_interface_try_to_connect_to_server")
            self.__getRepConnectToServer = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_connect_to_server_response")
            self.__askJoinTeam = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_join")
            self.__getRepJoinTeam = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_join_response")
            self.__getResponseState = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_response_state")
            self.__getUnexpectedResponseState = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_unexpected_response_state")
            self.__getUnexpectedResponse = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_unexpected_response")
            self.__askForward = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_forward")
            self.__askTurnRight = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_right")
            self.__askTurnLeft = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_left")
            self.__askLook = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_look")
            self.__askInventory = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_inventory")
            self.__askBroadcastText = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_broadcast")
            self.__askConnectNbr = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_connectable")
            self.__askFork = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_fork")
            self.__askEject = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_eject")
            self.__askTakeObject = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_take")
            self.__askPlaceObject = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_place")
            self.__askIncantation = self.DLLibWrapper.getFunctionFromLibrary("c_interface_ask_incantation")
            self.__getRepForward = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_forward_response")
            self.__getRepTurnRight = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_right_response")
            self.__getRepTurnLeft = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_left_response")
            self.__getRepLook = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_look_response")
            self.__getRepInventory = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_inventory_response")
            self.__getRepBroadcastText = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_broadcast_response")
            self.__getRepConnectNbr = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_connectable_response")
            self.__getRepFork = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_fork_response")
            self.__getRepEject = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_eject_response")
            self.__getRepTakeObject = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_take_response")
            self.__getRepPlaceObject = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_place_response")
            self.__getRepIncantation = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_incantation_response")
            self.__getNetworkState = self.DLLibWrapper.getFunctionFromLibrary("c_interface_get_network_state")
            self.__flushData = self.DLLibWrapper.getFunctionFromLibrary("c_interface_flush_asked_data")
        except Exception as ex:
            print(ex, file=stderr)
            return False
        return True

    def __flush(self) -> None:
        """ Wrapped Function : Flush the Api's command to the server """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__flushData.restype = ctypes.c_bool
        while not self.__flushData():
            continue

    def connectToServer(self, machineName : str, port : int):
        """ Wrapped Function : Try to connect the AI to the server
            Return True if a server has been found
            Return False otherwise
        """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        b_machineName = machineName.encode("UTF-8")
        c_port = ctypes.c_int(port)
        self.__connectToServer.restype = ctypes.c_bool
        c_value = self.__connectToServer(b_machineName, c_port)
        if c_value:
            self.__flush()
        return c_value

    def getRepConnectToServer(self) -> bool:
        """ Wrapped Function : Get the response of ConnectToServer() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getRepConnectToServer.restype = ctypes.c_bool
        c_value = self.__getRepConnectToServer()
        return c_value

    def askJoinTeam(self, teamName : str) -> bool:
        """ Wrapped Function : Try to join a Team """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        b_teamName = teamName.encode("UTF-8")
        self.__askJoinTeam.restype = ctypes.c_bool
        c_value = self.__askJoinTeam(ctypes.c_char_p(b_teamName))
        if c_value:
            self.__flush()
        return c_value

    def getRepJoinTeam(self) -> str:
        """ Wrapped Function : Get the response about joining a team """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getRepJoinTeam.restype = ctypes.c_char_p
        c_value = self.__getRepJoinTeam()
        if c_value == None:
            return None
        return c_value.decode("UTF-8")

    def getResponseState(self) -> bool:
        """ Wrapped Function : Return true if a response is available, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getResponseState.restype = ctypes.c_bool
        c_value = self.__getResponseState()
        return c_value

    def getUnexpectedResponseState(self) -> bool:
        """ Wrapped Function : Return true if a response is available, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getUnexpectedResponseState.restype = ctypes.c_bool
        c_value = self.__getUnexpectedResponseState()
        return c_value

    def getUnexpectedResponse(self) -> str:
        """ Wrapped Function : Return the unexpected message """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getUnexpectedResponse.restype = ctypes.c_char_p
        c_value = self.__getUnexpectedResponse()
        return c_value.decode("UTF-8")

    def askForward(self) -> bool:
        """ Wrapped Function : Move the client forward """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__askForward.restype = ctypes.c_bool
        c_value = self.__askForward()
        if c_value:
            self.__flush()
        return c_value

    def askTurnRight(self) -> bool:
        """ Wrapped Function : Turn the client to the right """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__askTurnRight.restype = ctypes.c_bool
        c_value = self.__askTurnRight()
        if c_value:
            self.__flush()
        return c_value

    def askTurnLeft(self) -> bool:
        """ Wrapped Function : Turn the client to the left """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__askTurnLeft.restype = ctypes.c_bool
        c_value = self.__askTurnLeft()
        if c_value:
            self.__flush()
        return c_value

    def askLook(self) -> bool:
        """ Wrapped Function : Look around the client """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__askLook.restype = ctypes.c_bool
        c_value = self.__askLook()
        if c_value:
            self.__flush()
        return c_value

    def askInventory(self) -> bool:
        """ Wrapped Function : Ask for the client inventory """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__askInventory.restype = ctypes.c_bool
        c_value = self.__askInventory()
        if c_value:
            self.__flush()
        return c_value

    def askBroadcastText(self, message : str) -> bool:
        """ Wrapped Function : Broadcast a text """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        b_message = message.encode("UTF-8")
        self.__askBroadcastText.restype = ctypes.c_bool
        c_value = self.__askBroadcastText(ctypes.c_char_p(b_message))
        if c_value:
            self.__flush()
        return c_value

    def askConnectNbr(self) -> bool:
        """ Wrapped Function : Ask for the place left on the client's team """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__askConnectNbr.restype = ctypes.c_bool
        c_value = self.__askConnectNbr()
        if c_value:
            self.__flush()
        return c_value

    def askFork(self) -> bool:
        """ Wrapped Function : Fork the client to lay an egg """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__askFork.restype = ctypes.c_bool
        c_value = self.__askFork()
        if c_value:
            self.__flush()
        return c_value

    def askEject(self) -> bool:
        """ Wrapped Function : Eject the other clients of the client's tile """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__askEject.restype = ctypes.c_bool
        c_value = self.__askEject()
        if c_value:
            self.__flush()
        return c_value

    def askTakeObject(self, object : str) -> bool:
        """ Wrapped Function : Take an object on the client tile """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        b_object = object.encode("UTF-8")
        self.__askTakeObject.restype = ctypes.c_bool
        c_value = self.__askTakeObject(ctypes.c_char_p(b_object))
        if c_value:
            self.__flush()
        return c_value

    def askPlaceObject(self, object : str) -> bool:
        """ Wrapped Function : Place an object on the client tile """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        b_object = object.encode("UTF-8")
        self.__askPlaceObject.restype = ctypes.c_bool
        c_value = self.__askPlaceObject(ctypes.c_char_p(b_object))
        if c_value:
            self.__flush()
        return c_value

    def askIncantation(self) -> bool:
        """ Wrapped Function : Start an incantation on the client tile """
        """ Return true if the command has been send, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__askIncantation.restype = ctypes.c_bool
        c_value = self.__askIncantation()
        if c_value:
            self.__flush()
        return c_value

    def getRepForward(self) -> bool:
        """ Wrapped Function : Get the reponse of AskForward() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getRepForward.restype = ctypes.c_bool
        c_value = self.__getRepForward()
        return c_value

    def getRepTurnRight(self) -> bool:
        """ Wrapped Function : Get the reponse of AskTurnRight() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getRepTurnRight.restype = ctypes.c_bool
        c_value = self.__getRepTurnRight()
        return c_value

    def getRepTurnLeft(self) -> bool:
        """ Wrapped Function : Get the reponse of AskTurnLeft() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getRepTurnLeft.restype = ctypes.c_bool
        c_value = self.__getRepTurnLeft()
        return c_value

    def getRepLook(self) -> str:
        """ Wrapped Function : Get the reponse of AskLook() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getRepLook.restype = ctypes.c_char_p
        c_value = self.__getRepLook()
        return c_value.decode("UTF-8")

    def getRepInventory(self) -> str:
        """ Wrapped Function : Get the reponse of AskInventory() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getRepInventory.restype = ctypes.c_char_p
        c_value = self.__getRepInventory()
        return c_value.decode("UTF-8")

    def getRepBroadcastText(self) -> bool:
        """ Wrapped Function : Get the reponse of AskBroadcastText() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getRepBroadcastText.restype = ctypes.c_bool
        c_value = self.__getRepBroadcastText()
        return c_value

    def getRepConnectNbr(self) -> bool:
        """ Wrapped Function : Get the reponse of AskConnectNbr() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getRepConnectNbr.restype = ctypes.c_bool
        c_value = self.__getRepConnectNbr()
        return c_value

    def getRepFork(self) -> bool:
        """ Wrapped Function : Get the reponse of AskFork() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getRepFork.restype = ctypes.c_bool
        c_value = self.__getRepFork()
        return c_value

    def getRepEject(self) -> bool:
        """ Wrapped Function : Get the reponse of AskEject() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getRepEject.restype = ctypes.c_bool
        c_value = self.__getRepEject()
        return c_value

    def getRepTakeObject(self) -> bool:
        """ Wrapped Function : Get the reponse of AskTakeObject() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getRepTakeObject.restype = ctypes.c_bool
        c_value = self.__getRepTakeObject()
        return c_value

    def getRepPlaceObject(self) -> bool:
        """ Wrapped Function : Get the reponse of AskPlaceObject() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getRepPlaceObject.restype = ctypes.c_bool
        c_value = self.__getRepPlaceObject()
        return c_value

    def getRepIncantation(self) -> int:
        """ Wrapped Function : Get the reponse of AskIncantation() """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        if not self.getNetworkState():
            safeExitError()
        self.__getRepIncantation.restype = ctypes.c_int
        c_value = self.__getRepIncantation()
        return c_value

    def getNetworkState(self) -> bool:
        """ Wrapped Function : Get the Network State, return true is everything ok, false otherwise """
        """ BEWARE : Any use of this function before calling getNecessaryFunctions() will need to undefined behaviour """
        self.__getNetworkState.restype = ctypes.c_bool
        c_value = self.__getNetworkState()
        return c_value
