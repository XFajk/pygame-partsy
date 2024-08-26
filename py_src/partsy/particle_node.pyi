
from particle import Particle

class ParticleNode:

    particle: Particle
    next_node: ParticleNode
    last_node: ParticleNode

    def __init__(self, particle: Particle | None = None,
                next_node: ParticleNode | None = None,
                last_node: ParticleNode | None = None) -> None:
