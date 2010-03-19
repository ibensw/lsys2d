#ifndef ENGINE_H
#define ENGINE_H

#include "../point3d.h"
#include "../memcache.h"

class Engine{
public:
	Engine();
	virtual ~Engine();

	virtual void draw();
	virtual void setWindow(double l, double r, double b, double t, double n, double f);
	virtual void setPoints(Point3D*);
	virtual void drawLine(const Line& l)=0;
	virtual void drawLinePlain(const Line& l)=0;
	virtual void drawTriangle(const Triangle&)=0;
	virtual void setColor(float r, float g, float b);
	inline void setLinePlain(bool p=true){ plain=p; }
	inline void setRoundCylinder(bool p=true){ roundcyls=p; }

protected:
	Point3D* points;
	bool plain;
	bool roundcyls;
};

#endif // ENGINE_H
