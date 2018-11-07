/*
 HEADER FILE : GAME_PLAYER_H
 Plays the game, not start menu.
*/

#ifndef _GAME_PLAYER_H
#define _GAME_PLAYER_H

#include <vector>

class GamePlayer
{
   public:
      GamePlayer(Score * s);

      void loop();
      bool isGameOver();
      
   private:
      Player ghostMan;
      Score * gameScore;

      void input();
      void draw();
      void move();
      void collision();
};

#endif
