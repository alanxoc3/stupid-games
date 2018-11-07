// enemy.h
#ifndef _ENEMY_H
#define _ENEMY_H

#include "constants.h"
#include "image.h"
#include "rectangle.h"
#include "living.h"
#include "thingHandler.h"
#include "timer.h"

class Enemy : public Living {
	public:
		Enemy(ImageHandler * imgHnd = nullptr);

		virtual void updateHand();
		virtual const Rectangle & getHandRect1() const;
		virtual const Rectangle & getHandRect2() const;

		// Inherited from Thing.
		virtual int type() const { return ID_ENEMY; };

		virtual void normalMode();
		virtual void dataMode(ThingHandler * sss, unsigned index);
		virtual void update();
		virtual void setImageHandler(ImageHandler * ih);
		virtual bool interact(Rectangle * other);
		virtual void moveTowards(Thing * other);

	private:
		Rectangle rect1;
		Rectangle rect2;
		Image hand;
		Timer timer;
};

#endif // _ENEMY_H
