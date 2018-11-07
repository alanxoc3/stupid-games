// TIMER.CPP

#include "timer.h"

/********************************************************************
 * Default Constructor
 * 	Initialize stuff.
 ********************************************************************/
Timer :: Timer() {
	paused = true;
	startTime = 0;
	endTime = 0;
}

/********************************************************************
 * reset()
 * 	Restarts the timer and plays it. Same thing as stop then play.
 ********************************************************************/
void Timer :: reset() {
	paused = false;
	startTime = SDL_GetTicks();
}

/********************************************************************
 * stop()
 * 	Restarts the timer and stops it.
 ********************************************************************/
void Timer :: stop() {
	paused = true;
	endTime = startTime;
}

/********************************************************************
 * pause()
 * 	Freezes time, until resumed.
 ********************************************************************/
void Timer :: pause() {
	if (!paused) {
		paused = true;
		endTime = SDL_GetTicks();
	}
}

/********************************************************************
 * play()
 * 	Unfreezes the timer.
 ********************************************************************/
void Timer :: play() {
	if (paused) {
		paused = false;
		startTime = SDL_GetTicks() - (endTime - startTime);
	}
}

/********************************************************************
 * getTicks()
 * 	Returns how long the timer has been going in milliseconds.
 ********************************************************************/
uint32_t Timer :: getTicks() const {
	return (paused ? endTime : SDL_GetTicks()) - startTime;
}

