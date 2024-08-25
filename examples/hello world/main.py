import pygame
import partsy
import sys

def foo(l):
    print(sys.getrefcount(l))

def main() -> None:

    partsy.init()

    vec = pygame.Vector2()

    particle = partsy.Particle(pygame.Vector2(200, 100), scale=[0.5, 0.5], velocity=pygame.Vector2(200, 100), acceleration=(0, 9.8))
    particle.velocity = [0, 10]
    particle.scale[1] += 0.1
    particle.position = particle.position.normalize()
    print(f"particle position: {particle.position}")
    print(f"particle scale: {particle.scale}")
    print(f"particle velocity: {particle.velocity}")
    print(f"particle.acceleration: {particle.acceleration}")


if __name__ == "__main__":
    pygame.init()
    main()
    pygame.quit()
