// rectangle.h

#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "constants.h"
#include "thingHandler.h"

// Default for the rectangle, Default Future Step.
#define DEF_FUTSTEP 1

/*********************************************************************
 * Rectangle
 * 	This class is a rectangle that can move. This class can change
 * 	the speed, direction, horizontal speed, vertical speed, x, y,
 * 	width, and height of a rectangle. This class can also check
 * 	the collision, touching, and containing state between other
 * 	rectangles.
*********************************************************************/
class Rectangle {
	public:
		// Possible relative positions.
		static const short NONE  = 0; // intersecting
		static const short LEFT  = 1; // this is to the left of that
		static const short UP    = 2; // etc
		static const short RIGHT = 4;
		static const short DOWN  = 8;
		static const short LEFT_UP    = 3;
		static const short RIGHT_UP   = 6;
		static const short LEFT_DOWN  = 9;
		static const short RIGHT_DOWN = 12;

		// Initialize
		Rectangle();

		// All rectangle logic in floats.
		Rectangle(float x, float y);
		Rectangle(float x, float y, float w, float h);
		Rectangle(float x, float y, float w, float h,
					 float vs, float hs);

		Rectangle(const Rectangle & rect);

		// Got a couple virtual guys.
		int getIndex() const;
		ThingHandler * getThingHandler();
		virtual void normalMode();
		virtual void dataMode(ThingHandler * sss, unsigned index);
		bool isNormalMode() const;
		bool isDataMode  () const;
		virtual void move();

		// Getters and setters. H = height. W = width.
		// HS = horizontal speed. VS = vertical speed.
		// CX = center x, CY = center y
		float getX() const;
		float getY() const;
		float getW() const;
		float getH() const;
		float getHS() const;
		float getVS() const;
		float getRad() const;
		float getDeg() const;
		float getSpeed() const;
		float getCX() const;
		float getCY() const;

		void reset();

		void setX(const float x);
		void setY(const float y);
		void setW(const float w);
		void setH(const float h);
		void setVS(const float & vs);
		void setHS(const float & hs);
		void setRadSpeed(const float & rad, const float & speed);
		void setDegSpeed(const float & deg, const float & speed);
		void setCX(const float & cx);
		void setCY(const float & cy);

		void setXY(float x, float y);
		void setWH(float w, float h);
		void setXYWH(float x, float y, float w, float h);

		void addX(const float & dx);
		void addY(const float & dy);
		void addW(const float & w);
		void addH(const float & h);
		void addHS(const float & hs);
		void addVS(const float & vs);
		void addCX(const float & dx);
		void addCY(const float & dy);
		void addRadSpeed(const float & rad, const float & speed);
		void addDegSpeed(const float & deg, const float & speed);

		void getXY(float & x, float & y);
		void getCXY(float & cx, float & cy);
		void getWH(float & w, float & h);
		void getHSVS(float & hs, float & vs);
		void getRadSpeed(float & rad, float & speed);
		void getDegSpeed(float & deg, float & speed);

		void getXYWH(float & x, float & y, float & w, float & h);

		// Returns true if both rectangles are touching each other, but not
		// colliding.
		bool isTouching(const Rectangle & rect) const;
		bool isTouching(const float & pX, const float & pY) const;

		// Returns true if the parameter rectangle is inside this rectangle.
		bool isContaining(const Rectangle & rect) const;
		bool isContaining(const float & pX, const float & pY) const;

		// Returns true if both rectangles intersect or contains each other.
		bool isIntersecting(const Rectangle & rect) const;

		short getRelativePosition(const Rectangle & rect) const;
		short getRelativePositionCenter(const Rectangle & rect) const;
		short nextRelativePosition(const Rectangle & rect) const;

		bool willContain(const float & x, const float & y) const;
		bool willContain(const Rectangle & rect) const;
		bool willIntersect(const Rectangle & rect) const;
		int willContain(const float & x, const float & y, const int steps) const;
		int willContain(const Rectangle & rect, const int steps) const;
		int willIntersect(const Rectangle & rect, const int steps) const;

		static int willContain(const Rectangle & parent, const Rectangle & child, const int steps = DEF_FUTSTEP);
		static int willContain(const Rectangle & rect, const float pX, const float pY, const int steps = DEF_FUTSTEP);
		static int willIntersect(Rectangle tmp1, Rectangle tmp2, const int steps = DEF_FUTSTEP);

		virtual int type() const { return ID_RECTANGLE; };
		virtual bool interact(Rectangle * other) { return willIntersect(*other); };

	protected:
		ThingHandler * thingHandle;

	private:
		// x, y, width, height, horizontal speed, vertical speed
		float x, y, w, h;
		float hs, vs;
		bool normal;
		unsigned index;
};

#endif // _RECTANGLE_H
