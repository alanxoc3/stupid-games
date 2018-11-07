// living.cpp

#include "living.h"

/********************************************************************
 * Default Constructor
 * 	Initializes some stuff.
 ********************************************************************/
Living :: Living(unsigned maxhp, unsigned attack) : Thing() {
	setMaxHP(maxhp);
	setAttackLevel(attack);
	heal();
	setFriction(DEF_FRICTION);
	setMaxSpeed(DEF_MAXSPEED);
}

/********************************************************************
 * getHP()
 * 	Returns the current amount of health that the living thing has.
 * 	Zero health means that the living thing is dead.
 ********************************************************************/
unsigned Living :: getHP() const {
	if (isNormalMode())
		return hp;
	else
		return thingHandle->getHP(getIndex());
}

/********************************************************************
 * setHP()
 * 	Sets the HP, must be >= zero and <= Max Health.
 ********************************************************************/
void Living :: setHP(unsigned hp) {
	if (hp <= getMaxHP()) {
		if (isNormalMode())
			this->hp = hp;
		else
			thingHandle->setHP(getIndex(), hp);
	}
}

/********************************************************************
 * getMaxHP()
 * 	Returns the maximum amount of hp that the living thing is
 * 	allowed to have.
 ********************************************************************/
unsigned Living :: getMaxHP() const {
	if (isNormalMode())
		return maxhp;
	else
		return thingHandle->getMH(getIndex());
}

/********************************************************************
 * getAttackLevel()
 * 	Returns the amount of damage the living thing can do. Or in
 * 	other words, how powerful the living thing is.
 ********************************************************************/
unsigned Living :: getAttackLevel() const {
	return attack;
}

/********************************************************************
 * hurt()
 * 	Inflicts so much damage on the living thing. Careful, too much
 * 	damage may kill it.
 ********************************************************************/
void Living :: hurt(const unsigned damage) {
	setHP(getHP() - damage);
}

/********************************************************************
 * kill()
 * 	Kills the living thing. This is done naturally by setting the hp
 * 	to zero.
 ********************************************************************/
void Living :: kill() {
	setHP(0u);
}

/********************************************************************
 * heal()
 * 	Heals the living thing all the way, even if the living thing
 * 	had zero health.
 ********************************************************************/
void Living :: heal() {
	setHP(getMaxHP());
}

/********************************************************************
 * heal()
 * 	Heals the living thing by the parameter's amount of health. The
 * 	living thing will heal even if it is dead. If it is healed
 * 	above the max health, then the health is now at the max health.
 ********************************************************************/
void Living :: heal(const unsigned h) {
	if (h > 0)
		setHP(getHP() + h);

	if (getHP() > getMaxHP())
		setHP(getMaxHP());
}

/********************************************************************
 * setMaxHP()
 * 	Sets the maximum amount of health that the living thing may
 * 	have. Must be ABOVE zero.
 ********************************************************************/
void Living :: setMaxHP(const unsigned h) {
	if (h > 0){
		if (isNormalMode())
			maxhp = h;
		else
			thingHandle->setMH(getIndex(), h);

		if (getHP() > getMaxHP()) {
			setHP(getMaxHP());
		}
	}
}

/********************************************************************
 * setAttackLevel()
 * 	Sets the power or amount of damage that the living thing may
 * 	inflict upon other objects. Cannot be negative, but can be zero.
 ********************************************************************/
void Living :: setAttackLevel(const unsigned damage) {
	if (damage >= 0)
		attack = damage;
}

/********************************************************************
 * isDead()
 * 	Returns true if the living thing is actually dead.
 ********************************************************************/
bool Living :: isDead() const {
	return getHP() <= 0;
}

/********************************************************************
 * isAlive()
 * 	Returns true if the living thing is actually alive.
 ********************************************************************/
bool Living :: isAlive() const {
	return getHP() > 0;
}

/*********************************************************************
 * normalMode()
 * 	Sets the mode of the rectangle AND the image to normal.
 *********************************************************************/
void Living :: normalMode() {
	if (isDataMode()) {
		hp = getHP();
		maxhp = getMaxHP();
		Thing :: normalMode();
	}
}

/*********************************************************************
 * datamode()
 * 	Sets the mode of the rectangle and the image to data.
 *********************************************************************/
void Living :: dataMode(ThingHandler * sss, unsigned index) {
	if (isNormalMode() && sss != nullptr) {
		sss->setHP( index, getHP() );
		sss->setMH( index, getMaxHP() );
		sss->enableHP( index );

		Thing :: dataMode(sss, index);
	}
}

/********************************************************************
 * upToMaxHS() uptoMaxVS() upToMaxDegSpeed()
 * 	Sets the objects to the speed plus the parameter, but if it
 * 	is greater than the max speed (PS), then sets to that.
 ********************************************************************/
void Living :: upToMaxHS(float hs, float max) {
	addHS(hs);

	if (hs > 0.0f && getHS() > max) {
		setHS(max);
	} else if (hs < 0.0f && getHS() < -max) {
		setHS(-max);
	}
}

void Living :: upToMaxVS(float vs, float max) {
	addVS(vs);

	if (vs > 0.0f && getVS() > max) {
		setVS(max);
	} else if (vs < 0.0f && getVS() < -max) {
		setVS(-max);
	}
}

void Living :: upToMaxDegSpeed(float deg, float speed, float max) {
	float dx =  cos(deg * PI / 180) * speed;
	float dy =  sin(deg * PI / 180) * speed;
	float mdx = cos(deg * PI / 180) * max;
	float mdy = sin(deg * PI / 180) * max;

	upToMaxHS(dx, abs(mdx));
	upToMaxVS(dy, abs(mdy));
}

/********************************************************************
 * getFacing()
 * 	Returns the direction that Living is facing. The possible
 * 	values are:
 * 		living.FACE_LEFT
 * 		living.FACE_UP
 * 		living.FACE_RIGHT
 * 		living.FACE_DOWN
 * 		living.FACE_LEFT_UP
 * 		living.FACE_RIGHT_UP
 * 		living.FACE_LEFT_DOWN
 * 		living.FACE_RIGHT_DOWN
 ********************************************************************/
short Living :: getFacing() const {
	return facing;
}

/********************************************************************
 * setFacing()
 * 	Sets the direction that this living thing is facing.
 ********************************************************************/
void Living :: setFacing(const short dir) {
	if (dir == FACE_LEFT       ||
		 dir == FACE_UP         ||
		 dir == FACE_RIGHT      ||
		 dir == FACE_DOWN       ||
		 dir == FACE_LEFT_UP    ||
		 dir == FACE_RIGHT_UP   ||
		 dir == FACE_LEFT_DOWN  ||
		 dir == FACE_RIGHT_DOWN)
	{
		facing = dir;
	}
}
