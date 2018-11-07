// rectangle.cpp

#include "rectangle.h"
#include "constants.h"

// CONSTRUCTORS

/*********************************************************************
 * Default Constructor
 * 	Sets Defaults.
 *********************************************************************/
Rectangle :: Rectangle() {
	normal = true;
	thingHandle = nullptr;
	index = 0;
	reset();
}

/*********************************************************************
 * Constructor
 * 	The x and y are the starting coordinates.
 *********************************************************************/
Rectangle :: Rectangle(float x, float y) {
	normal = true;
	thingHandle = nullptr;
	index = 0;
	setX       (x);
	setY       (y);
	setW       (0.0f);
	setH       (0.0f);
	setHS      (0.0f);
	setVS      (0.0f);
}

/*********************************************************************
 * Constructor
 * 	The x and y are the starting coordinates. The w and h are the
 * 	rectangle's width and height.
 *********************************************************************/
Rectangle :: Rectangle(float x, float y, float w, float h) {
	normal = true;
	thingHandle = nullptr;
	index = 0;
	setX       (x);
	setY       (y);
	setW       (w);
	setH       (h);
	setHS      (0.0f);
	setVS      (0.0f);
}

/*********************************************************************
 * Constructor
 * 	The x and y are the starting coordinates. The w and h are the
 * 	rectangle's width and height. The vs and hs are the vertical
 * 	speed and horizontal speed. Aka dx and dy.
 *********************************************************************/
Rectangle :: Rectangle(float x, float y, float w, float h, float vs, float hs) {
	normal = true;
	thingHandle = nullptr;
	index = 0;
	setX       (x);
	setY       (y);
	setW       (w);
	setH       (h);
	setHS      (hs);
	setVS      (vs);
}

/*********************************************************************
 * Copy Constructor
 * 	Copies one rectangle to another.
 *********************************************************************/
Rectangle :: Rectangle(const Rectangle & rect) {
	if (&rect != this) {
		normal = true;
		thingHandle = nullptr;
		index = 0;

		x  = rect.getX();
		y  = rect.getY();
		w  = rect.getW();
		h  = rect.getH();
		vs = rect.getVS();
		hs = rect.getHS();
	}
}

// GETTERS

/*********************************************************************
 * getX()
 * 	Returns the x position.
 *********************************************************************/
float Rectangle :: getX() const {
	if (isDataMode())
		return thingHandle->getX (index);
	else
		return x;
}

/*********************************************************************
 * getY()
 * 	Returns the y position.
 *********************************************************************/
float Rectangle :: getY() const {
	if (isDataMode())
		return thingHandle->getY (index);
	else
		return y;
}

/*********************************************************************
 * getW()
 * 	Returns the width.
 *********************************************************************/
float Rectangle :: getW() const {
	if (isDataMode())
		return thingHandle->getW (index);
	else
		return w;
}

/*********************************************************************
 * getH()
 * 	Returns the height.
 *********************************************************************/
float Rectangle :: getH() const {
	if (isDataMode())
		return thingHandle->getH (index);
	else
		return h;
}

/*********************************************************************
 * getHS()
 * 	Returns the horizontal speed.
 *********************************************************************/
float Rectangle :: getHS() const {
	if (isDataMode())
		return thingHandle->getHS(index);
	else
		return hs;
}

/*********************************************************************
 * getVS()
 * 	Returns the vertical speed.
 *********************************************************************/
float Rectangle :: getVS() const {
	if (isDataMode())
		return thingHandle->getVS(index);
	else
		return vs;
}

/*********************************************************************
 * getRad()
 * 	Returns the directional angle of the rectangle in radians.
 *********************************************************************/
float Rectangle :: getRad() const {
	// tan (y / x) = radian
	return tan(getVS() / getHS());
}

/*********************************************************************
 * getRad()
 * 	Returns the directional angle of the rectangle in degrees.
 *********************************************************************/
float Rectangle :: getDeg() const {
	// degree = rad * 180 / pi
	return getRad() * 180 / PI;
}

/*********************************************************************
 * getSpeed()
 * 	Returns the directional speed of the rectangle.
 *********************************************************************/
float Rectangle :: getSpeed() const {
	// Pythagorean theorem of hs and vs.
	return sqrt(pow(getHS(), 2) + pow(getVS(), 2));
}

// SETTERS

/*********************************************************************
 * setX()
 * 	Sets the x position.
 *********************************************************************/
void Rectangle :: setX(const float x) {
	if (isDataMode())
		thingHandle->setX (index, x);
	else
		this->x = x;
}

/*********************************************************************
 * setY()
 * 	Sets the y position.
 *********************************************************************/
void Rectangle :: setY(const float y) {
	if (isDataMode())
		thingHandle->setY (index, y);
	else
		this->y = y;
}

/*********************************************************************
 * setW()
 * 	Sets the width
 *********************************************************************/
void Rectangle :: setW(const float w) {
	if (isDataMode())
		thingHandle->setW (index, w);
	else
		this->w = w;
}

/*********************************************************************
 * setH()
 * 	Sets the width
 *********************************************************************/
void Rectangle :: setH(const float h) {
	if (isDataMode())
		thingHandle->setH (index, h);
	else
		this->h = h;
}

/********************************************************************
 * setVS()
 * 	Sets the vertical speed.
 ********************************************************************/
void Rectangle :: setVS(const float & vs) {
	if (isDataMode())
		thingHandle->setVS(index, vs);
	else
		this->vs = vs;
}

/********************************************************************
 * setHS()
 * 	Sets the horizontal speed.
 ********************************************************************/
void Rectangle :: setHS(const float & hs) {
	if (isDataMode())
		thingHandle->setHS(index, hs);
	else
		this->hs = hs;
}

/********************************************************************
 * setRadSpeed()
 * 	Sets the direction in radians and the speed.
 ********************************************************************/
void Rectangle :: setRadSpeed(const float & rad, const float & speed) {
	// Simple trig...
	setHS(cos(rad) * speed);
	setVS(sin(rad) * speed);
}

/********************************************************************
 * addRadSpeed()
 * 	Adds the angle/speed to the current one.
 ********************************************************************/
void Rectangle :: addRadSpeed(const float & rad, const float & speed) {
	// Simple trig...
	setHS(getHS() + cos(rad) * speed);
	setVS(getVS() + sin(rad) * speed);
}

/********************************************************************
 * setDegSpeed()
 * 	Sets the direction in degrees and the speed.
 ********************************************************************/
void Rectangle :: setDegSpeed(const float & deg, const float & speed) {
	// radians = deg * pi / 180
	setRadSpeed(deg * PI / 180, speed);
}

/********************************************************************
 * addDegSpeed()
 * 	Adds the angle/speed to the current one.
 ********************************************************************/
void Rectangle :: addDegSpeed(const float & deg, const float & speed) {
	// radians = deg * pi / 180
	addRadSpeed(deg * PI / 180, speed);
}

// ADDERS

/********************************************************************
 * addX()
 * 	Adds dx to the x position.
 ********************************************************************/
void Rectangle :: addX(const float & dx) {
	setX(getX() + dx);
}

/********************************************************************
 * addY()
 * 	Adds dy to the y position.
 ********************************************************************/
void Rectangle :: addY(const float & dy) {
	setY(getY() + dy);
}

/********************************************************************
 * addW()
 * 	Adds w to the width.
 ********************************************************************/
void Rectangle :: addW(const float & w) {
	setW(getW() + w);
}

/********************************************************************
 * addH()
 * 	Adds h to the height.
 ********************************************************************/
void Rectangle :: addH(const float & h) {
	setH(getH() + h);
}

/********************************************************************
 * addHS()
 * 	Adds hs to the horizontal speed.
 ********************************************************************/
void Rectangle :: addHS(const float & hs) {
	setHS(getHS() + hs);
}

/********************************************************************
 * addVS()
 * 	Adds vs to the vertical speed.
 ********************************************************************/
void Rectangle :: addVS(const float & vs) {
	setVS(getVS() + vs);
}

// SPECIAL GETTERS

/********************************************************************
 * getXY()
 * 	Passes the x and y by reference.
 ********************************************************************/
void Rectangle :: getXY(float & x, float & y) {
	x = getX();
	y = getY();
}

/********************************************************************
 * getWH()
 * 	Passes the width and height by reference.
 ********************************************************************/
void Rectangle :: getWH(float & w, float & h) {
	w = getW();
	h = getH();
}

/********************************************************************
 * getHSVS()
 * 	Passes the horizontal speed and vertical speed by reference.
 ********************************************************************/
void Rectangle :: getHSVS(float & hs, float & vs) {
	hs = getHS();
	vs = getVS();
}

/********************************************************************
 * getRadSpeed()
 * 	Passes the radian direction and speed direction by reference.
 ********************************************************************/
void Rectangle :: getRadSpeed(float & rad, float & speed) {
	rad = getRad();
	speed = getSpeed();
}

/********************************************************************
 * getDegSpeed()
 * 	Passes the degree direction and speed direction by reference.
 ********************************************************************/
void Rectangle :: getDegSpeed(float & deg, float & speed) {
	deg = getDeg();
	speed = getSpeed();
}

/********************************************************************
 * getXYWH()
 * 	Passes the x, y, width, and height by reference.
 ********************************************************************/
void Rectangle :: getXYWH(float & x, float & y, float & w, float & h) {
	getXY(x, y);
	getWH(w, h);
}

// COLLISION

/********************************************************************
 * isTouching()
 * 	Returns true if pX and pY are within 1 pixel of the outer edge
 * 	of the rectangle.
 ********************************************************************/
bool Rectangle :: isTouching(const float & pX, const float & pY) const
{
	float center[] = {getCX(), getCY()};
	float rCenter[] = {pX, pY};
	int lengths[] = {(int) (getW() / 2), (int) (getH() / 2)};

	int xLen = abs((int) (center[0] - rCenter[0]));
	int yLen = abs((int) (center[1] - rCenter[1]));

	return (xLen == lengths[0] && yLen < lengths[1]) ||
			 (yLen == lengths[1] && xLen < lengths[0]);
}

/********************************************************************
 * isContaining()
 * 	Returns true if pX and pY are inside the rectangle.
 ********************************************************************/
bool Rectangle :: isContaining(const float & pX, const float & pY) const
{
	return pX > getX() && pX < getX() + getW()
		&& pY > getY() && pY < getY() + getH();
}

/********************************************************************
 * isTouching()
 * 	Returns true if rect is within 1 pixel of the outer edge of
 * 	this rectangle, or vice versa.
 ********************************************************************/
bool Rectangle :: isTouching(const Rectangle & rect) const
{
	// Convert to integer to round down
	float center[] = {getCX(), getCY()};
	float rCenter[] = {rect.getCX(), rect.getCY()};
	int lengths[] = {(int) (getW() / 2 + rect.getW() / 2), (int) (getH() / 2 + rect.getH() / 2)};

	int xLen = abs((int) (center[0] - rCenter[0]));
	int yLen = abs((int) (center[1] - rCenter[1]));

	return (xLen == lengths[0] && yLen < lengths[1]) ||
			 (yLen == lengths[1] && xLen < lengths[0]);
}

/********************************************************************
 * isContaining()
 * 	Returns true if rect is inside this rectangle.
 ********************************************************************/
bool Rectangle :: isContaining(const Rectangle & rect) const
{
	// Check if all points are being contained.
	return isContaining(rect.getX(), rect.getY()) &&
		isContaining(rect.getX() + rect.getW(), rect.getY() + rect.getH());
}

/********************************************************************
 * isIntersecting()
 * 	Returns true if rect and this rectangle are intersecting at any
 * 	area.
 ********************************************************************/
bool Rectangle :: isIntersecting(const Rectangle & rect) const
{
	// If that is equal to none, then they are intersecting!
	return getRelativePosition(rect) == NONE;
}

/********************************************************************
 * getRelativePosition()
 * 	Returns a number signifying the relative position of this
 * 	rectangle when compared with the axis of rect, if the
 * 	rectangles are not intersecting.
 * 	Possible values are:
 * 	NONE        ==> this and rect are intersecting
 * 	LEFT        ==> this is to left of rect
 * 	UP          ==> this is above rect
 * 	RIGHT       ==> this is to right of rect
 * 	DOWN        ==> this is below rect
 * 	LEFT_UP     ==> this is to left and above rect
 * 	RIGHT_UP    ==> this is to right and above rect
 * 	LEFT_DOWN   ==> this is to left and below rect
 * 	RIGHT_DOWN  ==> this is to right and below rect
 ********************************************************************/
short Rectangle :: getRelativePosition(const Rectangle & rect) const {
	float center[] = {getCX(), getCY()};
	float rCenter[] = {rect.getCX(), rect.getCY()};
	float lengths[] = {getW() / 2 + rect.getW() / 2,  getH() / 2 + rect.getH() / 2};

	float xLen = center[0] - rCenter[0];
	float yLen = center[1] - rCenter[1];
	// Two must not have an equals sign, because the other object is a rectange...
	short iOnLeft  = (xLen <= -lengths[0]) * LEFT;
	short iOnRight = (xLen >=  lengths[0]) * RIGHT;
	short iOnUp    = (yLen >=  lengths[1]) * UP;
	short iOnDown  = (yLen <= -lengths[1]) * DOWN;

	return iOnLeft + iOnRight + iOnUp + iOnDown;
}

/********************************************************************
 * getRelativePositionCenter()
 * 	Returns a number signifying the relative position of this
 * 	rectangle when compared with the axis of rect, but may be
 * 	intersecting.
 * 	Possible values are:
 * 	NONE        ==> this and rect are in the exact same spot
 * 	LEFT        ==> this is to left of rect maybe inside
 * 	UP          ==> this is above rect maybe inside
 * 	RIGHT       ==> this is to right of rect maybe inside
 * 	DOWN        ==> this is below rect maybe inside
 * 	LEFT_UP     ==> this is to left and above rect maybe inside
 * 	RIGHT_UP    ==> this is to right and above rect maybe inside
 * 	LEFT_DOWN   ==> this is to left and below rect maybe inside
 * 	RIGHT_DOWN  ==> this is to right and below rect maybe inside
 ********************************************************************/
short Rectangle :: getRelativePositionCenter(const Rectangle & rect) const {
	float center[] = {getCX(), getCY()};
	float rCenter[] = {rect.getCX(), rect.getCY()};

	float xLen = center[0] - rCenter[0];
	float yLen = center[1] - rCenter[1];

	short iOnLeft  = (xLen < 0) * LEFT;
	short iOnRight = (xLen > 0) * RIGHT;
	short iOnUp    = (yLen > 0) * UP;
	short iOnDown  = (yLen < 0) * DOWN;

	return iOnLeft + iOnRight + iOnUp + iOnDown;
}

/********************************************************************
 * nextRelativePosition()
 * 	Returns a number signifying the next relative position of this
 * 	rectangle when compared with the axis of rect. This method is
 * 	not indecisive, a side will be picked no matter what.
 * 	Possible values are:
 * 	LEFT        ==> this will be to left of rect maybe inside
 * 	UP          ==> this will be above rect maybe inside
 * 	RIGHT       ==> this will be to right of rect maybe inside
 * 	DOWN        ==> this will be below rect maybe inside
 ********************************************************************/
short Rectangle :: nextRelativePosition(const Rectangle & rect) const {
	float center[] = {getCX(),                        getCY()};
	float rCenter[] = {rect.getCX(),                  rect.getCY()};
	float lengths[] = {getW() / 2 + rect.getW() / 2,  getH() / 2 + rect.getH() / 2};

	float xLen = center[0] - rCenter[0];
	float yLen = center[1] - rCenter[1];

	short curPos = getRelativePosition(rect);

	// Corner collision computed for more accurate collisions.
	if (curPos == RIGHT_DOWN) {
		// The distance in between corners.
		float measureX = xLen + lengths[0];
		float measureY = yLen - lengths[1];

		// Compare positive lengths.
		bool xBig = -rect.getHS() / measureX;
		bool yBig =  rect.getVS() / measureY;

		// The equals sign is here to prefer the x axis for perfect corner collisions.
		if (xBig >= yBig)
			return DOWN;
		else
			return RIGHT;
	} else if (curPos == RIGHT_UP) {
		float measureX = xLen + lengths[0];
		float measureY = yLen + lengths[1];
		bool xBig = -rect.getHS() / measureX;
		bool yBig = -rect.getVS() / measureY;

		if (xBig >= yBig)
			return UP;
		else
			return RIGHT;
	} else if (curPos == LEFT_DOWN) {
		float measureX = xLen - lengths[0];
		float measureY = yLen - lengths[1];
		bool xBig =  rect.getHS() / measureX;
		bool yBig =  rect.getVS() / measureY;

		if (xBig >= yBig)
			return DOWN;
		else
			return LEFT;
	} else if (curPos == LEFT_UP) {
		float measureX = xLen - lengths[0];
		float measureY = yLen + lengths[1];
		bool xBig =  rect.getHS() / measureX;
		bool yBig = -rect.getVS() / measureY;

		if (xBig >= yBig)
			return UP;
		else
			return LEFT;
	} else if (curPos == NONE) {
		// Already colliding try to figure out which is best direction.
		float measureX = (center[0] - rCenter[0]) / lengths[0];
		float measureY = (center[1] - rCenter[1]) / lengths[1];

		if (fabs(measureX) > fabs(measureY))
			return (measureX > 0) ? RIGHT : LEFT;
		else
			return (measureY > 0) ? UP : DOWN;
	} else {
		// Return the position for all the other directions.
		// Either NONE, LEFT, RIGHT, DOWN, or UP
		return curPos;
	}
}

/********************************************************************
 * willContain()
 * 	Returns true if this rectangle will have the coordinates within
 * 	it in the next step.
 ********************************************************************/
bool Rectangle :: willContain(const float & x, const float & y) const
{
	return Rectangle :: willContain(*this, x, y, DEF_FUTSTEP) != -1;
}

/********************************************************************
 * willContain()
 * 	Returns true if this rectangle will have rect inside of it
 * 	in the next step.
 ********************************************************************/
bool Rectangle :: willContain(const Rectangle & rect) const {
	return Rectangle :: willContain(rect, DEF_FUTSTEP) != -1;
}

/********************************************************************
 * willIntersect()
 * 	Returns true if this rectangle will intersect with rect in the
 * 	next step.
 ********************************************************************/
bool Rectangle :: willIntersect(const Rectangle & rect) const {
	return Rectangle :: willIntersect(rect, DEF_FUTSTEP) != -1;
}

/********************************************************************
 * willContain()
 * 	Returns the first step under steps where rect is inside of this
 * 	rectangle. -1 is returned if this doesn't happen in the given
 * 	amount of steps.
 ********************************************************************/
int Rectangle :: willContain(const Rectangle & rect, int steps) const
{
	return Rectangle :: willContain(*this, rect, steps);
}

/********************************************************************
 * willIntersect()
 * 	Returns the first step under steps where rect is intersecting
 * 	with rectangle. -1 is returned if this doesn't happen in the
 * 	given amount of steps.
 ********************************************************************/
int Rectangle :: willIntersect(const Rectangle & rect, int steps) const
{
	return Rectangle :: willIntersect(*this, rect, steps);
}

/********************************************************************
 * willContain()
 * 	Returns the first step under steps where the x y coordinate is
 * 	inside of this rectangle. -1 is returned if this doesn't happen
 * 	in the given amount of steps.
 ********************************************************************/
int Rectangle :: willContain(const float & x, const float & y, const int steps) const
{
	return Rectangle :: willContain(*this, x, y, DEF_FUTSTEP);
}

/********************************************************************
 * willContain()
 * 	A static method. Returns the first step when the child is
 * 	inside the parent. -1 is returned if this doesn't happen in the
 * 	given amount of steps.
 ********************************************************************/
int Rectangle :: willContain(const Rectangle & parent, const Rectangle & child, int steps)
{
	if (steps < 0)
		steps = 0;

	Rectangle tmp1 = parent;
	Rectangle tmp2 = child;

	for (int i = 0; i <= steps; ++i) {
		if (tmp1.isContaining(tmp2))
			return i;

		tmp1.move();
		tmp2.move();
	}

	return -1;
}

/********************************************************************
 * willIntersect()
 * 	A static method. Returns the first step when r1 intersects with
 * 	r2. -1 is returned if this doesn't happen in the given amount
 * 	of steps.
 ********************************************************************/
int Rectangle :: willIntersect(Rectangle tmp1, Rectangle tmp2, int steps)
{
	if (steps <= 0)
		return tmp1.isIntersecting(tmp2) ? 0 : -1;

	// Move X and Y INDEPENDENT!
	for (int i = 1; i <= steps; ++i) {
		tmp1.addX(tmp1.getHS());
		tmp2.addX(tmp2.getHS());

		if (tmp1.isIntersecting(tmp2))
			return i;

		// Rewind.
		tmp1.addX(-tmp1.getHS());
		tmp2.addX(-tmp2.getHS());

		tmp1.addY(tmp1.getVS());
		tmp2.addY(tmp2.getVS());

		if (tmp1.isIntersecting(tmp2))
			return i;

		tmp1.addX(tmp1.getHS());
		tmp2.addX(tmp2.getHS());
	}

	return -1;
}

/********************************************************************
 * willContain()
 * 	Returns the number of steps it takes for the point to be within
 * 	the rectangle. -1 is returned if there was no collision in the
 * 	amount of steps.
 ********************************************************************/
int Rectangle :: willContain(const Rectangle & rect, const float pX, const float pY, int steps)
{
	if (steps < 0)
		steps = 0;

	Rectangle tmp1 = rect;

	for (int i = 0; i <= steps; ++i) {
		if (tmp1.isContaining(pX, pY))
			return i;

		tmp1.move();
	}

	return -1;
}

/********************************************************************
 * move()
 * 	A generic function that may be over written. Adds the speed
 * 	to the x and y positions.
 ********************************************************************/
void Rectangle :: move() {
	addX(getHS());
	addY(getVS());
}

/********************************************************************
 * addCX()
 * 	Adds dx to the center x position. Same as addX().
 ********************************************************************/
void Rectangle :: addCX(const float & dx) {
	addX(dx);
}

/********************************************************************
 * addCY()
 * 	Adds dy to the center y position. Same as addY().
 ********************************************************************/
void Rectangle :: addCY(const float & dy) {
	addY(dy);
}

/********************************************************************
 * setCX()
 * 	Sets cx to the center x position of the rectangle.
 ********************************************************************/
void Rectangle :: setCX(const float & cx) {
	setX(cx - getW() / 2);
}

/********************************************************************
 * setCY()
 * 	Sets cy to the center y position of the rectangle.
 ********************************************************************/
void Rectangle :: setCY(const float & cy) {
	setY(cy - getH() / 2);
}

/********************************************************************
 * getCX()
 * 	Returns the center x position of the rectangle.
 ********************************************************************/
float Rectangle :: getCX() const {
	return getX() + getW() / 2;
}

/********************************************************************
 * getCY()
 * 	Returns the center y position of the rectangle.
 ********************************************************************/
float Rectangle :: getCY() const {
	return getY() + getH() / 2;
}

/********************************************************************
 * getCXY()
 * 	Passes the center x and center y by reference to cx and cy.
 ********************************************************************/
void Rectangle :: getCXY(float & cx, float & cy) {
	cx = getCX();
	cy = getCY();
}

/********************************************************************
 * reset()
 * 	Resets the values of x, y, w, h, hs, vs.
 ********************************************************************/
void Rectangle :: reset() {
	setX       (0.0f);
	setY       (0.0f);
	setW       (0.0f);
	setH       (0.0f);
	setHS      (0.0f);
	setVS      (0.0f);
}

/********************************************************************
 * getIndex()
 * 	Returns the index of the thing if this object is in data mode.
 * 	If in normal mode, returns -1.
 ********************************************************************/
int Rectangle :: getIndex() const {
	return (isDataMode() ? index : -1);
}

/********************************************************************
 * getThingHandler()
 * 	Returns the thingHandler currently used by this class. If the
 * 	object is in normal mode, then this method returns nullptr.
 ********************************************************************/
ThingHandler * Rectangle :: getThingHandler() {
	return thingHandle;
}

/********************************************************************
 * normalMode()
 * 	Sets the mode of the rectangle to normal mode. The rectangle is
 * 	in normal mode by default. This is no longer linked to the thing
 * 	handler. The data from the thing handler is copied to to this.
 ********************************************************************/
void Rectangle :: normalMode() {
	if (!normal) {
		normal = true; // Must be first
		setX       ( thingHandle->getX (index) );
		setY       ( thingHandle->getY (index) );
		setW       ( thingHandle->getW (index) );
		setH       ( thingHandle->getH (index) );
		setHS      ( thingHandle->getHS(index) );
		setVS      ( thingHandle->getVS(index) );

		thingHandle = nullptr;
		index = 0;
	}
}

/********************************************************************
 * dataMode()
 * 	Sets the mode of the rectangle to data mode. This mode stores
 * 	all the variables on the thing handler instead of private vars.
 * 	The data that is currently on this object
 ********************************************************************/
void Rectangle :: dataMode(ThingHandler * sss, unsigned index) {
	if (normal && sss != nullptr) {
		thingHandle = sss;
		this->index = index;

		thingHandle->setX ( index, getX () );
		thingHandle->setY ( index, getY () );
		thingHandle->setW ( index, getW () );
		thingHandle->setH ( index, getH () );
		thingHandle->setHS( index, getHS() );
		thingHandle->setVS( index, getVS() );

		normal = false; // This has to be last.
	}
}

/********************************************************************
 * isNormalMode()
 * 	Returns true if the rectangle is in normal mode.
 ********************************************************************/
bool Rectangle :: isNormalMode() const {
	return normal;
}

/********************************************************************
 * isDataMode()
 * 	Returns true if the rectangle is in data mode.
 ********************************************************************/
bool Rectangle :: isDataMode  () const {
	return !normal;
}

/********************************************************************
 * setXYWH() setWH() setXY()
 * 	Sets the X, Y, W, and H.
 ********************************************************************/
void Rectangle :: setXYWH(float x, float y, float w, float h) {
	setX(x);
	setY(y);
	setW(w);
	setH(h);
}

void Rectangle :: setWH(float w, float h) {
	setW(w);
	setH(h);
}

void Rectangle :: setXY(float x, float y) {
	setX(x);
	setY(y);
}
