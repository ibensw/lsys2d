#ifndef ENGINE_H
#define ENGINE_H

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "point3d.h"

class Engine
{
	SDL_Surface* drawContext;
	Uint32 flags;
	double left;
	double right;
	double top;
	double bottom;
	double near;
	double far;

public:
	Engine();
	virtual ~Engine();
	void init(int w, int h);
	void draw();
	void clear();
	void setViewport(int x, int y, int w, int h);
	void setWindow(double l, double r, double b, double t, double n, double f);
	void rotateX(double r);
	void rotateY(double r);
	void rotateZ(double r);
	void drawLine(const Point3D&, const Point3D&);
	void drawLinePlain(const Point3D&, const Point3D&);
	void drawText(GLint x, GLint y, char* s, GLfloat r, GLfloat g, GLfloat b);
	void drawTriangle(const Point3D&, const Point3D&, const Point3D&);
	void setColor(float r, float g, float b);

	inline int PollEvent(SDL_Event &event){return SDL_PollEvent(&event);}
};

#endif // ENGINE_H
