// background.h

#ifndef _BACKGROUND_H
#define _BACKGROUND_H

#include "view.h"
#include "imageHandler.h"
#include "constants.h"

class Background {
	public:
		Background();
		void drawBackground(const View * v);
		~Background();
		void drawThings(const float * viewMatrix, unsigned activeTexture, unsigned width, unsigned height);

	private:
		GLuint vao, vbo, prog, vert, frag;
		ImageHandler * ih;
		void initgl();
		void enditgl();
		void unbind();
};


#endif //_BACKGROUND_H
