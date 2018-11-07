/*
 CPP FILE : SPRITE_CPP
*/

#include "sprite.h"
#include <cassert>
#include "constants.h"

// CONSTRUCTOR
// Will set the vars to an initial value.
Sprite :: Sprite(ALLEGRO_BITMAP * image) {
   x = 0;
   y = 0;
   width = PIECE_WIDTH;
   height = PIECE_WIDTH;
   hspeed = 0;
   vspeed = 0;
   alive = true; // You start living. :)

   assert(image != NULL);
   setI(image);
}

// IS_ALIVE
// Will return if the sprite is alive.
bool Sprite :: isAlive () const {
   return alive;
}

// KILL
// Will let IS_ALIVE return false.
void Sprite :: kill() {
   alive = false;
}

// A couple useful getters: x, y, width, and height.
float Sprite :: getX() const {
   return x;
}

float Sprite :: getY() const {
   return y;
}

float Sprite :: getW() const {
   return width;
}

float Sprite :: getH() const {
   return height;
}

// Here are some useful setters: x, y, width, and height.
void Sprite :: setX(const float & x) {
   this->x = x;
}

void Sprite :: setY(const float & y) {
   this->y = y;
}

void Sprite :: setW(const float & w) {
   width = w;
}

void Sprite :: setH(const float & h) {
   height = h;
}

// TEST_COLLISION
// The local version of testing collision.
bool Sprite :: testCollision(const Sprite & s2) const {
   return Sprite::testCollision(*this, s2);
}

// TEST_COLLISION
// The static version of testing collision.
bool Sprite :: testCollision(
                         const Sprite & s1, const Sprite & s2)
{
   // If the two boxes intersect: that is the algorithm.
   if (s1.getX() < s2.getX() + s2.getW() &&
       s1.getX() + s1.getW() > s2.getX() &&
       s1.getY() < s2.getY() + s2.getH() &&
       s1.getY() + s1.getH() > s2.getY())
      return true;
   else
      return false;
   
}

ALLEGRO_BITMAP * Sprite :: getI() const {
   return image;
}

void Sprite :: setI(ALLEGRO_BITMAP * image) {
   this->image = image;
}

void Sprite :: draw() {
   al_draw_bitmap(image, x, y, 0);
}

//hspeed and vseed getters and setters
float Sprite :: getHS() const {
   return hspeed;
}

float Sprite :: getVS() const {
   return vspeed;
}

void Sprite :: setHS(float h) {
   hspeed = h;
}

void Sprite :: setVS(float v) {
   vspeed = v;
}

// The move method.
void Sprite :: move() {
   // Simply, move the person.
   setX(getX() + getHS());

   setY(getY() + getVS());
}

bool Sprite :: spriteInRoom(const Sprite & s1) {
   return (s1.getX() + s1.getW() <= ROOM_WIDTH  && s1.getX() >= 0 &&
       s1.getY() + s1.getH() <= ROOM_HEIGHT && s1.getY() >= 0);
}
