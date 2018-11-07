/*
 HEADER FILE : SPRITE_LIST_H
 Ah, yes, a compilation of sprites.
 I can't tell your what would be better than that.
*/

#ifndef _SPRITELIST_H
#define _SPRITELIST_H

#include "sprite.h"
#include <vector>

class SpriteList
{
   public:
      SpriteList();
      ~SpriteList();

      // Gotta Draw 'Em All
      // Seriously, this method draws all the Sprites.
      void draw();

      // This method moves all the sprites.
      void move();

      // This method tests the collision with all the sprites.
      void collision();

      // Powers everyone up.
      void powerUp();

      // This method will add a new sprite for you.
      void add(Sprite * newbie);

      // Returns how many "things" are in the sprite list.
      int size() const ;

      // Tells if the sprite is colliding with anything of a different type.
      bool isFreeType(const Sprite & test);

   private:
      std::vector<Sprite *> list;

      // This one deletes all the sprites. My private implementation!
      void deleteAll();
};

#endif
