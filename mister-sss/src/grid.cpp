// grid.cpp

#include "grid.h"

/********************************************************************
 * Default Constructor
 * 	Initializes the grid spaces.
 ********************************************************************/
Grid :: Grid() {
	// Set up my precious defaults.
	clearGrid();
	curRow = 0;
	curCol = 0;
	initDraw();
}

/********************************************************************
 * Destructor
 * 	DESTROY the GL stuff.
 ********************************************************************/
Grid :: ~Grid() {
	enditDraw();
}

/********************************************************************
 * draw()
 * 	Draws the grid. The grid looks similar to a tic-tac-toe board,
 * 	in essence, four lines are drawn across the screen, not across
 * 	the world. This must be drawn last in order for it to be above
 * 	everything else. Here is what it kind of looks like on the
 * 	screen:
 * 	   |   |
 * 	---+---+---
 * 	   |   |
 * 	---+---+---
 * 	   |   |
 ********************************************************************/
void Grid :: draw() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, 8);

	glUseProgram(mprogram);
	glBindVertexArray(mvao);
	glDrawArrays(GL_TRIANGLES, 8, 6);

	unbind();

	//for (int i = 0; i < 3; ++i) {
		//for (int j = 0; j < 3; ++j) {
			//if (gridStates[j][i] == PRESS)
				//g.drawCircle(x1 * j + x1 / 2, y1 * i + y1 / 2, 9, 6);
			//else if (gridStates[j][i] == DOWN)
				//g.drawCircle(x1 * j + x1 / 2, y1 * i + y1 / 2, 5, 6);
			//else if (gridStates[j][i] == SELECT)
				//g.drawCircle(x1 * j + x1 / 2, y1 * i + y1 / 2, 2, 6);
		//}
	//}
}

/********************************************************************
 * update()
 * 	This method is in charge of always keeping the grid up to date.
 * 	It needs info from the mouse in order to do this.
 ********************************************************************/
void Grid :: update(const Input & input) {
	char state = NONE;
	bool same = true;

	// STEP 1 - UPDATE COORDS
	if (input.didMouseMove()) {
		int row = (int) (input.mouseX() / x1);
		int col = (int) (input.mouseY() / y1);

		// Make sure the spaces keep their bounds.
		if (row > 2)
			row = 2;
		else if (row < 0)
			row = 0;

		if (col > 2)
			col = 2;
		else if (col < 0)
			col = 0;

		// DEBUG
		//std::cout << "ROW: " << row << " | COL: " << col << std::endl;
		same = (curRow == row && curCol == col);

		if (!same) {
			curRow = row;
			curCol = col;
		}
	}

	// STEP 2 - FIGURE OUT STATUS
	if (input.mousePressed() && input.mouseDown()) {
		// Reason for the and, if you press a mouse quickly enough,
		// it will release and press in the same turn. When it is
		// released, it will no longer be down. We don't want mouse
		// input to be that quick.
		state = PRESS;
	} else if (input.mouseDown()) {
		if (!same)
			refreshGrid();

		//if (gridStates[curRow][curCol] == SELECT)
			//state = SELECT;
		//else
			//state = DOWN;
		state = DOWN;

	} else if (input.mouseReleased()) {
		clearGrid();
		state = RELEASE;
	} else {
		if (!same)
			clearGrid();
		state = HOVER;
	}

	// STEP 3 - UPDATE GRID
	gridStates[curRow][curCol] = state;

	// STEP 4 - UPDATE TO GL
	glUseProgram(mprogram);
	glUniform2f(glGetUniformLocation(mprogram, "mpos"), input.mouseX(), input.mouseY());
}

/********************************************************************
 * clearGrid()
 * 	Private method, clear the grid array to all have no status.
 ********************************************************************/
void Grid :: clearGrid() {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			gridStates[i][j] = NONE;
}

/********************************************************************
 * refreshGrid()
 * 	Private method, changes PRESS to DOWN, DOWN to SELECT, and
 * 	SELECT to NONE.
 ********************************************************************/
void Grid :: refreshGrid() {
	// If it was pressed last time, it is now down.
	// If it was selected last time, it is still selected.
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j) {
			if (gridStates[i][j] == PRESS)
				gridStates[i][j] = DOWN;
			else if (gridStates[i][j] == DOWN)
				gridStates[i][j] = SELECT;
			else if (gridStates[i][j] != SELECT)
				gridStates[i][j] = NONE;
		}
}

/********************************************************************
 * getState()
 * 	Returns the state of the row and column. Possible states are
 * 	as follows:
 * 	NONE    => mouse has nothing to do with grid space.
 * 	HOVER   => mouse is hovering over the grid space.
 * 	RELEASE => Mouse just released on a space.
 * 	SELECT  => Mouse had been pressed on a space and the
 * 				  key still pressed
 * 	DOWN    => Mouse is being held down on a space.
 * 	PRESS   => mouse just pressed down on a space.
 ********************************************************************/
char Grid :: getState(const unsigned int row,
							 const unsigned int col) const
{
	assert(row >= 0 && row < 3);
	assert(col >= 0 && col < 3);

	return gridStates[row][col];
}

/********************************************************************
 * getOverallState()
 * 	Returns the overall state of the grid. Possible states this
 * 	method may return are: HOVER, RELEASE, DOWN, and PRESS.
 * 	NONE is returned if the grid has never been updated.
 ********************************************************************/
char Grid :: getOverallState(unsigned & xPos, unsigned & yPos) const {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j) {
			switch (gridStates[i][j]) {
				case HOVER: case DOWN: case PRESS: case RELEASE:
					xPos = i;
					yPos = j;
					return gridStates[i][j];
				default: break;
			}
		}

	// Should only return none if the board has never been updated.
	return NONE;
}

void Grid :: enditDraw() {
	glDeleteProgram(program);
	glDeleteShader(vShader);
	glDeleteShader(fShader);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	glDeleteProgram(mprogram);
	glDeleteShader(fMShader);
	glDeleteVertexArrays(1, &mvao);
}

void Grid :: unbind() {
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Grid :: initDraw() {
// STEP 1: Create Shader Programs
	// Vertex/Fragment Shaders
	vShader = createShader(GL_VERTEX_SHADER,   VS_GRID);
	fShader = createShader(GL_FRAGMENT_SHADER, FS_GRID);

	program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);

	glBindFragDataLocation(program, 0, "out_color");
	glLinkProgram(program);

	// Create mouse shader program.
	fVShader = createShader(GL_VERTEX_SHADER, VS_MOUSE);
	fMShader = createShader(GL_FRAGMENT_SHADER, FS_MOUSE);

	mprogram = glCreateProgram();
	glAttachShader(mprogram, fVShader);
	glAttachShader(mprogram, fMShader);

	glBindFragDataLocation(mprogram, 0, "out_color");
	glLinkProgram(mprogram);

	// For debugging.
	printShaderError(vShader,  VS_GRID);
	printShaderError(fShader,  FS_GRID);
	printShaderError(fMShader, FS_MOUSE);

	glUseProgram (program);

// STEP 2: Create Vertex Buffer Object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * LINE_GRID_SIZE, lineGrid, GL_STATIC_DRAW);

// STEP 3: Create Vertex Array Object
	GLuint pos = glGetAttribLocation(program, "pos");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, nullptr);
	glEnableVertexAttribArray(pos);

// STEP 4: Projection Matrix
	float projMatrix[] = {
		2.0f / SCREEN_WIDTH, 0.0f, 0.0f, -1.0f,
		0.0f, 2.0f / SCREEN_HEIGHT, 0.0f, -1.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	// Because the vectors must be horizontal (in arrays), the matrix must be transposed.
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, projMatrix);

// STEP 5: Texture Uniform && Screen Uniform
	// The framebuffer texture is on GL_TEXTURE1
	glUniform1i(glGetUniformLocation(program, "texFrame"), 1);
	glUniform2f(glGetUniformLocation(program, "screen"), SCREEN_WIDTH, SCREEN_HEIGHT);



	// Create the mouse vao without interfering.
	glUseProgram(mprogram);
		GLuint mouseShape = glGetAttribLocation(mprogram, "pos");

		glGenVertexArrays(1, &mvao);
		glBindVertexArray(mvao);

		glVertexAttribPointer(mouseShape, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, nullptr);
		glEnableVertexAttribArray(mouseShape);

		glUniformMatrix4fv(glGetUniformLocation(mprogram, "proj"), 1, GL_TRUE, projMatrix);

	printGLError();
	unbind();
}
