// enemy.cpp

#include "player.h"
#include "enemy.h"

Enemy :: Enemy(ImageHandler * imgHnd) : Living() {
	     setXYWH(DEF_X, DEF_Y, ENEMY_DIM     , ENEMY_DIM);
	rect1.setXYWH(DEF_X, DEF_Y, ENEMY_HAND_DIM, ENEMY_HAND_DIM);
	rect2.setXYWH(DEF_X, DEF_Y, ENEMY_HAND_DIM, ENEMY_HAND_DIM);
	setImageHandler(imgHnd);
	setMaxHP(ENEMY_MAXHP);
	setMaxSpeed(ENEMY_MAXSPEED);
	heal();
	timer.reset();
	setZ(Z_ENEMY);
	hand.setZ(Z_ENEMY);
}

/********************************************************************
 * normalMode()
 * 	Set to Normal Mode. Sets the parents as well.
 ********************************************************************/
void Enemy :: normalMode() {
	Living :: normalMode();
	//rect1.normalMode();
	//rect2.normalMode();
	hand.normalMode();
}

/********************************************************************
 * dataMode()
 * 	Set to data mode. Sets the parents as well. Adds a thing to
 * 	the thing handler, for the hand...
 ********************************************************************/
void Enemy :: dataMode(ThingHandler * sss, unsigned index) {
	Living :: dataMode(sss, index);
	rect1.dataMode(sss, sss->addThing());
	rect2.dataMode(sss, sss->addThing());
	hand.dataMode(sss, sss->addThing());
}

/********************************************************************
 * updateHand()
 * 	Inherited from Living. Updates the position/stuff relating to
 * 	the Hand.
 ********************************************************************/
void Enemy :: updateHand() {
	uint32_t stop = timer.getTicks();
	unsigned base = 0;
	unsigned colMax = 12;
	// Twelve frames a second.
	unsigned subIm = (stop % 1000) * colMax / 1000;
	
	hand.setIX(getX() + getIX() + getHS());
	hand.setIY(getY() + getIY() + getVS());

	// Figure out collision boxes.
	if (getFacing() == FACE_DOWN) {
		base = 2 * 16;
		switch (subIm) {
			case 0: case 6:
				rect1.setX(getX() + getIX() + getHS() + 42); rect2.setX(getX() + getIX() + getHS() + 19);
				rect1.setY(getY() + getIY() + getVS() + 22); rect2.setY(getY() + getIY() + getVS() + 22);
			break; case 1: case 5:
				rect1.setX(getX() + getIX() + getHS() + 41); rect2.setX(getX() + getIX() + getHS() + 17);
				rect1.setY(getY() + getIY() + getVS() + 19); rect2.setY(getY() + getIY() + getVS() + 25);
			break; case 2: case 3: case 4:
				rect1.setX(getX() + getIX() + getHS() + 41); rect2.setX(getX() + getIX() + getHS() + 17);
				rect1.setY(getY() + getIY() + getVS() + 9 ); rect2.setY(getY() + getIY() + getVS() + 30);
			break; case 7: case 11:
				rect1.setX(getX() + getIX() + getHS() + 44); rect2.setX(getX() + getIX() + getHS() + 20);
				rect1.setY(getY() + getIY() + getVS() + 25); rect2.setY(getY() + getIY() + getVS() + 19);
			break; case 8: case 9: case 10:
				rect1.setX(getX() + getIX() + getHS() + 44); rect2.setX(getX() + getIX() + getHS() + 20);
				rect1.setY(getY() + getIY() + getVS() + 30); rect2.setY(getY() + getIY() + getVS() + 9 );
		}
	} else if (getFacing() == FACE_LEFT) {
		base = 3 * 16;
		switch (subIm) {
			case 0: case 6:
				rect1.setX(getX() + getIX() + getHS() + 22); rect2.setX(getX() + getIX() + getHS() + 22);
				rect1.setY(getY() + getIY() + getVS() + 19); rect2.setY(getY() + getIY() + getVS() + 42);
			break; case 1: case 5:
				rect1.setX(getX() + getIX() + getHS() + 19); rect2.setX(getX() + getIX() + getHS() + 25);
				rect1.setY(getY() + getIY() + getVS() + 20); rect2.setY(getY() + getIY() + getVS() + 44);
			break; case 2: case 3: case 4:
				rect1.setX(getX() + getIX() + getHS() + 9 ); rect2.setX(getX() + getIX() + getHS() + 30);
				rect1.setY(getY() + getIY() + getVS() + 20); rect2.setY(getY() + getIY() + getVS() + 44);
			break; case 7: case 11:
				rect1.setX(getX() + getIX() + getHS() + 25); rect2.setX(getX() + getIX() + getHS() + 19);
				rect1.setY(getY() + getIY() + getVS() + 17); rect2.setY(getY() + getIY() + getVS() + 41);
			break; case 8: case 9: case 10:
				rect1.setX(getX() + getIX() + getHS() + 30); rect2.setX(getX() + getIX() + getHS() + 9 );
				rect1.setY(getY() + getIY() + getVS() + 17); rect2.setY(getY() + getIY() + getVS() + 41);
		}
	} else if (getFacing() == FACE_UP) {
		base = 4 * 16;
		switch (subIm) {
			case 0: case 6:
				rect1.setX(getX() + getIX() + getHS() + 19); rect2.setX(getX() + getIX() + getHS() + 42);
				rect1.setY(getY() + getIY() + getVS() + 39); rect2.setY(getY() + getIY() + getVS() + 39);
			break; case 1: case 5:
				rect1.setX(getX() + getIX() + getHS() + 20); rect2.setX(getX() + getIX() + getHS() + 44);
				rect1.setY(getY() + getIY() + getVS() + 42); rect2.setY(getY() + getIY() + getVS() + 36);
			break; case 2: case 3: case 4:
				rect1.setX(getX() + getIX() + getHS() + 20); rect2.setX(getX() + getIX() + getHS() + 44);
				rect1.setY(getY() + getIY() + getVS() + 52); rect2.setY(getY() + getIY() + getVS() + 31);
			break; case 7: case 11:
				rect1.setX(getX() + getIX() + getHS() + 17); rect2.setX(getX() + getIX() + getHS() + 41);
				rect1.setY(getY() + getIY() + getVS() + 36); rect2.setY(getY() + getIY() + getVS() + 42);
			break; case 8: case 9: case 10:
				rect1.setX(getX() + getIX() + getHS() + 17); rect2.setX(getX() + getIX() + getHS() + 41);
				rect1.setY(getY() + getIY() + getVS() + 31); rect2.setY(getY() + getIY() + getVS() + 52);
		}
	} else if (getFacing() == FACE_RIGHT) {
		base = 5 * 16;
		switch (subIm) {
			case 0: case 6:
				rect1.setX(getX() + getIX() + getHS() + 39); rect2.setX(getX() + getIX() + getHS() + 39);
				rect1.setY(getY() + getIY() + getVS() + 42); rect2.setY(getY() + getIY() + getVS() + 19);
			break; case 1: case 5:
				rect1.setX(getX() + getIX() + getHS() + 42); rect2.setX(getX() + getIX() + getHS() + 36);
				rect1.setY(getY() + getIY() + getVS() + 41); rect2.setY(getY() + getIY() + getVS() + 17);
			break; case 2: case 3: case 4:
				rect1.setX(getX() + getIX() + getHS() + 52); rect2.setX(getX() + getIX() + getHS() + 31);
				rect1.setY(getY() + getIY() + getVS() + 41); rect2.setY(getY() + getIY() + getVS() + 17);
			break; case 7: case 11:
				rect1.setX(getX() + getIX() + getHS() + 36); rect2.setX(getX() + getIX() + getHS() + 42);
				rect1.setY(getY() + getIY() + getVS() + 44); rect2.setY(getY() + getIY() + getVS() + 20);
			break; case 8: case 9: case 10:
				rect1.setX(getX() + getIX() + getHS() + 31); rect2.setX(getX() + getIX() + getHS() + 52);
				rect1.setY(getY() + getIY() + getVS() + 44); rect2.setY(getY() + getIY() + getVS() + 20);
		}
	}

	hand.setSubImage(base + subIm);
}

/********************************************************************
 * getHandRect1() getHandRect2() 1 is left hand. 2 is right hand.
 * 	Returns the rectangle the hand is using.
 ********************************************************************/
const Rectangle & Enemy :: getHandRect1() const {
	return rect1;
}

const Rectangle & Enemy :: getHandRect2() const {
	return rect2;
}

/********************************************************************
 * getHandRect()
 * 	Inherited from Living. Basically a step method. Gets called
 * 	every frame before movement.
 ********************************************************************/
void Enemy :: update() {
	if (getFacing() == FACE_DOWN)
		setSubImage(7 * 16 + 3 * 0);
	else if (getFacing() == FACE_LEFT)
		setSubImage(7 * 16 + 3 * 1);
	else if (getFacing() == FACE_UP)
		setSubImage(7 * 16 + 3 * 2);
	else if (getFacing() == FACE_RIGHT)
		setSubImage(7 * 16 + 3 * 3);
}

/********************************************************************
 * setImageHandler()
 * 	Overloaded from Living. Needs to be over written, because this
 * 	sets the hand's image handler as well.
 ********************************************************************/
void Enemy :: setImageHandler(ImageHandler * ih) {
	Living :: setImageHandler(ih);
	hand.setImageHandler(ih);
}

void Enemy :: moveTowards(Thing * other) {
	// Get relative position, measuring center points.
	short relPos = other->getRelativePosition(*this);
	// First, figure facing.
	     if (relPos == LEFT)  { setFacing(FACE_LEFT); }
	else if (relPos == UP)    { setFacing(FACE_UP  ); }
	else if (relPos == RIGHT) { setFacing(FACE_RIGHT); }
	else if (relPos == DOWN)  { setFacing(FACE_DOWN); }
	// Diagonal directions are ignored.

	// Now figure speed.
	switch (relPos) {
		case LEFT : upToMaxHS(-ENEMY_ACCEL, getMaxSpeed()); break;
		case RIGHT: upToMaxHS( ENEMY_ACCEL, getMaxSpeed()); break;
		case DOWN : upToMaxVS(-ENEMY_ACCEL, getMaxSpeed()); break;
		case UP   : upToMaxVS( ENEMY_ACCEL, getMaxSpeed()); break;

		case RIGHT_DOWN: upToMaxDegSpeed(-45, ENEMY_ACCEL, getMaxSpeed()); break;
		case RIGHT_UP  : upToMaxDegSpeed(45,  ENEMY_ACCEL, getMaxSpeed()); break;
		case LEFT_DOWN : upToMaxDegSpeed(235, ENEMY_ACCEL, getMaxSpeed()); break;
		case LEFT_UP   : upToMaxDegSpeed(135, ENEMY_ACCEL, getMaxSpeed()); break;
	}
}

/********************************************************************
 * interact()
 * 	Inherited from Thing, how this object deals with another thing.
 ********************************************************************/
bool Enemy :: interact(Rectangle * other) {
	bool intersects = willIntersect(*other);

	if (other->type() == ID_ENEMY || other->type() == ID_PLAYER) {
		if (intersects) {
			short curPos = other->nextRelativePosition(*this);
			if (curPos == LEFT) {
				other->setHS(getX() + getHS() - other->getX() - other->getW());
			} else if (curPos == RIGHT) {
				other->setHS(getX() + getHS() + getW() - other->getX());
			} else if (curPos == DOWN) {
				other->setVS(getY() + getVS() - other->getY() - other->getH());
			} else if (curPos == UP) {
				other->setVS(getY() + getVS() + getH() - other->getY());
			} else {
				// nextRelativePosition wont return anything else.
				assert(false);
			}
		}
	}
/*
		if (getHandRect1().willIntersect(*player)) {
			player->hurt(ENEMY_DAMAGE);

			float acc = 64 * 13 / FPS;
			float cx = player->getCX() - getHandRect1().getCX();
			float cy = player->getCY() - getHandRect1().getCY();
			float angle = atan(cy / cx);
			float dx = abs(cos(angle) * acc);
			float dy = abs(sin(angle) * acc);

			if (cx < 0.0f)
				player->addHS(-dx );
			else
				player->addHS( dx );

			if (cy < 0.0f)
				player->addVS(-dy );
			else
				player->addVS( dy );
		}

		if (getHandRect2().willIntersect(*player)) {
			player->hurt(ENEMY_DAMAGE);

			float acc = 64 * 13 / FPS;
			float cx = player->getCX() - getHandRect2().getCX();
			float cy = player->getCY() - getHandRect2().getCY();
			float angle = atan(cy / cx);
			float dx = abs(cos(angle) * acc);
			float dy = abs(sin(angle) * acc);

			if (cx < 0.0f)
				player->addHS(-dx );
			else
				player->addHS( dx );

			if (cy < 0.0f)
				player->addVS(-dy );
			else
				player->addVS( dy );
		}
*/

	return intersects;
}
