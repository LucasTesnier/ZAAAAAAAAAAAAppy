#!/usr/bin/python3
import sys

sys.path.append('../')

from ai_function_wrapper import ServerWrapper

def server_wrapper_test(lib_path : str) -> ServerWrapper:
    """ Add the path to the lib in the ServerWrapper Object """
    server_wrapper_object : ServerWrapper = ServerWrapper(lib_path)
    return server_wrapper_object

def test_default():
    """ Main Function """
    Test1 : ServerWrapper = server_wrapper_test("./TestLib.so")
    assert(Test1.getNecessaryFunctions() == False)

def test_unexisting():
    Test2 : ServerWrapper = server_wrapper_test("./unexisting_lib.so")
    assert(Test2.getNecessaryFunctions() == False)

def test_valid():
    Test3 : ServerWrapper = server_wrapper_test("./../libzappy_ai_api.so")
    assert(Test3.getNecessaryFunctions() == True)
