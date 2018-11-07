// background.cpp

#include "background.h"

Background :: Background() {
	// Check constants.h for BACKGROUND
	ih = new ImageHandler(BACKGROUND, BSPOT_BKGD);

	ih->parseStrip(0, 0, ih->getSheetWidth(), ih->getSheetHeight(), 1, 1, 0, 0);
	initgl();
}

Background :: ~Background() {
	delete ih;
	enditgl();
}

void Background :: initgl() {
	// The standard gl object stuff.
	vert = createShader(GL_VERTEX_SHADER,   VS_BKGD);
	frag = createShader(GL_FRAGMENT_SHADER, FS_BKGD);

	prog = glCreateProgram();
	glAttachShader(prog, vert);
	glAttachShader(prog, frag);
	glBindFragDataLocation(prog, 0, "out_color");

	glLinkProgram(prog);
	glUseProgram(prog);
	printShaderError(vert, VS_BKGD);
	printShaderError(frag, FS_BKGD);

	//vao, vbo, 
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Uploaded to the GPU
	float rectArray [] {
		-1.0f,  1.0f, 0.0f, 0.0f, // TL
		 1.0f,  1.0f, 1.0f, 0.0f, // TR
		 1.0f, -1.0f, 1.0f, 1.0f, // BR

		-1.0f,  1.0f, 0.0f, 0.0f, // TL
		-1.0f, -1.0f, 0.0f, 1.0f, // BL
		 1.0f, -1.0f, 1.0f, 1.0f  // BR
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(rectArray), rectArray, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint pos = glGetAttribLocation(prog, "pos");
	GLuint uv  = glGetAttribLocation(prog, "uv");

	glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, nullptr);
	glVertexAttribPointer(uv , 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void *) (sizeof(GLfloat) * 2));

	glEnableVertexAttribArray(pos);
	glEnableVertexAttribArray(uv);

	glUniform1i(glGetUniformLocation(prog, "BkgdTex"), BSPOT_BKGD);
	// ren_dim / img_dim = num of repeat
	glUniform2f(glGetUniformLocation(prog, "rep_num"),
		RENDER_WIDTH  / (float) ih->getSheetWidth(),
		RENDER_HEIGHT / (float) ih->getSheetHeight());

	// Because the vectors must be horizontal (in arrays), the matrix must be transposed.
	glUniform2f(glGetUniformLocation(prog, "img_dim"), ih->getSheetWidth(), ih->getSheetHeight());

	unbind();
}

void Background :: enditgl() {
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glDeleteShader(vert);
	glDeleteShader(frag);
	glDeleteProgram(prog);
}

void Background :: unbind() {
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Background :: drawBackground(const View * v) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
	glUseProgram(prog);

	glUniform2f(glGetUniformLocation(prog, "view"), v->getX(), v->getY());
	glDrawArrays(GL_TRIANGLES, 0, 6);

	unbind();
}
