#! /usr/bin/env python2

"""
A Relaxing Asteroids game.
-Written by: Alan Morgan and Cameron Fife.
"""

import os
import sys
import math
import itertools
import astgroup
import assets
import random

import pygame as pg

class App(object):
  """
  A class to manage our event, game loop, and overall program flow.
  """
  def __init__(self):
    """
    Get a reference to the display surface; set up required attributes;
    and create a Player instance.
    """
    self.screen = pg.display.get_surface()
    self.screen_rect = self.screen.get_rect()
    self.clock  = pg.time.Clock()
    self.fps = 30
    self.done = False
    # Starting Point, Speed, Trajectory Angle, Rotation Speed 
    self.astList = astgroup.AsteroidGroup()
    self.astList.spawnAsteroid()
    self.keys = pg.key.get_pressed() # All the keys currently held.
    self.prev = 0

  def event_loop(self):
    """
    Pass events on to the player.
    """
    for event in pg.event.get():
      if event.type == pg.QUIT or self.keys[pg.K_ESCAPE]:
        self.done = True
      if event.type == pg.MOUSEBUTTONUP:
        return True
    return False

  def display_fps(self):
    """
    Show the program's FPS in the window handle.
    """
    caption = "{} - FPS: {:.2f}".format(assets.CAPTION, self.clock.get_fps())
    pg.display.set_caption(caption)

  def update(self):
    """
    Update the player.
    The current time is passed for purposes of animation.
    """
    now = pg.time.get_ticks()
    waitTime = 400

    if now-self.prev > waitTime:
      self.astList.spawnAsteroid()
      self.prev = now

    self.astList.update()

  def render(self):
    """
    Perform all necessary drawing and update the screen.
    """
    self.screen.fill(assets.BACKGROUND_COLOR)
    assets.DISPLAYSURF.blit(assets.BG, (0, 0))
    textScore = assets.FONT.render(str(assets.score), 1, (255,255,255))
    assets.DISPLAYSURF.blit(textScore, (90, 100))
    self.astList.draw(self.screen)
    pg.display.update()

  def render_start_screen(self):
    """
    Perform all necessary drawing and update the screen.
    """
    self.screen.fill(assets.BACKGROUND_COLOR)
    assets.DISPLAYSURF.blit(assets.BG, (0, 0))
    assets.DISPLAYSURF.blit(assets.QUOTE1, (90, 100))
    assets.DISPLAYSURF.blit(assets.QUOTE2, (90, 130))
    assets.DISPLAYSURF.blit(assets.LABEL, (90, 400))
    pg.display.update()
    
  def main_loop(self):
    """
    Our main game loop; I bet you'd never have guessed.
    """
    startScreen = True
    SCORE = 0
    pg.mouse.set_cursor(*pg.cursors.broken_x)
    
    pg.mixer.Sound.play(assets.RELAX)
    pg.mixer.music.load('assets/seven.mp3')
    pg.mixer.music.play(1)

    while not self.done:
      tmp = self.event_loop()
      
      if not startScreen:
        self.update()
        
      # Render
      if startScreen:
        self.render_start_screen()
      else:
        self.render()

      if not startScreen and not pg.mixer.music.get_busy():
         playSong()

      if startScreen and not pg.mixer.get_busy():
        startScreen = not tmp

      self.clock.tick(self.fps)
      self.display_fps()

def playSong():
  myNum = random.randint(0, 3)
  pg.mixer.music.load(assets.SONGS[myNum])
  pg.mixer.music.play(assets.SONGSPLAYTIMES[myNum])
      
def main():
  """
  Prepare our environment, create a display, and start the program.
  """
  os.environ['SDL_VIDEO_CENTERED'] = '1'
  pg.init()
  pg.display.set_caption(assets.CAPTION)
  assets.load_assets()

  App().main_loop()
  pg.quit()
  sys.exit()

if __name__ == "__main__":
  main()
