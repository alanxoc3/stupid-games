/********************************************************************
 * view.cpp
 * 	The view class is in charge of drawing the game relative to
 * 	the world, aka the view. Kind of like looking through
 * 	binoculars, you only see a little bit at a time. The difference
 * 	is that this is rectangular and not zoomed in.
 ********************************************************************/
#include "view.h"

/********************************************************************
 * Default Constructor
 ********************************************************************/
View :: View() {
	rect.setX(0);
	rect.setY(0);
	rect.setW(RENDER_WIDTH);
	rect.setH(RENDER_HEIGHT);

	pushBox.setX(0);
	pushBox.setY(0);
	pushBox.setW(rect.getW() / 3);
	pushBox.setH(rect.getH() / 3);

	// The identity matrix :)
	for(unsigned i = 0; i < MATRIX_SIZE; ++i)
		viewMatrix[i] = ((i % 5) ? 0.0f : 1.0f);
}

/********************************************************************
 * center()
 * 	Centers the view around the parameters. If useBox is true, then
 * 	the view is centered, with the thing pushing an invisible
 * 	bounding box.
 ********************************************************************/
void View :: center(const float xCenter, float yCenter, bool useBox) {
	if (!useBox) {
		pushBox.setX(xCenter - pushBox.getW() / 2); pushBox.setY(yCenter - pushBox.getH() / 2);
	} else {
		if (xCenter < pushBox.getX())
			pushBox.setX(xCenter);
		if (xCenter > pushBox.getX() + pushBox.getW())
			pushBox.setX(xCenter - pushBox.getW());

		if (yCenter < pushBox.getY())
			pushBox.setY(yCenter);
		if (yCenter > pushBox.getY() + pushBox.getH())
			pushBox.setY(yCenter - pushBox.getH());
	}

	centerViewToPushBox();
	updateViewMatrix();
}

/********************************************************************
 * center()
 * 	Centers the view to the rectangle. Yes, width and height are
 * 	accounted for. If useBox is true, then the view is centered,
 * 	with the thing pushing an invisible bounding box.
 ********************************************************************/
void View :: center(const Rectangle & cRect, bool useBox) {
	if (!useBox) {
		pushBox.setX(cRect.getX() + cRect.getW() / 2 - pushBox.getW() / 2);
		pushBox.setY(cRect.getY() + cRect.getH() / 2 - pushBox.getH() / 2);
	} else {
		if (cRect.getX() < pushBox.getX())
			pushBox.setX(cRect.getX());
		if (cRect.getX() + cRect.getW() > pushBox.getX() + pushBox.getW())
			pushBox.setX(cRect.getX() + cRect.getW() - pushBox.getW());

		if (cRect.getY()< pushBox.getY())
			pushBox.setY(cRect.getY());
		if (cRect.getY() + cRect.getH() > pushBox.getY() + pushBox.getH())
			pushBox.setY(cRect.getY() + cRect.getH() - pushBox.getH());
	}

	centerViewToPushBox();
	updateViewMatrix();
}

/********************************************************************
 * centerViewToPushBox()
 * 	Centers the view box to the push box.
 ********************************************************************/
void View :: centerViewToPushBox() {
	rect.setX(pushBox.getCX() - rect.getW() / 2);
	rect.setY(pushBox.getCY() - rect.getH() / 2);
}

/********************************************************************
 * setX()
 * 	Sets the left edge of the view.
 ********************************************************************/
void View :: setX(const float xPos) {
	rect.setX(xPos);
}

/********************************************************************
 * setY()
 * 	Sets the bottom edge of the view.
 ********************************************************************/
void View :: setY(const float yPos) {
	rect.setY(yPos);
}

/********************************************************************
 * getX()
 * 	Returns the x position of the view.
 ********************************************************************/
float View :: getX() const {
	return rect.getX();
}

/********************************************************************
 * getY()
 * 	Returns the y position of the view.
 ********************************************************************/
float View :: getY() const {
	return rect.getY();
}

/********************************************************************
 * getW()
 * 	Returns the width of the view, or the screen width.
 ********************************************************************/
float View :: getW() const {
	// Contained in constants.h
	return rect.getW();
}

/********************************************************************
 * getH()
 * 	Returns the height of the view, or the screen height.
 ********************************************************************/
float View :: getH() const {
	// Contained in constants.h
	return rect.getH();
}

/********************************************************************
 * getRect()
 * 	Returns the rectangle that represents the view. May be used
 * 	for checking collision with the view.
 ********************************************************************/
const Rectangle & View :: getRect() const {
	return rect;
}

/********************************************************************
 * getPushBox()
 * 	Returns the rectangle that represents the thing pushing the
 * 	view.
 ********************************************************************/
const Rectangle & View :: getPushBox() const {
	return pushBox;
}

/********************************************************************
 * setPushBox()
 * 	Sets the rectangle that represents the thing pushing the view.
 ********************************************************************/
void View :: setPushBox(const Rectangle & newRect) {
	pushBox = newRect;
}

/********************************************************************
 * updateViewMatrix()
 * 	Updates the view matrix according to the rectangle of view.
 * 	This is a helper method for the view class and should be called
 * 	at the end of any method changing the view rectangle.
 ********************************************************************/
void View :: updateViewMatrix() {
	viewMatrix[3] = -rect.getX();
	viewMatrix[7] = -rect.getY();
}

/********************************************************************
 * getViewMatrix()
 * 	Returns the view matrix. Note that this matrix cannot be
 * 	changed, because it is a pointer, pointing to the same matrix
 * 	this class uses. The matrix is NOT transposed. You should have
 * 	it transposed if it is going into Open GL.
 ********************************************************************/
const float * const View :: getViewMatrix() const {
	return viewMatrix;
}
