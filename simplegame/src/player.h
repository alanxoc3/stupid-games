/*
 HEADER FILE : PLAYER_H
 The player is user's character!
*/

#ifndef _PLAYER_H
#define _PLAYER_H

#include <allegro5/allegro.h>
#include "score.h"
#include "sprite.h"
#include "constants.h"

class Player : public Sprite
{
   public:
      Player(ALLEGRO_BITMAP * image, Score * score);

      virtual int type() const {return TYPE_PLAYER;};

      void input(const ALLEGRO_EVENT & ev);
      void move();
      void draw();
      void collide(const Sprite & s2);

   private:
      // Directions:
      // L UL U UR R DR D DL
      bool * curDir;
      int face;
      Score * score;

      void updateDirections();
};

#endif
