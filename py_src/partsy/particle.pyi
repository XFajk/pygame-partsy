from typing import Optional, Tuple, List
from pygame import Vector2

class Particle:
    position: Tuple[float, float] | List[float] | Vector2
    scale: Tuple[float, float] | List[float] | Vector2
    velocity:   Tuple[float, float] | List[float] | Vector2
    acceleration: Tuple[float, float] | List[float] | Vector2
    rotationalVelocity: float
    rotationalAcceleration: float

    def __init__(self, position: Tuple[float, float] | List[float] | Vector2,
                scale: Optional[Tuple[float, float] | List[float] | Vector2] = (1, 1),
                velocity: Optional[Tuple[float, float] | List[float] | Vector2] = (0, 0),
                acceleration: Optional[Tuple[float, float] | List[float] | Vector2] = (0, 0),
                rotationalVelocity: Optional[float] = 0.0,
                rotationalAcceleration: Optional[float] = 0.0) -> None:
