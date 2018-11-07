import pygame as pg

def split_sheet(sheet, size, dims):
  """
  Divide a loaded sprite sheet into subsurfaces.
  
  The argument size is the width and height of each frame (w,h)
  columns and rows are the integer number of cells horizontally and
  vertically.
  """
  subsurfaces = []
  for y in range(dims[1]):
    row = []
    for x in range(dims[0]): 
      rect = pg.Rect((x*size[0], y*size[1]), size)
      row.append(sheet.subsurface(rect))
    subsurfaces.append(row)
  return subsurfaces


# This method taken from:
# http://www.pygame.org/wiki/RotateCenter
def rot_center(image, rect, angle):
  """rotate an image while keeping its center"""
  rot_image = pg.transform.rotate(image, angle)
  rot_rect = rot_image.get_rect(center=rect.center)
  return rot_image,rot_rect

# This method is taken from:
# http://www.nerdparadise.com/programming/pygameblitopacity
def blit_alpha(target, source, location, opacity):
  x = location[0]
  y = location[1]
  temp = pg.Surface((source.get_width(), source.get_height())).convert()
  temp.blit(target, (-x, -y))
  temp.blit(source, (0, 0))
  temp.set_alpha(opacity)        
  target.blit(temp, location)
