// sssThingHandler.cpp

// Work on drawing.

#include "thingHandler.h" 
#include "helperGL.h"

/********************************************************************
 * Various Getters
 * 	Due to somewhat lazy and efficient documentation, here are
 * 	various getters, namely:
 * 	X, Y, Width, Height, Horizontal Speed, Vertical Speed,
 * 	image Center X, image Center Y, Image, Hit Points,
 * 	Max Hitpoints.
 * 	Index is the value pointer thing
 ********************************************************************/
// The numbers inside here are the locations in the array. Useful to know when adding onto this class.
const GLfloat & ThingHandler :: getX   (const GLuint & index) const { return getPosOff(index, 1); }
const GLfloat & ThingHandler :: getY   (const GLuint & index) const { return getPosOff(index, 2); }

const GLfloat & ThingHandler :: getZ   (const GLuint & index) const { return getPosOff(index, 3); }

const GLfloat & ThingHandler :: getW   (const GLuint & index) const { return getPosOff(index, 4); }
const GLfloat & ThingHandler :: getH   (const GLuint & index) const { return getPosOff(index, 5); }
const GLfloat & ThingHandler :: getHS  (const GLuint & index) const { return getPosOff(index, 6); }
const GLfloat & ThingHandler :: getVS  (const GLuint & index) const { return getPosOff(index, 7); }

const GLfloat & ThingHandler :: getIX  (const GLuint & index) const { return getPosOff(index, 8); }
const GLfloat & ThingHandler :: getIY  (const GLuint & index) const { return getPosOff(index, 9); }
const GLfloat & ThingHandler :: getIW  (const GLuint & index) const { return getPosOff(index, 10); }
const GLfloat & ThingHandler :: getIH  (const GLuint & index) const { return getPosOff(index, 11); }
const GLfloat & ThingHandler :: getOFFX(const GLuint & index) const { return getPosOff(index, 12); }
const GLfloat & ThingHandler :: getOFFY(const GLuint & index) const { return getPosOff(index, 13); }

const GLfloat & ThingHandler :: getHP  (const GLuint & index) const { return getPosOff(index, 14); }
const GLfloat & ThingHandler :: getMH  (const GLuint & index) const { return getPosOff(index, 15); }

/********************************************************************
 * isHPEnabled
 * 	Returns true if, when drawn, the shader draws the object's
 * 	health at all.
 ********************************************************************/
const GLboolean ThingHandler :: isHPEnabled(const GLuint & index) const {
	return (getPosOff(index, 0) > 10.0f);
}

/********************************************************************
 * Various Setters
 * 	Due to somewhat lazy and efficient documentation, here are
 * 	various getters, namely:
 * 	X, Y, Width, Height, Horizontal Speed, Vertical Speed,
 * 	image Center X, image Center Y, Image, Hit Points,
 * 	Max Hitpoints.
 * 	Index is the object pointer thing, and val it the value to set.
 ********************************************************************/
void ThingHandler :: setX   (const GLuint & index, const GLfloat & val) { setPosOff(index, 1, val); }
void ThingHandler :: setY   (const GLuint & index, const GLfloat & val) { setPosOff(index, 2, val); }

void ThingHandler :: setZ   (const GLuint & index, const GLfloat & val) { setPosOff(index, 3, val); }

void ThingHandler :: setW   (const GLuint & index, const GLfloat & val) { setPosOff(index, 4, val); }
void ThingHandler :: setH   (const GLuint & index, const GLfloat & val) { setPosOff(index, 5, val); }
void ThingHandler :: setHS  (const GLuint & index, const GLfloat & val) { setPosOff(index, 6, val); }
void ThingHandler :: setVS  (const GLuint & index, const GLfloat & val) { setPosOff(index, 7, val); }

void ThingHandler :: setIX  (const GLuint & index, const GLfloat & val) { setPosOff(index, 8, val); }
void ThingHandler :: setIY  (const GLuint & index, const GLfloat & val) { setPosOff(index, 9, val); }
void ThingHandler :: setIW  (const GLuint & index, const GLfloat & val) { setPosOff(index, 10, val); }
void ThingHandler :: setIH  (const GLuint & index, const GLfloat & val) { setPosOff(index, 11, val); }
void ThingHandler :: setOFFX(const GLuint & index, const GLfloat & val) { setPosOff(index, 12, val); }
void ThingHandler :: setOFFY(const GLuint & index, const GLfloat & val) { setPosOff(index, 13, val); }

void ThingHandler :: setHP  (const GLuint & index, const GLfloat & val) { setPosOff(index, 14, val); }
void ThingHandler :: setMH  (const GLuint & index, const GLfloat & val) { setPosOff(index, 15, val); }

/********************************************************************
 * enableHP disableHP
 * 	Enables or disables the drawing of the HP, passed to the shader.
 ********************************************************************/
void ThingHandler :: enableHP (const GLuint & index) {
	// Note that if visible index is greater than 10, then hp is drawn.
	if (getPosOff(index, 0) > 0.0f)
		setPosOff(index, 0, 11.0f);
}

void ThingHandler :: disableHP(const GLuint & index) {
	// If visible index is less than 10, then hp is not.
	if (getPosOff(index, 0) > 0.0f)
		setPosOff(index, 0, 1.0f);
}

/********************************************************************
 * getPosOff()
 * 	Drives all the getters, a simple way to access elements in the
 * 	array. Each attribute has a unique offset. Position Offset
 ********************************************************************/
const GLfloat & ThingHandler :: getPosOff(const GLuint & index, const GLuint & offset) const {
	if (index * LINE_SIZE >= capacity * LINE_SIZE)
		throw std::runtime_error("Trying to access out of the array, taunting a seg fault.");

	return thingGrid[index * LINE_SIZE + offset];
}

/********************************************************************
 * setPosOff()
 * 	Drives all the setters. See getPosOff().
 ********************************************************************/
void ThingHandler :: setPosOff(const GLuint & index, const GLuint & offset, const GLfloat & val) {
	if (index * LINE_SIZE >= capacity * LINE_SIZE)
		throw std::runtime_error("Trying to access out of the array, taunting a seg fault.");

	thingGrid[index * LINE_SIZE + offset] = val;
}

/********************************************************************
 * Constructor
 * 	Initializes capacity. Can't change capacity without a reset.
 ********************************************************************/
ThingHandler :: ThingHandler(GLuint capacity) {
	this->capacity = capacity;
	thingGrid = new GLfloat[capacity * LINE_SIZE];
	// Everything is available to be added on start.
	for (GLuint i = 0; i < this->capacity * LINE_SIZE; ++i) {
		if (i % LINE_SIZE == 0) {
			availableSpots.push(i / LINE_SIZE);
			thingGrid[i] = -1.0f;
		} else {
			thingGrid[i] = 0.0f;
		}
	}
	
	// For TFBK output buffer. Note that the array is dynamically allocated.
	feedData = new GLfloat[capacity * TBO_LINE_SIZE];
	// Init array to ZEROS -- for debugging purposes mainly.
	for (GLuint i = 0; i < capacity * TBO_LINE_SIZE; ++i)
		feedData[i] = 0.0f;

	// Needs the capacity set! Keep these at the bottom!
	initTBO();
	initDraw();
}

/********************************************************************
 * Destructor
 * 	Deallocates the array.
 ********************************************************************/
ThingHandler :: ~ThingHandler() {
	delete [] thingGrid;
	delete [] feedData;
	thingGrid = 0;
	feedData = 0;
	capacity = 0;
	enditTBO();
	enditDraw();
}

/********************************************************************
 * reset()
 * 	Deallocates the array, and creates a new one with the indicated
 * 	capacity. NOTE: if the capacity is the same, then the array
 * 	will STILL be reallocated.
 ********************************************************************/
void ThingHandler :: reset(GLuint capacity) {
	// Almost identical to the constructor. See constructor.
	this->capacity = capacity;
	delete [] thingGrid;
	// Reset the queue.
	availableSpots = std::queue<GLuint>();

	thingGrid = new GLfloat[capacity * LINE_SIZE];

	for (GLuint i = 0; i < this->capacity * LINE_SIZE; ++i) {
		if (i % LINE_SIZE == 0) {
			availableSpots.push(i / LINE_SIZE);
			thingGrid[i] = -1.0f;
		} else {
			thingGrid[i] = 0.0f;
		}
	}

	// Now update feedData
	delete [] feedData;
	feedData = new GLfloat[capacity * TBO_LINE_SIZE];

	for (GLuint i = 0; i < this->capacity * TBO_LINE_SIZE; ++i)
		feedData[i] = 0.0f;

	// And finally, update GL.
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, capacity * LINE_SIZE     * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, capacity * TBO_LINE_SIZE * sizeof(GLfloat), nullptr,  GL_DYNAMIC_READ);

	unbind();
}

/********************************************************************
 * removeThing()
 * 	Removes an index from the array. If the index already doesn't
 * 	exist, exception is thrown. The index may be zero. This method
 * 	will not change the parameter.
 ********************************************************************/
void ThingHandler :: removeThing(const GLuint & index) {
	// If the first spot is negative, then the item is already not in
	// the array.
	GLboolean outOfArray = getPosOff(index, 0) < 0.0f;
	// Not out of array means in the array.
	if (!outOfArray) {
		// negative on first position means not alive.
		setPosOff(index, 0, -1.0f);
		// Set all the spots to zero
		for (GLuint i = 1; i < LINE_SIZE; ++i)
			thingGrid[index + i] = 0.0f;
		// When you remove a thing, that thing is now available.
		availableSpots.push(index);
	} else {
		throw std::runtime_error("Trying to remove from empty array.");
	}
}

/********************************************************************
 * addThing()
 * 	Adds a things to the array. If the array is full, then nothing
 * 	happens. The data initialized may be provided in the parameters.
 * 	If a parameter is left empty, then 0 is entered into that
 * 	attribute. Leave empty if using for a rectangle or image's data
 * 	mode.
 ********************************************************************/
GLuint ThingHandler :: addThing( const GLfloat & x, const GLfloat & y, const GLfloat & z, 
			const GLfloat & w , const GLfloat & h , const GLfloat & hs, const GLfloat & vs,
			const GLfloat & ix, const GLfloat & iy, const GLfloat & iw, const GLfloat & ih,
			const GLfloat & ox, const GLfloat & oy, const GLfloat & hp, const GLfloat & mh )
{
	// Remember, availableSpots is a queue.
	if (availableSpots.empty()) {
		// If it is empty, that means the array is full.
		throw std::runtime_error("Trying to add to a full array.");
	}

	GLuint index = availableSpots.front();
	assert( getPosOff(index, 0) < 0.0f );
	availableSpots.pop();

	setPosOff(index,  0, 1.0f);
	setX   (index, x);
	setY   (index, y);

	setZ   (index, ix);

	setW   (index, w);
	setH   (index, h);
	setHS  (index, hs);
	setVS  (index, vs);

	setIX  (index, ix);
	setIY  (index, iy);
	setIW  (index, iw);
	setIH  (index, ih);
	setOFFX(index, ox);
	setOFFY(index, oy);

	setHP  (index, hp);
	setMH  (index, mh);

	return index;
}

/********************************************************************
 * updatePositions()
 * 	Using transform feedback in Open GL, uses the graphics card
 * 	to compute new positions and speeds based on hs, vs, x, & y.
 ********************************************************************/
void ThingHandler :: updatePositions() {
// STEP 1: BIND THINGS
	glUseProgram(tbprogram);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(tvao);

// STEP 2: Update Buffer
	// Target Offset Size Data
	glBufferSubData(GL_ARRAY_BUFFER, 0, capacity * LINE_SIZE * sizeof(GLfloat), thingGrid);

// STEP 3: Execute Shader
	glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, query);
		glEnable(GL_RASTERIZER_DISCARD);
			glBeginTransformFeedback(GL_POINTS);
				glDrawArrays(GL_POINTS, 0, capacity);
			glEndTransformFeedback();
		glDisable(GL_RASTERIZER_DISCARD);
	glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);

	GLuint primitives = 0;
	glGetQueryObjectuiv(query, GL_QUERY_RESULT, &primitives);

// STEP 4: Update Array
	// Type, offset, size, data
	glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, capacity * TBO_LINE_SIZE * sizeof(GLfloat), feedData);

	// Copy feed data values into thingGrid.
	for (GLuint i = 0; i < capacity; ++i) {
		setX (i, feedData[i * TBO_LINE_SIZE + 0]);
		setY (i, feedData[i * TBO_LINE_SIZE + 1]);
	}

// STEP 5: Update Buffer again.
	glBufferSubData(GL_ARRAY_BUFFER, 0, capacity * LINE_SIZE * sizeof(GLfloat), thingGrid);

	unbind();
}

/********************************************************************
 * drawThings()
 * 	Using shaders/open gl, the things are drawn, along with health
 * 	(if health is enabled), and their image number. Make sure
 * 	the correct images are bound to the correct texture buffer
 * 	before a call to this method. The things are drawn within view.
 * 	The active texture is the texture buffer that contains the
 * 	sprite sheet.
 ********************************************************************/
void ThingHandler :: drawThings(const float * viewMatrix, unsigned activeTexture, unsigned width, unsigned height) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(dvao);
	glUseProgram(dprogram);

	// Set the view and active texture uniforms.
	glUniform1i(glGetUniformLocation(dprogram, "Sheet"), activeTexture);
	glUniform2f(glGetUniformLocation(dprogram, "SHEET_DIM"), (float) width, (float) height);
	glUniformMatrix4fv(glGetUniformLocation(dprogram, "view"), 1, GL_TRUE, viewMatrix);
	glUniform1i(glGetUniformLocation(dprogram, "IsHealth"), 0); // Disabled

	glDrawArrays(GL_POINTS, 0, capacity);

	glUniform1i(glGetUniformLocation(dprogram, "IsHealth"), 1); // Enabled .. Red.
	glDrawArrays(GL_POINTS, 0, capacity);

	glUniform1i(glGetUniformLocation(dprogram, "IsHealth"), 2); // Enabled .. Green.
	glDrawArrays(GL_POINTS, 0, capacity);

	unbind();
}

/********************************************************************
 * initTBO()
 * 	A helper function, sets up a vertex array object, buffer object
 * 	for the array, buffer object for transform feedback, and a
 * 	shader program with transform feedback set up. Everything bound
 * 	in Open GL is unbound at the end of this method. Note that the
 * 	following vars need to be in your TF vertex shader:
 * 	in vec2 vel;
 * 	in vec2 pos;
 * 	out vec2 POS;
 ********************************************************************/
void ThingHandler :: initTBO() {
// STEP 1: Create Feedback Shader Program
	glGenQueries(1, &query);
	// No fragment shader here, Vertex Shader updates positions.
	thandle = createShader(GL_VERTEX_SHADER, VS_TRANS_FDBK);
	tbprogram = glCreateProgram();
	glAttachShader(tbprogram, thandle);
	// This is needed for transform feedback, before linking.
	// The interleaved attribs means put all the primitive outputs in the same array.
	const GLchar * feedbackVaryings[] = { "POS" };
	glTransformFeedbackVaryings(tbprogram, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);

	glLinkProgram(tbprogram);
	glUseProgram (tbprogram);

// STEP 2: Create Feedback Buffer Object
	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	
	// Set up the transform feedback buffer object stuff, tfbos isa fla!
	glBufferData(GL_ARRAY_BUFFER, capacity * TBO_LINE_SIZE * sizeof(GLfloat), nullptr, GL_DYNAMIC_READ);
	// Bound to the zeroeth transform feedback buffer.
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);

// STEP 3: Create Buffer Object / Vertex Array Object
	GLuint pos = glGetAttribLocation(tbprogram, "pos");
	GLuint vel = glGetAttribLocation(tbprogram, "vel");

	glGenBuffers(1, &vbo); glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, capacity * LINE_SIZE * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);

	glGenVertexArrays(1, &tvao);
	glBindVertexArray(tvao);

	glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE,
			sizeof(GLfloat) * LINE_SIZE,
			(void *) (sizeof(GLfloat) * 1) );

	glVertexAttribPointer(vel, 2, GL_FLOAT, GL_FALSE,
			sizeof(GLfloat) * LINE_SIZE,
			(void *) (sizeof(GLfloat) * 6) );

	glEnableVertexAttribArray(pos);
	glEnableVertexAttribArray(vel);

	unbind();
}

/********************************************************************
 * enditTBO()
 * 	Removes all the things created in initTBO from the graphics
 * 	card. And removes the feedData array.
 ********************************************************************/
void ThingHandler :: enditTBO() {
	glDeleteQueries(1, &query);
	glDeleteBuffers(1, &tbo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &tvao);

	glDeleteProgram(tbprogram);
	glDeleteShader(thandle);
}

/********************************************************************
 * unbind()
 * 	Unbinds buffer on the graphics card that could have been bound
 * 	this object. And unbinds the program.
 ********************************************************************/
void ThingHandler :: unbind() {
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);
}

/********************************************************************
 * initDraw()
 * 	A helper method. Sets up the shader program and VAO for the
 * 	drawing aspect of the things.
 * 	The following vars must be in your drawing vertex shader:
 * 	in float type;
 * 	in vec2 pos;
 * 	in vec2 dim;
 * 	in vec2 img_ctr;
 * 	in float hp;
 * 	in float max_hp;
 ********************************************************************/
void ThingHandler :: initDraw() {
// STEP 1: Create Graphics Shader Program
	// Vertex, Fragment, and Geometry shaders here.
	dVShader = createShader(GL_VERTEX_SHADER,   VS_THING_DRAW);
	dFShader = createShader(GL_FRAGMENT_SHADER, FS_THING_DRAW);
	dGShader = createShader(GL_GEOMETRY_SHADER, GS_THING_DRAW);

	dprogram = glCreateProgram();
	glAttachShader(dprogram, dVShader);
	glAttachShader(dprogram, dFShader);
	glAttachShader(dprogram, dGShader);

	glBindFragDataLocation(dprogram, 0, "out_color");
	glLinkProgram(dprogram);
	glUseProgram (dprogram);
	// For debugging.
	printShaderError(dVShader, VS_THING_DRAW);
	printShaderError(dFShader, FS_THING_DRAW);
	printShaderError(dGShader, GS_THING_DRAW);

// STEP 2: Create Vertex Array Object
	GLuint type   = glGetAttribLocation(dprogram, "type");
	GLuint pos    = glGetAttribLocation(dprogram, "pos");
	GLuint dim    = glGetAttribLocation(dprogram, "dim");
	GLuint imgCtr = glGetAttribLocation(dprogram, "img_ctr");
	GLuint imgDim = glGetAttribLocation(dprogram, "img_dim");
	GLuint imgOff = glGetAttribLocation(dprogram, "img_off");
	GLuint hp     = glGetAttribLocation(dprogram, "hp");
	GLuint maxHP  = glGetAttribLocation(dprogram, "max_hp");

	// Vertex Array -- Need to have buffer set up in another function (in initTBO now)
	// Buffer must be bound in order for glVertexAttribPointer to work.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glGenVertexArrays(1, &dvao);
	glBindVertexArray(dvao);

	glVertexAttribPointer(type,   1, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * LINE_SIZE,
			nullptr);

	glVertexAttribPointer(pos,    3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * LINE_SIZE,
			(void *) (sizeof(GLfloat) * 1) );

	glVertexAttribPointer(dim,    2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * LINE_SIZE,
			(void *) (sizeof(GLfloat) * 4) );

	glVertexAttribPointer(imgCtr, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * LINE_SIZE,
			(void *) (sizeof(GLfloat) * 8));

	glVertexAttribPointer(imgDim, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * LINE_SIZE,
			(void *) (sizeof(GLfloat) * 10));

	glVertexAttribPointer(imgOff, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * LINE_SIZE,
			(void *) (sizeof(GLfloat) * 12));

	glVertexAttribPointer(hp    , 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * LINE_SIZE,
			(void *) (sizeof(GLfloat) * 14));

	glVertexAttribPointer(maxHP , 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * LINE_SIZE,
			(void *) (sizeof(GLfloat) * 15));

	glEnableVertexAttribArray(type);
	glEnableVertexAttribArray(pos);
	glEnableVertexAttribArray(dim);
	glEnableVertexAttribArray(imgCtr);
	glEnableVertexAttribArray(imgDim);
	glEnableVertexAttribArray(imgOff);
	glEnableVertexAttribArray(hp);
	glEnableVertexAttribArray(maxHP);

// STEP 3: Set up projection matrix
	float projMatrix[] = {
		2.0f / SCREEN_WIDTH, 0.0f, 0.0f, -1.0f,
		0.0f, 2.0f / SCREEN_HEIGHT, 0.0f, -1.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	// Because the vectors must be horizontal (in arrays), the matrix must be transposed.
	glUniformMatrix4fv(glGetUniformLocation(dprogram, "proj"), 1, GL_TRUE, projMatrix);

// STEP 4: Set up a couple more uniforms.
	glUniform1f(glGetUniformLocation(dprogram, "green_z"), Z_GREEN);
	glUniform1f(glGetUniformLocation(dprogram, "red_z"),   Z_RED);

	printGLError();
	unbind();
}

void ThingHandler :: enditDraw() {
	glDeleteShader(dVShader);
	glDeleteShader(dFShader);
	glDeleteShader(dGShader);
	glDeleteProgram(dprogram);
	glDeleteVertexArrays(1, &dvao);
}
