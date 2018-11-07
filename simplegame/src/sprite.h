/*
 HEADER FILE : SPRITE_H
 A sprite is a movable object.
*/

#ifndef _SPRITE_H
#define _SPRITE_H

#include "constants.h"
#include <allegro5/allegro.h>

class Sprite
{
   public:
      Sprite(ALLEGRO_BITMAP * image);

      virtual int type() const {return TYPE_SPRITE;};
      virtual void move();
      virtual void draw();
      virtual void collide(const Sprite & s2) {}

      bool isAlive() const;
      void kill();

      float getX() const;
      float getY() const;
      float getW() const;
      float getH() const;
      void setX(const float & x);
      void setY(const float & y);
      void setW(const float & w);
      void setH(const float & h);
      bool testCollision(const Sprite & s2) const;

      float getHS() const;
      float getVS() const;
      void setHS(float h);
      void setVS(float v);

      // This method is mainly for the enemy sprites, but may be changed
      // to fit various other types of sprites.
      virtual void powerUp() {};

      // Image getter/setter
      ALLEGRO_BITMAP * getI() const;
      void setI(ALLEGRO_BITMAP * image);

      static bool testCollision(const Sprite & s1, const Sprite & s2);
      static bool spriteInRoom(const Sprite & s1);

   private:
      float hspeed;
      float vspeed;
      float width, height;
      float x, y;
      ALLEGRO_BITMAP * image;

      bool alive;
};

#endif
