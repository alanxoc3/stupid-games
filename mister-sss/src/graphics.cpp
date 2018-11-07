// graphics.cpp

#include "graphics.h"
#include <iostream>
#include <cmath>
#include "helperGL.h"

/*********************************************************************
 * Constructor
 * 	Initializes the graphics.
*********************************************************************/
Graphics :: Graphics() {
	// stubbed
	win = nullptr;
	ren = nullptr;
	con = nullptr;
	fb = 0;
	ft = 0;
	fr = 0;

	fvao = 0;
	fvbo = 0;
	febo = 0;

	fvert = 0;
	ffrag = 0;
	fprogram = 0;
}

/*********************************************************************
 * Destructor
 * 	Destroys the graphics.
*********************************************************************/
Graphics :: ~Graphics() {
	endit();
}

/*********************************************************************
 * update()
 * 	Updates the graphics, so that the changes now appear on the
 * 	screen.
*********************************************************************/
void Graphics :: update() {
	SDL_GL_SwapWindow(win);
}

/*********************************************************************
 * sleep()
 * 	The graphics sleep for the time in milliseconds given in the
 * 	parameter.
*********************************************************************/
void Graphics :: sleep(int milliseconds) const {
	SDL_Delay(milliseconds);
}

/*********************************************************************
 * init()
 * 	Sets up the SDL part of the application. Returns true if it
 * 	fails. The SDL component is in charge of creating the window,
 * 	loading things, keyboard and mouse input, sound. Also enables
 * 	GL_DEPTH_TEST.
*********************************************************************/
bool Graphics :: init() {

	// Video includes sdl initialization for video and input.
	// Like an SDL constructor.
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Deprecated functions are disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// Using open gl 3.2
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	win = SDL_CreateWindow(
		SSS_TITLE,                  // constants.h
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,           // constants.h
		SCREEN_HEIGHT,          // constants.h
		SDL_WINDOW_OPENGL
	);

	if (win == nullptr) {
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	// The context is basically what sets up the operating system specific
	// things Open GL needs to have set up.
	con = SDL_GL_CreateContext(win);
	if (con == nullptr) {
		SDL_DestroyWindow(win);
		std::cerr<< "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}


	// Used for more up to date open gl functionality
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);

	printGLError();
	return 0;
}

/********************************************************************
 * createFrameBuffer()
 * 	Creates a frame buffer with a texture and depth/stencil buffer.
 * 	The shaders used are defined by the files given. The shader
 * 	must have these specifications:
 * 	VERTEX SHADER:
 * 	in vec2 pos; // triangle point positions.
 * 	in vec2 tex; // Texture Coordinates
 * 	out vec2 TEX; // Texture Coordinates
 *
 * 	FRAGMENT SHADER:
 * 	in vec2 TEX; // Texture Coordinates
 * 	out vec4 outColor; // output color
 * 	uniform sampler2D fbTex; // frame buffer texture.
 * 	Also, a useful thing to know, the FrameBuffer's textures is
 * 	stored on the active TEXTURE1
 ********************************************************************/
void Graphics :: createFrameBuffer(const char vertFile[], const char fragFile[])
{
	// Shader program.
	fvert = createShader(GL_VERTEX_SHADER, vertFile);
	ffrag = createShader(GL_FRAGMENT_SHADER, fragFile);
	fprogram = glCreateProgram();
	glAttachShader(fprogram, fvert);
	glAttachShader(fprogram, ffrag);
	glLinkProgram(fprogram);
	glUseProgram(fprogram);

	// Frame Buffer
	glGenFramebuffers(1, &fb);
	glBindFramebuffer(GL_FRAMEBUFFER, fb);

	// Frame buffers need textures for color.
	glGenTextures(1, &ft);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, ft);

	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA, RENDER_WIDTH, RENDER_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL
	);

	glFramebufferTexture2D(
		GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ft, 0
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// And frame buffers need textures for depth and stenciling.
	glGenRenderbuffers(1, &fr);
	glBindRenderbuffer(GL_RENDERBUFFER, fr);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, RENDER_HEIGHT, RENDER_WIDTH);

	glFramebufferRenderbuffer(
		GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fr
	);
	glActiveTexture(GL_TEXTURE0);

	// Unbind  stuff

	GLfloat quad[] = {
		-1.0f,  1.0f, 0.0f, 1.0f, // TL
		 1.0f,  1.0f, 1.0f, 1.0f, // TR
		 1.0f, -1.0f, 1.0f, 0.0f, // BR
		-1.0f, -1.0f, 0.0f, 0.0f  // BL
	};

	glGenVertexArrays(1, &fvao);
	glBindVertexArray(fvao);

	glGenBuffers(1, &fvbo);
	glBindBuffer(GL_ARRAY_BUFFER, fvbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

	GLuint fposAtt = glGetAttribLocation(fprogram, "pos");
	glEnableVertexAttribArray(fposAtt);
	glVertexAttribPointer(fposAtt, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

	// Offset by 2
	GLuint ftexAtt = glGetAttribLocation(fprogram, "tex");
	glEnableVertexAttribArray(ftexAtt);
	glVertexAttribPointer(ftexAtt, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *) (sizeof(GLfloat) * 2));

	GLuint felements[] = {
		0, 1, 2,
		0, 2, 3
	};

	glGenBuffers(1, &febo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, febo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(felements), felements, GL_STATIC_DRAW);

	glUniform1i(glGetUniformLocation(fprogram, "fbTex"), 1);

	// Unbind everything.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/********************************************************************
 * endit()
 * 	Destroys everything SDL related. Please call this upon your
 * 	program's termination.
 ********************************************************************/
void Graphics :: endit() {
	// Destroy the things which were created.
	SDL_DestroyWindow(win);
	SDL_GL_DeleteContext(con);
	SDL_Quit();
}

/********************************************************************
 * deleteFrameBuffer()
 * 	Deletes the frame buffer associated with this object.
 ********************************************************************/
void Graphics :: deleteFrameBuffer() {
	glDeleteProgram(fprogram);
	glDeleteShader(fvert);
	glDeleteShader(ffrag);
	glDeleteVertexArrays(1, &fvao);
	glDeleteTextures(1, &ft);
	glDeleteRenderbuffers(1, &fr);
	glDeleteFramebuffers(1, &fb);
	glDeleteBuffers(1, &fvbo);
	glDeleteBuffers(1, &febo);
}

/********************************************************************
 * beginFrameBuffer()
 * 	Any GL drawing commands executed after this one will draw the
 * 	results to the framebuffer. To draw the framebuffer to the
 * 	screen, call the endFrameBuffer function.
 ********************************************************************/
void Graphics :: beginFrameBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, fb);
}

/********************************************************************
 * endFrameBuffer()
 * 	Draws what had been drawn to the frame buffer on the screen.
 * 	To draw things to the frame buffer, call beginFrameBuffer.
 ********************************************************************/
void Graphics :: endFrameBuffer() {
	glUseProgram(fprogram);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, fvbo);
	glBindVertexArray(fvao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, febo);

	glClear(GL_DEPTH_BUFFER_BIT);
	// glBlitFramebuffer migt do a similar thing.
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}
