/*
 HEADER FILE : ENEMY_H 
 This is the enemy, AKA BADOT.
 He is a very bad, bad dot.
*/

#ifndef _ENEMY_H
#define _ENEMY_H

#include <allegro5/allegro.h>
#include "sprite.h"
#include "constants.h"
#include "spriteList.h"

class Enemy : public Sprite
{
   public:
      Enemy (ALLEGRO_BITMAP * image, SpriteList & list);

      virtual int type() const {return TYPE_ENEMY;};

      // This move method must have bouncing capabilities.
      virtual void move();
      virtual void powerUp();

   private:
      bool horizontal;

      void create(SpriteList & list);
};

#endif
