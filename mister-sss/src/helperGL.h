/********************************************************************
 * Helper GL
 * 	Contains a bunch of rogue helper functions for open GL.
 * 	Simplifies more used stuff a bit. This is not an object
 * 	oriented file, open gl isn't either. TAKE THAT!
 ********************************************************************/

#ifndef _HELPER_GL_H
#define _HELPER_GL_H

#include "constants.h"

void printShaderError(GLuint shader, const char * fileName);
GLuint createShader(GLenum type, const char filename[]);
void readShaderFile(const char * fileName, char * & source);

void printGLError();
GLuint loadImage(const char * fileName, GLuint bindSpot, GLuint & w, GLuint & h);

#endif //_HELPER_GL_H
