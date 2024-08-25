from typing import Optional, Any, Sequence
from pygame import Vector2

class Particle:

    position: Any
    scale: Any
    velocity: Any
    acceleration: Any
    rotationalVelocity: float
    rotationalAcceleration: float

    def __init__(self, position: Sequence[float] | Vector2,
                scale: Optional[Sequence[float] | Vector2] = (1, 1),
                velocity: Optional[Sequence[float] | Vector2] = (0, 0),
                acceleration: Optional[Sequence[float] | Vector2] = (0, 0),
                rotationalVelocity: Optional[float] = 0.0,
                rotationalAcceleration: Optional[float] = 0.0) -> None:
