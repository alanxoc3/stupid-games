from random import randint
from random import uniform
import math
import asteroid
import assets

class AsteroidGroup(object):
  """
  A class that manages all the asteroids.
  """

  def __init__(self):
    self.asteroids = []

  # Spawns an asteroid with random parameters.
  def spawnAsteroid(self):
    # Want a:
    #   random position,
    #   random direction towards the center-ish
    #   random speed
    #   random rotation angle

    # 0 = left side
    # 1 = top side
    # 2 = right side
    # 3 = bottom side
    side = randint(0,3)
    x,y = 0,0
    ang = 0

    # Some numbers to make the math look easier.
    lowbound = math.pi / 16
    upbound  = math.pi / 2 - math.pi / 16
    onebound = math.pi / 2

    if side == 0:
      x = -assets.SIZE[0]
      y = randint(0, assets.SCREEN_SIZE[1])

      if y < assets.HALF_SCREEN[1]:
        ang = uniform(lowbound, upbound)
      else:
        ang = uniform(-lowbound, -upbound)

    elif side == 1:
      x = randint(0, assets.SCREEN_SIZE[1])
      y = -assets.SIZE[1]

      if x < assets.HALF_SCREEN[1]:
        ang = uniform(lowbound, upbound)
      else:
        ang = uniform(onebound + lowbound, onebound + upbound)

    elif side == 2:
      x = assets.SIZE[0] + assets.SCREEN_SIZE[0]
      y = randint(0, assets.SCREEN_SIZE[1])

      if y < assets.HALF_SCREEN[1]:
        ang = uniform(onebound + lowbound, onebound + upbound)
      else:
        ang = uniform(-(onebound + lowbound), -(onebound + upbound))

    else:
      x = randint(0, assets.SCREEN_SIZE[1])
      y = assets.SIZE[1] + assets.SCREEN_SIZE[1]

      if x < assets.HALF_SCREEN[1]:
        ang = uniform(-lowbound, -upbound)
      else:
        ang = uniform(-(onebound + lowbound), -(onebound + upbound))

    spd = randint(1,8)
    rot = randint(-5,5)

    self.asteroids.append(asteroid.Asteroid( (x, y), spd, ang, rot))

  # Draws all the asteroids.
  def draw(self, surface):
    for ast in self.asteroids:
      ast.draw(surface)

  # Updates all the asteroids, and cleans them all.
  def update(self):
    for ast in self.asteroids:
      ast.update()

    self.clean()

  # Removes all the dead asteroids.
  def clean(self):
    garbageList = []
    for ast in self.asteroids:
      if ast.dead:
        garbageList.append(ast)

    for garbage in garbageList:
      self.asteroids.remove(garbage)
