/*
 CPP FILE : COIN_CPP
 The coin gives the player a point! Basically, all this class needs
 to do is destroy itself when it touches a person.
*/

#include "coin.h"
#include <cstdlib>

Coin :: Coin(ALLEGRO_BITMAP * image) : Sprite(image) {
   create();
}

void Coin :: create() {
   int xMax = ROOM_WIDTH  - PIECE_WIDTH;
   int yMax = ROOM_HEIGHT - PIECE_HEIGHT;

   setX(std :: rand() % xMax);
   setY(std :: rand() % yMax);
   assert(Sprite::spriteInRoom(*this));
}

// Only will react to touching a player.
void Coin :: collide(const Sprite & s2) {
   // If the coin collides with the player, then the coin must recreate.
   if (s2.type() == TYPE_PLAYER)
      create();
}
