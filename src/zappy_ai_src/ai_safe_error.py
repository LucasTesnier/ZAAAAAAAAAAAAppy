from sys import stderr

def safeExitError(exitCode : int = 84, message : str = "Connection to server lost"):
    print(message, file=stderr)
    exit(exitCode)