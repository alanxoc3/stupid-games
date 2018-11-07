// helperGL.cpp

#include "helperGL.h"

/********************************************************************
 * printShaderError(shader, fileName)
 * 	Prints what is wrong with a shader. The compile errors. Prints
 * 	nothing if there is nothing wrong with the shader. Filename
 * 	is only needed to print the error message nicely. Shader is the
 * 	shader that was compiled.
 ********************************************************************/
void printShaderError(GLuint shader, const char * fileName) {
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		std::cerr << "ERROR WITH " << fileName << " CODE!" << std::endl;
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		std::cerr << "GL ERROR LOG:\n\t" << buffer << std::endl;
	}
}

/********************************************************************
 * readShaderFile(fileName, source)
 * 	Puts the contents of the file into the source parameter.
 * 	allocation is handled by this function, make sure to free the
 * 	memory.
 ********************************************************************/
void readShaderFile(const char * fileName, char * & source) {
	std::ifstream fin(fileName);

	// Source is NULL
	if (fin.fail()) {
		source = NULL;
		return;
	}

	int len = 0;
	fin.seekg(0, fin.end);
	len = fin.tellg();
	len += 1;
	fin.seekg(0, fin.beg);
	source = new char[len];
	fin.read(source, len);
	fin.close();

	// Add a null character at the end.
	source[len - 1] = '\0';
}

/********************************************************************
 * createShader()
 * 	Creates the shader by loading a file, then compiling the shader,
 * 	then checking for compile errors. Returns the shader program
 * 	number.
 ********************************************************************/
GLuint createShader(GLenum type, const char filename[]) {
	char * shaderSrc = nullptr;
	readShaderFile(filename, shaderSrc);

	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &shaderSrc, nullptr);
	glCompileShader(shader);
	printShaderError(shader, filename);
	if (!shaderSrc) {
		std::cerr << "ERROR: BAD FILE NAME \"" << filename << "\"\n";
	}

	delete [] shaderSrc;

	return shader;
}

/********************************************************************
 * loadImage()
 * 	Loads an image from a file onto a graphics card. Supports RGB
 * 	images at the moment, not RGBA. Returns the GL pointer location
 * 	to the resulting texture. Width and height may be set as well.
 * 	The image will remain bound to the texture spot of bindSpot.
 ********************************************************************/
GLuint loadImage(const char *fileName, GLuint bindSpot, GLuint & w, GLuint & h) {
	GLuint texture;
	GLint width, height;
	unsigned char * image;

	image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);
	std::cerr << width << " " << height << std::endl;

	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0 + bindSpot);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);

	w = width;
	h = height;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return texture;
}

/********************************************************************
 * printGLError()
 * 	Prints an error message if there is an error with Open GL.
 * 	Does nothing if there is no error.
 ********************************************************************/
void printGLError()
{
	GLenum error = glGetError();
	if (error == GL_NO_ERROR)
		return;
	
	std::cerr << "ERROR: OPENGL ";
	switch(error) {
		case GL_INVALID_ENUM:
			std::cerr << "INVALID ENUM";
			break;
		case GL_INVALID_VALUE:
			std::cerr << "INVALID VALUE";
			break;
		case GL_INVALID_OPERATION:
			std::cerr << "INVALID OPERATION";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cerr << "INVALID FRAMEBUFFER OPERATION";
			break;
		case GL_OUT_OF_MEMORY:
			std::cerr << "OUT OF MEMORY";
			break;
		case GL_STACK_UNDERFLOW:
			std::cerr << "ATTEMPTED STACK UNDERFLOW";
			break;
		case GL_STACK_OVERFLOW:
			std::cerr << "ATTEMPTED STACK OVERFLOW";
			break;
		default:
			std::cerr << "IDK - " << error;
			break;
	}

	std::cerr << " ERROR!\n**If you have an error other than \"OUT OF MEMORY\", please contact alanxoc3@gmail.com for improvements to this project.\n";
}
