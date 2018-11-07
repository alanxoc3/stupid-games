/*********************************************************************
 * view.h
 * 	This file contains the View class for the Mister-SSS game.
 * 	The view class controls what is seen on the screen. A separate
 * 	coordinate system from all the other objects is used. You may
 * 	set the width, height, and coordinates of the view port. You may
*********************************************************************/

#ifndef _VIEW_H
#define _VIEW_H

#include "constants.h"
#include "graphics.h"
#include "rectangle.h"

class View {
	public:
		View();

		void center(const float xCenter, float yCenter, bool useBox = false);
		void center(const Rectangle & cRect, bool useBox = false);

		void setX(const float xPos);
		void setY(const float yPos);

		// GETTERS
		Graphics * getGraphics();
		float getX() const;
		float getY() const;
		float getW() const;
		float getH() const;

		const Rectangle & getRect() const;
		const Rectangle & getPushBox() const;
		void setPushBox(const Rectangle & newRect);

		const float * const getViewMatrix() const;

	private:
		Rectangle rect, pushBox;
		static const int MATRIX_SIZE = 4 * 4;
		float viewMatrix [MATRIX_SIZE];
		void centerViewToPushBox();
		void updateViewMatrix();
};


#endif //_VIEW_H
