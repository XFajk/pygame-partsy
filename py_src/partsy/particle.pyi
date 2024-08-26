from collections.abc import Sequence
from typing import Any

from pygame import Vector2

class Particle:

    position: Any
    scale: Any
    velocity: Any
    acceleration: Any
    rotational_velocity: float
    rotational_acceleration: float
    delete: bool

    def __init__(self, position: Sequence[float] | Vector2,
                scale: Sequence[float] | Vector2 | None = (1, 1),
                velocity: Sequence[float] | Vector2 | None = (0, 0),
                acceleration: Sequence[float] | Vector2 | None = (0, 0),
                rotational_velocity: float | None = 0.0,
                rotational_acceleration: float | None = 0.0) -> None:
