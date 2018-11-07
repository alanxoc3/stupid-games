/*
 HEADER FILE : SCORE_H
 The player's score.
*/

#ifndef _SCORE_H
#define _SCORE_H

#include <allegro5/allegro_font.h>

class Score
{
   public:
      Score(ALLEGRO_FONT * font);

      void add();
      void draw();
      int getScore();
      bool save(); // Return false if it failed.
      void reset();
      void showHighScore();
      void hideHighScore();
      int getHighScore();

   private:
      int scoreNum;
      int highScore;
      bool displayHighScore;
      ALLEGRO_FONT * font;
};

#endif
