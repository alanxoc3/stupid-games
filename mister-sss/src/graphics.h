/*********************************************************************
 * Graphics
 * 	This class has three responsibilities. ONE: Provide a layer
 * 	between SDL and the application, a wrapper. TWO: Make setting
 * 	up some things in open gl, but not handling open gl for the
 * 	application. THREE: Image loading. Note that no GL things are
 * 	bound after a function, they are just tediously created.
*********************************************************************/

#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include "constants.h"

class Graphics {
	public:
		Graphics();
		~Graphics();

		bool init();
		void endit();

		void update();
		void sleep(int milliseconds) const;

		void createFrameBuffer(const char vertFile[], const char fragFile[]);

		void beginFrameBuffer();
		void endFrameBuffer();
		void deleteFrameBuffer();

	private:
		SDL_Window * win;
		SDL_Renderer * ren;
		SDL_GLContext con;

		GLuint fb, ft, fr, fvao, fvbo, febo, fvert, ffrag, fprogram;
};

#endif // _GRAPHICS_H
