import pygame as pg
import tools
import math
import assets
from random import randint

class Asteroid(object):
  """
  The Asteroid class
  """
  def __init__(self, startingPosition, speed, direction, rotationAngleSpeed): 
    self.hs = math.cos(direction) * speed
    self.vs = math.sin(direction) * speed

    if self.hs > 0 and self.hs < 1:
      self.hs = 1
    elif self.hs < 0 and self.hs > -1:
      self.hs = -1

    if self.vs > 0 and self.vs < 1:
      self.vs = 1
    elif self.vs < 0 and self.vs > -1:
      self.vs = -1

    self.hs = int(self.hs)
    self.vs = int(self.vs)

    self.genImage()
    self.genSize(startingPosition)

    self.explode = False
    self.rotAngle = 0
    self.rotSpeed = rotationAngleSpeed
    self.vapor = 255
    self.dead = False
    self.starting = True # For starting off the screen.

  def genImage(self):
    row = randint(0,3)
    col = randint(0,4)
    self.image = assets.FRAMES[row][col]

  def genSize(self, startingPosition):
    w = randint(assets.SIZE[0], int(assets.SIZE[0] * 1.5) )
    h = randint(assets.SIZE[1], int(assets.SIZE[1] * 1.5) )

    self.image = pg.transform.smoothscale( self.image, (w, h) )
    self.rect = self.image.get_rect(center=startingPosition)

  def updateAngle(self):
    if not self.explode:
      self.rotAngle += self.rotSpeed
    else:
      self.rotAngle += self.rotSpeed * 2

  def disappear(self):
    vapor_speed = 20
    if self.vapor > 0:
      self.vapor -= vapor_speed
    else:
      self.dead = True

  def mouseCollision(self):
    # True if the left button is pressed.
    point = pg.mouse.get_pos()

    # Check if mouse point collides with rectangle.
    if self.rect.collidepoint(point):
      self.explode = True
      assets.score += 1
      

  def boundsChecking(self):
    # The asteroid should be within the bounds of the screen unless starting out.
    if not self.rect.colliderect(assets.SCREEN_RECT):
      if not self.starting:
        self.dead = True
    else:
      self.starting = False

  def update(self):
    """
    Updates our player appropriately every frame.
    """
    if self.dead:
      return

    self.updateAngle()

    if not self.explode:
      self.boundsChecking()
      self.mouseCollision()
    else:
      self.disappear()

    self.rect.x += self.hs
    self.rect.y += self.vs

  def draw(self, surface):
    """
    Draws the player to the target surface.
    """
    if self.dead:
      return

    drawnImage, drawnRect = tools.rot_center(self.image, self.rect, self.rotAngle)
    tools.blit_alpha(surface, drawnImage, drawnRect.topleft, self.vapor)
