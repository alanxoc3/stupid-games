/********************************************************************
 * grid.h
 * 	The grid class handles mouse input with the grid and can
 * 	display the grid.
 ********************************************************************/

#ifndef _GRID_H
#define _GRID_H

#include "constants.h"
#include "rectangle.h"
#include "input.h"
#include "helperGL.h"

#define LINE_GRID_SIZE 28

class Grid {
	public:
		// Guideline for grid statuses (below).
		static const char NONE    = 0; // None    => No mouse.
		static const char HOVER   = 1; // Hover   => Mouse is hovering
		static const char RELEASE = 2; // Release => Mouse is releasing
		static const char SELECT  = 3; // Select  => Mouse had touched and is still down
		static const char DOWN    = 4; // Down    => Mouse is down
		static const char PRESS   = 5; // Press   => Mouse is being pressed (and down)

		static const unsigned R0 = 1;
		static const unsigned R1 = 2;
		static const unsigned R2 = 3;

		static const unsigned C0 = 4;
		static const unsigned C1 = 5;
		static const unsigned C2 = 6;

		Grid();
		~Grid();

		char getState(const unsigned int row,
						  const unsigned int col) const;

		char getOverallState(unsigned & xPos, unsigned & yPos) const;

		void draw();
		void update(const Input & input);

	private:
		void initDraw();
		void enditDraw();
		void unbind();

		void refreshGrid();
		void clearGrid();
		char gridStates[3][3];
		int curRow, curCol;

		// Grid bounds. Rectangles and lines may be constructed out of these.
		// Looks like: (3x3 grid)
		unsigned program, vbo, vao, fShader, vShader, mprogram, fMShader, mvao, fVShader;

		const float x0 = 0;
		const float y0 = 0;

		const float x1 = SCREEN_WIDTH / 3;
		const float y1 = SCREEN_HEIGHT / 3;

		const float x2 = x1 * 2;
		const float y2 = y1 * 2;

		const float x3 = SCREEN_WIDTH;
		const float y3 = SCREEN_HEIGHT;

		const float lineGrid[LINE_GRID_SIZE] = {
			x1, y0, x1, y3,
			x2, y0, x2, y3,
			x0, y1, x3, y1,
			x0, y2, x3, y2,
		// MOUSE
			-3.0f, -3.0f,
			-3.0f,  3.0f,
			 3.0f, -3.0f,

			-3.0f,  3.0f,
			 3.0f,  3.0f,
			 3.0f, -3.0f
		};
};

#endif //_GRID_H
