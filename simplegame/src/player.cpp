/*
 CPP FILE : PLAYER_CPP
 The player is user's character!
*/

#include "player.h"
#include "constants.h"

Player :: Player(ALLEGRO_BITMAP * image, Score * score) : Sprite(image) {
   curDir = new bool [4];
   for (int i = 0; i < 4; ++i)
      curDir[i] = 0;

   face = R;
   this->score = score;

   setX(ROOM_WIDTH /2-PIECE_WIDTH /2);
   setY(ROOM_HEIGHT/2-PIECE_HEIGHT/2);
}


void Player :: input(const ALLEGRO_EVENT & ev) {

   // Set the keys!
   if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      switch (ev.keyboard.keycode) {
         case ALLEGRO_KEY_LEFT:
            curDir[LL] = true;
            break;
         case ALLEGRO_KEY_UP:
            curDir[UU] = true;
            break;
         case ALLEGRO_KEY_RIGHT:
            curDir[RR] = true;
            break;
         case ALLEGRO_KEY_DOWN:
            curDir[DD] = true;
            break;
      }
   } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
      switch (ev.keyboard.keycode) {
         case ALLEGRO_KEY_LEFT:
            curDir[LL] = false;
            break;
         case ALLEGRO_KEY_UP:
            curDir[UU] = false;
            break;
         case ALLEGRO_KEY_RIGHT:
            curDir[RR] = false;
            break;
         case ALLEGRO_KEY_DOWN:
            curDir[DD] = false;
            break;
         case ALLEGRO_KEY_ESCAPE: // Kill myself on escape.
            kill();
            break;
      }
   }
}

void Player :: move() {
   // I must do this method in a timer loop.
   updateDirections();

   // Change the speed with a nifty, simple algorithm.
   // Equipped with a nifty algorithm.
   float hSP = curDir[LL] * PLAYER_SPEED * -1 + curDir[RR] * PLAYER_SPEED;
   float vSP = curDir[UU] * PLAYER_SPEED * -1 + curDir[DD] * PLAYER_SPEED;

   setHS(hSP);
   setVS(vSP);
   Sprite::move();

   // Get in bounds man!
   if (getX() < 0) setX(0);
   if (getX() + getW() > ROOM_WIDTH) setX(ROOM_WIDTH - getW());
   if (getY() < 0) setY(0);
   if (getY() + getH() > ROOM_HEIGHT) setY(ROOM_HEIGHT - getH());

   // The player should not be out of the room now, if using the move method.
   assert(spriteInRoom(*this));
}

void Player :: draw() {
   float w = al_get_bitmap_width(getI());
   float h = al_get_bitmap_height(getI());
   float dir = ALLEGRO_PI / 4 * face;

   // right = 0. Left = pi, down = pi/2
   al_draw_rotated_bitmap(getI(), w / 2.0, h / 2.0, getX() + w / 4.0, getY() + h / 4.0, dir, 0);
}

void Player :: collide(const Sprite & s2) {
   // change this for badots.
   if (s2.type() == TYPE_COIN)
      score->add();
   else if (s2.type() == TYPE_ENEMY)
      kill();
}

void Player :: updateDirections() {
   // L UL U UR R DR D DL
   // l u r d 0 1 2 3
   if      (curDir[LL] && curDir[UU])
      face = UL;
   else if (curDir[LL] && curDir[DD])
      face = DL; 
   else if (curDir[RR] && curDir[UU])
      face = UR; 
   else if (curDir[RR] && curDir[DD])
      face = DR; 
   else if (curDir[UU])
      face = U; 
   else if (curDir[RR])
      face = R; 
   else if (curDir[DD])
      face = D; 
   else if (curDir[LL])
      face = L; 
   // Otherwise, face should equal face. 
}
