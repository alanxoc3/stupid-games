/*
 CPP FILE : SPRITE_TEST
 Tester for the sprite class.
*/

#include <iostream>
#include "../sprite.h"

using namespace std;

int main(int argc, char ** argv) {
   Sprite testSprite, testSprite2;

   testSprite2.setX(5);
   testSprite2.setY(58);
   testSprite2.setW(12);
   testSprite2.setH(12);

   cout << "Sprite x: " << testSprite.getX() << endl;
   cout << "Sprite y: " << testSprite.getY() << endl;
   cout << "Sprite w: " << testSprite.getW() << endl;
   cout << "Sprite h: " << testSprite.getH() << endl;

   cout << "NEXT SPRITE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

   cout << "Sprite x: " << testSprite2.getX() << endl;
   cout << "Sprite y: " << testSprite2.getY() << endl;
   cout << "Sprite w: " << testSprite2.getW() << endl;
   cout << "Sprite h: " << testSprite2.getH() << endl;

   cout << "Colliding?: " << testSprite2.testCollision(testSprite);
   cout << endl;

   testSprite2.setX(-1);
   testSprite2.setY(-1);
   testSprite2.setW(2);
   testSprite2.setH(2);

   cout << "Sprite x: " << testSprite.getX() << endl;
   cout << "Sprite y: " << testSprite.getY() << endl;
   cout << "Sprite w: " << testSprite.getW() << endl;
   cout << "Sprite h: " << testSprite.getH() << endl;

   cout << "NEXT SPRITE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

   cout << "Sprite x: " << testSprite2.getX() << endl;
   cout << "Sprite y: " << testSprite2.getY() << endl;
   cout << "Sprite w: " << testSprite2.getW() << endl;
   cout << "Sprite h: " << testSprite2.getH() << endl;

   cout << "Colliding?: " << testSprite2.testCollision(testSprite);
   cout << endl;

   cout << "Have a nice day. this has been the spriteTester" << endl;
   
   return 0;
}
