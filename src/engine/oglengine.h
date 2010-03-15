#ifndef OGLENGINE_H
#define OGLENGINE_H

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include "engine.h"

class OGLEngine: public Engine{
private:
	SDL_Surface* drawContext;
	Uint32 flags;
	double left;
	double right;
	double top;
	double bottom;
	double near;
	double far;

	double rotX, rotY, rotZ;

public:
	OGLEngine(int w, int h, std::string caption);
	virtual ~OGLEngine();
	void draw();
	void clear();
	void setViewport(int x, int y, int w, int h);
	void setWindow(double l, double r, double b, double t, double n, double f);
	void rotateX(double r);
	void rotateY(double r);
	void rotateZ(double r);
	void drawLine(const Line& l);
	void drawLinePlain(const Line& l);
	void drawTriangle(const Triangle&);
	void setColor(float r, float g, float b);
	void onQuit(void (*f)(void*), void*);
};

#endif // OGLENGINE_H
