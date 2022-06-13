import ctypes
import os
from _ctypes import dlopen
from _ctypes import dlsym
from _ctypes import dlclose

"""
The libToto
void toto() { printf("TOTO\n"); }
void add(int a) { return a + 1;}
"""

class DLLibWrapper:
    def __init__(self, libraryPath : str = "./libToto.so") -> None:
        """ Constructor of the DLLibWrapper Class """
        self.library : str = libraryPath
        self.libInfo = None


    def openLibrary(self) -> None:
        """ Open the library provided in the constructor """
        self.libInfo = dlopen(self.library, os.RTLD_NOW)
        if not self.libInfo:
            raise Exception('The lib ' + self.library + ' can not be opened')


    def closeLibray(self) -> None:
        """
        Close the library provided in the constructor
        BEWARE : You must call openLibrary() or it can lead to undefined behaviour
        """
        dlclose(self.libInfo)


    def getFunctionFromLibrary(self, fctName : str):
        """
        Get a function by its name from the previously opened library
        BEWARE : You must call openLibrary() or it can lead to undefined behaviour
        Return the asked function pointer
        """
        fctType = ctypes.CFUNCTYPE(ctypes.c_int)
        fctPtr = dlsym(self.libInfo, fctName)

        return fctType(fctPtr)