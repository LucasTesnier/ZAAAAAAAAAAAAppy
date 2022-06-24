from hmac import new
from queue import Queue

MAX_COMMAND = 10

class AIQueues:
    def __init__(self, queueSize : int = 10):
        """
        Constructor of the AI Queue Class
        Init two queues, one corresponding to the API queue, the second one to have an infinite stock of object
        The Queue's object will be function pointer
        When a "Ask..." function is send to the Api, please put the "Get..." corresponding in the Queue with addInAiQueue()
        """
        self.__serverQueue : Queue = Queue(queueSize)
        self.__aiQueue : Queue = Queue(-1)
        self.__movement : int = 0
        self.__nbCommand : int = 0

    def isServerQueueFull(self) -> bool:
        """ If the server Queue cannot accept any more object, return True """
        return self.__serverQueue.full()

    def isServerQueueEmpty(self) -> bool:
        """ If the server Queue hasn't any object, return True """
        return self.__serverQueue.empty()

    def isAiQueueEmpty(self) -> bool:
        """ If the server Queue hasn't any object, return True """
        return self.__aiQueue.empty()

    def addInAiQueue(self, newObj, transferToServerQueue : bool = False):
        """
        Add the newObj in the infinite Queue
        if transferToServerQueue is True, it will try to put directly in the server Queue (Use case : Begin of the AI)
        """
        if transferToServerQueue and not self.isServerQueueFull():
            self.__addInServerQueue(newObj)
        else:
            self.__aiQueue.put(newObj)
        self.incrNbCommand()

    def __popFromAiQueue(self):
        """ Return the front element of the infinite Queue """
        return self.__aiQueue.get()

    def __addInServerQueue(self, newObj) -> None:
        """
        Add the newObj in the server Queue
        BEWARE : Check if the server Queue isn't full before calling this function
        """
        self.__serverQueue.put(newObj)

    def __popFromServerQueue(self):
        """ Return the front element of the server Queue """
        return self.__serverQueue.get()

    def addInServerQueue(self) -> int:
        """
        Empty the infinite Queue until the server Queue is full
        Return the number of objects transfered
        """
        added : int = 0
        while not self.isAiQueueEmpty() and not self.isServerQueueFull():
            newObj = self.__popFromAiQueue()
            self.__addInServerQueue(newObj)
            added += 1
        return added

    def popFctPtr(self):
        """
        Empty the server Queue of one element
        Return the poped object
        """
        newObj = None
        if not self.isServerQueueEmpty():
            newObj = self.__popFromServerQueue()
        return newObj

    def incrMov(self) -> None:
        self.__movement += 1

    def decMov(self) -> None:
        self.__movement -= 1

    def isMovementLeft(self) -> bool:
        """
        Return True if there is movement(s) left to do
        """
        return self.__movement != 0

    def incrNbCommand(self) -> None:
        self.__nbCommand += 1

    def decrNbCommand(self) -> None:
        self.__nbCommand -= 1

    def getNbCommand(self) -> int:
        return self.__nbCommand