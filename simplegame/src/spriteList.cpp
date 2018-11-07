/*
 CPP FILE : SPRITE_LIST_CPP
 Ah, yes, a compilation of sprites.
 I can't tell your what would be better than that.
 There is some nice pointer magic going on here.
 Apparently, iterators for vectors are pointers.
 See the Header file for info on things.
*/

#include "spriteList.h"

SpriteList :: SpriteList() {

}

SpriteList :: ~SpriteList() {
   deleteAll();
}

void SpriteList :: deleteAll() {
   for (std::vector<Sprite *>::iterator it = list.begin(); it != list.end(); it++)
   {
      delete [] *it;
      *it = NULL;
   }

   list.clear();
}

void SpriteList :: draw() {
   for (std::vector<Sprite *>::iterator it = list.begin(); it != list.end(); it++)
      (*it)->draw();
}

void SpriteList :: move() {
   for (std::vector<Sprite *>::iterator it = list.begin(); it != list.end(); it++)
      (*it)->move();
}

void SpriteList :: collision() {
   for (std::vector<Sprite *>::iterator it = list.begin(); it != list.end(); it++)
      for (std::vector<Sprite *>::iterator it2 = list.begin(); it2 != list.end(); it2++)
      {
         if ((*it)->testCollision(**it2))
            (*it)->collide(**it2);
      }
}

void SpriteList :: add(Sprite * newbie) {
   list.push_back(newbie);
}

int SpriteList :: size() const {
   return list.size();
}

void SpriteList :: powerUp() {
   for (std::vector<Sprite *>::iterator it = list.begin(); it != list.end(); it++)
      (*it)->powerUp();
}

bool SpriteList :: isFreeType(const Sprite & test) {
   for (std::vector<Sprite *>::iterator it = list.begin(); it != list.end(); it++) {
      if (test.testCollision(**it)) {
         if ((**it).type() != test.type())
            return false;
      }
   }

   return true;
}
