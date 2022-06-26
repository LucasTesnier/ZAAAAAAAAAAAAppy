
from dataclasses import dataclass

@dataclass
class BroadcastInfo:
    """ Dataclass for the Broadcast info """
    action: str
    teamName: str
    pos: int
    requiredLevel: int
    nbPlayers: int
    resource: str
