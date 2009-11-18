#ifndef ENGINE_H
#define ENGINE_H

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "point3d.h"
#include "../memcache.h"

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
	MemCache<Point3D>* points;
	bool plain;

public:
	Engine();
	inline void setPoints(MemCache<Point3D>* s){ points=s; }
	virtual ~Engine();
	void init(int w, int h);
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
	inline void setLinePlain(bool p=true){ plain=p; }

	inline int PollEvent(SDL_Event &event){return SDL_PollEvent(&event);}
};

#endif // ENGINE_H
