// living.h

#ifndef _LIVING_H
#define _LIVING_H

#include "constants.h"
#include "thing.h"
#include "grid.h"
#include "thingHandler.h"

/********************************************************************
 * Living
 * 	Living things are things. Things are rectangles. Enemies, and
 * 	players are living things. Living things cannot be a class on
 * 	its own, because the null virtual functions inherited are not
 * 	set. Living things have an HP, can die, and living things in
 * 	mister-sss have an attack value as well. The living type is
 * 	defined in "constants.h".
 ********************************************************************/
class Living : public Thing {
	public:
		Living(unsigned maxhp = DEF_MAXHP, unsigned attack = DEF_ATTACK);

		static const short FACE_NONE  = 0;
		static const short FACE_LEFT  = 1;
		static const short FACE_UP    = 2;
		static const short FACE_RIGHT = 4;
		static const short FACE_DOWN  = 8;
		static const short FACE_LEFT_UP    = 3;
		static const short FACE_RIGHT_UP   = 6;
		static const short FACE_LEFT_DOWN  = 9;
		static const short FACE_RIGHT_DOWN = 12;

		short getFacing() const;
		void setFacing(const short dir);

		unsigned getHP() const;
		unsigned getMaxHP() const;
		unsigned getAttackLevel() const;

		// To use this method, the parameter should be the user's attack value.
		void hurt(const unsigned damage);

		// Sets the HP to 0.
		void kill();

		// Sets the HP to MaxHP
		void heal();

		// Heals so much of the HP, up to the max
		void heal(const unsigned h);

		// Setters
		void setMaxHP(const unsigned h);
		void setAttackLevel(const unsigned damage);
		void setHP(unsigned hp);

		inline float getMaxSpeed() const { return ms; };
		inline void  setMaxSpeed(float ms) { this->ms = ms; };

		inline float getFriction() const  { return friction; };
		inline void setFriction(float fr) { this->friction = friction; };

		void upToMaxHS(float hs, float max);
		void upToMaxVS(float vs, float max);
		void upToMaxDegSpeed(float deg, float speed, float max);

		// Returns whether or not the living thing is dead.
		bool isDead() const;
		bool isAlive() const;

		// Used along with thing.
		virtual void normalMode();
		virtual void dataMode(ThingHandler * sss, unsigned index);

		virtual void update() { };

		// Inherited from Thing.
		virtual int type() const { return ID_LIVING; };

	private:
		short facing;
		unsigned hp, maxhp, attack;
		float friction, ms;
};

#endif // _LIVING_H
