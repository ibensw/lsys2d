#ifndef OPENGLSHOT_H
#define OPENGLSHOT_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
void glBindFramebuffer (GLenum, GLuint);

void Screenshot(const char* filename, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

#endif // OPENGLSHOT_H
