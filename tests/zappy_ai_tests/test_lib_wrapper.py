#!/usr/bin/python3
from ai_DLLib_wrapper import DLLibWrapper

def lib_test(lib_path : str) -> DLLibWrapper:
    """ Add the path to the lib in the LibWrapper Object """
    lib_object : DLLibWrapper = DLLibWrapper(lib_path)
    return lib_object

def test_unexisting_lib():
    Test1 : DLLibWrapper = lib_test("./unexisting_lib.so")
    try:
        Test1.openLibrary()
    except Exception as e:
        assert(e.args == ('./unexisting_lib.so: cannot open shared object file: No such file or directory', ))

def test_existing_lib():
    Test2 : DLLibWrapper = lib_test("./tests_lib/libzappy_ai_api.so")
    try:
        Test2.openLibrary()
    except:
        print("The second test for the Lib Wrapper has failed")
        exit()
    Test2.closeLibray()
    """ If the test arrives to this line, it's means it's successfull"""
    assert 0 == 0

def test_get_function_from_lib():
    Test3 : DLLibWrapper = lib_test("./tests_lib/libzappy_ai_api.so")
    try:
        Test3.openLibrary()
        ptr = Test3.getFunctionFromLibrary("c_interface_ask_join")
        Test3.closeLibray()
    except:
        print("The third test for the Lib Wrapper has failed")
        exit()
    assert(ptr != None)