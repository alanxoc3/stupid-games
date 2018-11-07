/*
 HEADER FILE : COIN_H
 The coin gives the player a point! Basically, all this class needs
 to do is destroy itself when it touches a person.
*/

#include <allegro5/allegro.h>
#include "sprite.h"
#include "constants.h"

class Coin : public Sprite {
   public:
      Coin(ALLEGRO_BITMAP * image);

      virtual int type() const {return TYPE_COIN;};

      virtual void collide(const Sprite & s2);
   private:
      void create();
};
