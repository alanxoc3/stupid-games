// input.h

#ifndef _INPUT_H
#define _INPUT_H

#include "constants.h"

/*********************************************************************
 * input.h
 * 	This file contains the input class for the mister-sss game.
 * 	The input class is responsible for providing a simple way to
 * 	handle user input.
*********************************************************************/
class Input {
	public:
		static const int KEY_W = 0;
		static const int KEY_A = 1;
		static const int KEY_S = 2;
		static const int KEY_D = 3;
		static const int KEY_SPA = 4;
		static const int KEY_ESC = 5;
		static const int SIZE = 6;

		Input();
		bool isQuit() const;

		// Keyboard
		bool down(const int key) const;
		bool released(const int key) const;
		bool pressed(const int key) const;

		// Mouse
		bool mouseDown() const;
		bool mouseReleased() const;
		bool mousePressed() const;
		int mouseX() const;
		int mouseY() const;
		void mouseCoords(int & mX, int & mY) const;
		void mouseCapture();
		void mouseFree();
		bool isMouseCaptured() const;
		bool didMouseMove() const;

		void update();
		
	private:
		bool keysPressed [SIZE];
		bool keysReleased[SIZE];
		bool keysDown[SIZE];
		bool quit;

		int mX, mY;
		bool mPressed, mReleased, mDown;
		bool mMoved;

		void clearKeys();
};

#endif //_INPUT_H
