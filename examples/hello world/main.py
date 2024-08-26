import pygame
import partsy
import random as rnd

def print_particle(p: partsy.Particle) -> None:
    if p is not None:
        print(f"particle position: {p.position}")
        print(f"particle scale: {p.scale}")
        print(f"particle velocity: {p.velocity}")
        print(f"particle acceleration: {p.acceleration}")
        print(f"particle rotational velocity: {p.rotational_velocity}")
        print(f"particle rotational acceleration {p.rotational_acceleration}")
        print("")

def main() -> None:

    partsy.init()

    last_node: partsy.ParticleNode = partsy.ParticleNode()
    for i in range(3):
        particle_setup = {
            "position": (rnd.randint(-100, 100), rnd.randint(-100, 100)),
            "scale": (rnd.random(), rnd.random()),
            "velocity": (rnd.randint(-100, 100)/10, rnd.randint(-100, 100)/10),
            "acceleration": ((rnd.randint(-100, 100)/100, rnd.randint(-100, 100)/100)),
            "rotational_velocity": rnd.random(),
            "rotational_acceleration": rnd.random()
        }
        node = partsy.ParticleNode(last_node=last_node)
        last_node.next_node = node

        last_node.particle = particle=partsy.Particle(**particle_setup)

        last_node = node

    current_node: partsy.ParticleNode = last_node
    for i in range(4):
        print_particle(current_node.particle)
        if current_node.last_node is not None:
            current_node = current_node.last_node








if __name__ == "__main__":
    pygame.init()
    main()
    pygame.quit()
