/********************************************************************
 * timer.h
 *		This contains the timer class. One may ask, why do we need a 
 * 	timer class for game development? Many reasons! One big one is
 * 	framerate. If you want to incorporate framerate into your game,
 * 	then you need some sort of timer.
 ********************************************************************/

#ifndef _TIMER_H
#define _TIMER_H

#include "constants.h"

class Timer {
	public:
		Timer();

		void reset();
		void stop();
		void pause();
		void play();

		uint32_t getTicks() const;

	private:
		bool paused;
		uint32_t startTime;
		uint32_t endTime;
};

#endif //_TIMER_H
