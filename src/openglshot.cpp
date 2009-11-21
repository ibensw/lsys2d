#include "openglshot.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <pngwriter.h>
#include <stdio.h>

void Screenshot(const char* filename, unsigned int x, unsigned int y, unsigned int w, unsigned int h){
	pngwriter png(w, h, 0.0, filename);
	unsigned int surface = w*h;
	float *pixels = new float[surface*3];

	glReadPixels( (GLint)x, (GLint)y, (GLsizei)w, (GLsizei)h, GL_RGB, GL_FLOAT, pixels);

	printf ("GL Error : %s\n", gluErrorString(glGetError()));
	for (unsigned int i=0; i<surface; ++i){
		if (pixels[3*i]+pixels[3*i+1]+pixels[3*i+2] != 0.0)
			//printf("%u,%u: %f %f %f\n", i/w, i%w, pixels[3*i], pixels[3*i+1], pixels[3*i+2]);
			png.plot(i%w, i/w, pixels[3*i], pixels[3*i+1], pixels[3*i+2]);
	}

	delete []pixels;
	png.close();
}

