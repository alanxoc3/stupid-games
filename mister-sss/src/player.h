// player.h

#ifndef _PLAYER_H
#define _PLAYER_H

#include "input.h"
#include "constants.h"
#include "living.h"
#include "grid.h"
#include "enemy.h"
#include "thingHandler.h"

/********************************************************************
 * Player
 * 	The player is the main character of the game. This class is
 * 	in charge of the player and many of the player's capabilities
 * 	including attacking, moving, and health.
 ********************************************************************/
class Player : public Living {
	public:
		Player();

		void input(const Input & in);
		virtual int type() const { return ID_PLAYER; };

		virtual void updateHand(const Grid & grid);
		virtual inline const Rectangle & getHandRect1() const { return rect1; };
		virtual inline const Rectangle & getHandRect2() const { return rect2; };

		virtual void normalMode();
		virtual void dataMode(ThingHandler * sss, unsigned index);

		virtual void setImageHandler(ImageHandler * ih);

		virtual bool interact(Rectangle * other);

	private:
		bool xHeld, yHeld;
		Rectangle rect1, rect2;
		Image hand;

		void updateHandTemplate(const Grid & grid, Rectangle & rect, float gap, float speed);
		void figureOutHandImage();
		void figureOutHandImage(const unsigned & xpos, const unsigned & ypos);

		
};

#endif //_PLAYER_H
