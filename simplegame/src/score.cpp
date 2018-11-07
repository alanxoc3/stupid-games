/*
 CPP FILE : SCORE_CPP
 The player's score.
*/

#include <iostream>
#include "score.h"
#include <string>
#include <sstream>
#include <fstream>
#include "constants.h"

Score :: Score(ALLEGRO_FONT * font) {
   this->font = font;
   displayHighScore = false;
   highScore = 0;
   reset();
   save();
}


void Score :: reset() {
   scoreNum = 0;
}

void Score :: draw() {
   // Display width divided by two.
   // Uggh, code is looking a little ugly.
   // char * tmpStr = std::to_string(getScore()).c_str();
   std::stringstream ss;
   ss << getScore();
   const char * tmpStr = ss.str().c_str();
   al_draw_text(font, al_map_rgb(0,0,0), 0, 0, 0, tmpStr);

   if (displayHighScore) {
      std::stringstream sd;
      sd << "highscore:" << highScore;
      const char * highStr = sd.str().c_str();

      al_draw_text(font, al_map_rgb(200, 30, 30), 0, ROOM_HEIGHT - FONT_SIZE, 0, highStr);
   }
}

int Score :: getScore() {
   return scoreNum;
}

void Score :: add() {
   scoreNum += 1;
}

// saveScore
// returns false if it could not save.
bool Score :: save() {
   std::string line;
   std::ifstream saveFile(FNAME_SCORE);
   int tmpScore = 0;

   if (saveFile.is_open())
   {
      getline (saveFile, line);
      saveFile.close();
   }

   // Numeric base of ten.
   
   std::istringstream ss(line);
   ss >> tmpScore;

   if (getScore() > tmpScore)
   {
      std::ofstream fin (FNAME_SCORE);
      if (fin.is_open())
      {
         fin << getScore();
         fin.close();
      }

      highScore = getScore();
   } else {
      highScore = tmpScore;
   }
}

void Score :: showHighScore() {
   displayHighScore = true;
}

void Score :: hideHighScore() {
   displayHighScore = false;
}

int Score :: getHighScore() {
   return highScore;
}
