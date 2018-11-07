/*
 CPP FILE : ENEMY_CPP
 This is the enemy, AKA BADOT.
 He is a very bad, bad dot.
*/

#include "enemy.h"
#include <cstdlib>
#include <cassert>

Enemy :: Enemy (ALLEGRO_BITMAP * image, SpriteList & list) : Sprite(image) {
   create(list);
}

void Enemy :: move() {
   Sprite::move();

   if (horizontal) {
      if (getX() < 0) {
         setX(0);
         setHS(-getHS());
      } else if (getX() + getW() > ROOM_WIDTH) {
         setX(ROOM_WIDTH - getW());
         setHS(-getHS());
      }
   } else {
      if (getY() < 0) {
         setY(0);
         setVS(-getVS());
      } else if (getY() + getH() > ROOM_HEIGHT) {
         setY(ROOM_HEIGHT - getH());
         setVS(-getVS());
      }
   }

}

void Enemy :: create(SpriteList & list) {
   horizontal = bool (std::rand() % 2);
   setHS(0);
   setVS(0);

   do {
      setX(rand() % (ROOM_WIDTH  - PIECE_WIDTH));
      setY(rand() % (ROOM_HEIGHT - PIECE_HEIGHT));
   } while (!list.isFreeType(*this));

   assert(spriteInRoom(*this));
}

void Enemy :: powerUp() {
   // If the speed is zero, then have a random value as it instead.
   if (horizontal) {
      if (getHS() == 0)
         setHS(rand() % 2 == 1 ? -1 : 1);
      else {
         setHS(getHS() + (getHS() > 0 ? 1 : -1));
         assert(getVS() == 0);
      }
   }
   else {
      if (getVS() == 0)
         setVS(rand() % 2 == 1 ? -1 : 1);
      else {
         setVS(getVS() + (getVS() > 0 ? 1 : -1));
         assert(getHS() == 0);
      }
   }
}
