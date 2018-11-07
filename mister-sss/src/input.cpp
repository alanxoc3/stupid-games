// input.cpp

#include "input.h"

/*********************************************************************
 * Default Constructor
 *    Initializes the input stuff.
*********************************************************************/
Input :: Input() {
	// Set everything to FALSE.
	quit = 0;
	for (int i = 0; i < SIZE; ++i) {
		keysPressed[i] = 0;
		keysReleased[i] = 0;
		keysDown[i] = 0;
	}

	mPressed = 0;
	mReleased = 0;
	mDown = 0;
	// Coords to zero
	mX = 0;
	mY = 0;
	mMoved = 0;
	mouseFree();
}

/*********************************************************************
 * isQuit()
 *    Returns true if the user quit the program.
*********************************************************************/
bool Input :: isQuit() const {
	return quit;
}

/*********************************************************************
 * down()
 *    Returns true if the key index is held down, false otherwise.
 * 	Asserts if the key is out of range.
*********************************************************************/
bool Input :: down(const int key) const {
	assert(key >= 0 && key < SIZE);
	return keysDown[key];
}

/*********************************************************************
 * released()
 *    Returns true if the key index was released, false otherwise.
 * 	Asserts if the key is out of range.
*********************************************************************/
bool Input :: released(const int key) const {
	assert(key >= 0 && key < SIZE);
	return keysReleased[key];
}

/*********************************************************************
 * pressed()
 *    Returns true if the key index was pressed, false otherwise.
 * 	Asserts if the key is out of range.
*********************************************************************/
bool Input :: pressed(const int key) const {
	assert(key >= 0 && key < SIZE);
	return keysPressed[key];
}

/*********************************************************************
 * update()
 * 	Updates key presses that have taken place. This function should
 * 	be called at the beginning of every frame in order to have the
 * 	most up to date key info.
*********************************************************************/
void Input :: update() {
	clearKeys();

	SDL_Event e;
	int key = -1;
	while(SDL_PollEvent(&e) != 0) {
		key = -1;
		if (e.type == SDL_QUIT) {
			quit = true;
		} else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case 'w': key = KEY_W; break;
				case 'a': key = KEY_A; break;
				case 's': key = KEY_S; break;
				case 'd': key = KEY_D; break;
				case SDLK_ESCAPE: key = KEY_ESC; break;
				case SDLK_SPACE:  key = KEY_SPA; break;
			}

			if (key > -1) {
				if (keysDown[key])
					keysPressed[key] = false;
				else {
					keysPressed[key] = true;
					keysDown[key]    = true;
				}
			}
		} else if (e.type == SDL_KEYUP) {
			switch (e.key.keysym.sym) {
				case 'w': key = KEY_W; break;
				case 'a': key = KEY_A; break;
				case 's': key = KEY_S; break;
				case 'd': key = KEY_D; break;
				case SDLK_ESCAPE: key = KEY_ESC; break;
				case SDLK_SPACE:  key = KEY_SPA; break;
			}

			if (key > -1) {
				keysReleased[key] = true;
				keysDown[key]     = false;
			}
		} else if (e.type == SDL_MOUSEBUTTONDOWN) {
			// Only pressed once, this is for safe keeping.
			if (mDown)
				mPressed = false;
			else {
				mPressed = true;
				mDown    = true;
			}
		} else if (e.type == SDL_MOUSEBUTTONUP) {
			mReleased = true;
			mDown = false;
		} else if (e.type == SDL_MOUSEMOTION) {
			// If the mouse was moved then say it was and set coords.
			mMoved = true;
			SDL_GetMouseState(&mX, &mY);

			// Print coordinates for debugging.
			// std::cout << "X: " << mX << " | Y: " << mY << std::endl;
		}
	}
}

/*********************************************************************
 * clearKeys()
 * 	Clears the key pressed and released buffers (arrays). A private
 * 	function.
*********************************************************************/
void Input :: clearKeys() {
	for (int i = 0; i < SIZE; ++i) {
		keysPressed[i] = 0;
		keysReleased[i] = 0;
	}

	mPressed = false;
	mReleased = false;
	// Assume that mouse was not moved.
	mMoved = false;
}

/******************************************************************** 
 * mouseDown()
 * 	Returns true if the mouse is being held down right now.
 ********************************************************************/
bool Input :: mouseDown() const {
	return mDown;
}

/******************************************************************** 
 * mouseReleased()
 * 	Returns true if the mouse was just released from being down.
 ********************************************************************/
bool Input :: mouseReleased() const {
	return mReleased;
}

/******************************************************************** 
 * mousePressed()
 * 	Returns true if the mouse was just pressed after not being held
 * 	down.
 ********************************************************************/
bool Input :: mousePressed() const {
	return mPressed;
}

/******************************************************************** 
 * mouseX()
 * 	Returns the current x position of the mouse.
 ********************************************************************/
int Input :: mouseX() const {
	return mX;
}

/******************************************************************** 
 * mouseY()
 * 	Returns the current y position of the mouse.
 ********************************************************************/
int Input :: mouseY() const {
	return SCREEN_HEIGHT - mY;
}

/******************************************************************** 
 * mouseCoords()
 * 	Returns the x and y position of the mouse by reference into the
 * 	parameters.
 ********************************************************************/
void Input :: mouseCoords(int & mX, int & mY) const {
	mX = this->mX;
	mY = this->mY;
}

/******************************************************************** 
 * mouseCapture()
 * 	Captures the mouse in the window. When the mouse is captured,
 * 	it is not visible, and it cannot leave the window. Very useful
 * 	feature.
 ********************************************************************/
void Input :: mouseCapture() {
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

/******************************************************************** 
 * mouseFree()
 * 	Uncaptures the mouse from the window. Now the mouse can move
 * 	around the operating system.
 ********************************************************************/
void Input :: mouseFree() {
	SDL_SetRelativeMouseMode(SDL_FALSE);
}

/******************************************************************** 
 * isMouseCaptured()
 * 	Returns true if the mouse is being captured right now, false
 * 	if the mouse is not being captured right now.
 ********************************************************************/
bool Input :: isMouseCaptured() const {
	return SDL_GetRelativeMouseMode() == SDL_TRUE ? true : false;
}

/******************************************************************** 
 * didMouseMove()
 * 	Returns true if the mouse had moved in the last step. False if
 * 	the mouse had not moved in the last step/frame.
 ********************************************************************/
bool Input :: didMouseMove() const {
	return mMoved;
}
