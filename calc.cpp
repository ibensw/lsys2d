#include "calc.h"
//#include <iostream>
#include <math.h>
#include <stack>
#include "point3d.h"
#include "direction.h"
#include "memcache.h"
#include "iteratator3.h"

#include <stdlib.h>

#define PI2 (M_PI*2)
#define WIDTH 800
#define HEIGHT 800

using namespace std;

Calc::Calc(Alphabet* a):
		s(0), a(0), points(0), lines(0), triangles(0), cLines(0), cTriangles(0), ab(a), minX(0), maxX(0), minY(0), maxY(0), minZ(0), maxZ(0)
{
}

Calc::~Calc(){
	if (points)
		delete points;
	if (lines)
		delete lines;
	if (triangles)
		delete triangles;
}

void Calc::init(SIterator* ss, double aa){
	s=ss;
	a=aa;
	cLines=ss->countLines();
	cTriangles=ss->countTriangles();
	cPoints=ss->countPoints();
	minX=minY=maxX=maxY=minZ=maxZ=0.0;
	if (points)
		delete points;
	points=0;
	if (lines)
		delete lines;
	lines=0;
	if (triangles)
		delete triangles;
	triangles=0;
}

struct {
	Point3D pos;
	Direction dir;
	long thick;
	long length;
} state;

void Calc::calculate(){
	Point3D p(0.0, 0.0, 0.0);
	stack< pair<Point3D,Direction> > pointstack;
	Point3D f(0.0, 1.0, 0.0); //forward
	Point3D u(0.0, 0.0, 1.0); //up
	Direction d(f, u);

	if (points)
		delete points;

	if (lines)
		delete lines;

	if (triangles)
		delete triangles;

	//points=new Point3D[cPoints];
	points=new MemCache<Point3D>(cPoints, (256*1024*1024)/sizeof(Point3D)); //64MB blocks
	//lines= new unsigned long[cLines*2];
	lines=new MemCache<unsigned long>(cLines*2, (128*1024*1024)/sizeof(unsigned long));
	//triangles=new unsigned long[cTriangles*3];
	triangles=new MemCache<unsigned long>(cTriangles*3, (64*1024*1024)/sizeof(unsigned long));

	unsigned long pCount=0;
	unsigned long lCount=0;
	unsigned long tCount=0;
	unsigned long polystack=0;
	unsigned long polyPoint=0;

	s->front();
	char x;
	while ((x=s->next())){
		switch(ab->lookup(x)){
			case DRAW:
				if (!pCount || points->get(pCount-1) != p){
					(*points)[pCount++]=p;
				}
				p+=d.GetForward();
				(*points)[pCount++]=p;

				(*lines)[lCount++]=pCount-2;
				(*lines)[lCount++]=pCount-1;

				if (p.c[0]<minX) minX=p.c[0];
				if (p.c[0]>maxX) maxX=p.c[0];
				if (p.c[1]<minY) minY=p.c[1];
				if (p.c[1]>maxY) maxY=p.c[1];
				if (p.c[2]<minZ) minZ=p.c[2];
				if (p.c[2]>maxZ) maxZ=p.c[2];
				break;
			case MOVE:
				p+=d.GetForward();
				(*points)[pCount++]=p;
				if (p.c[0]<minX) minX=p.c[0];
				if (p.c[0]>maxX) maxX=p.c[0];
				if (p.c[1]<minY) minY=p.c[1];
				if (p.c[1]>maxY) maxY=p.c[1];
				if (p.c[2]<minZ) minZ=p.c[2];
				if (p.c[2]>maxZ) maxZ=p.c[2];

				if (polystack && p!=points->get(polyPoint) && points->get(pCount-2)!=points->get(polyPoint)){
					(*triangles)[tCount++]=polyPoint;
					(*triangles)[tCount++]=pCount-2;
					(*triangles)[tCount++]=pCount-1;
				}

				break;
			case TURNL:
				d.TurnLeft(a);
				break;
			case TURNR:
				d.TurnLeft(-a);
				break;
			case PITCHU:
				d.PitchUp(a);
				break;
			case PITCHD:
				d.PitchUp(-a);
				break;
			case ROLLR:
				d.RollLeft(-a);
				break;
			case ROLLL:
				d.RollLeft(a);
				break;
			case FULLTURN:
				d.TurnLeft(M_PI);
				break;
			case PUSH:
				pointstack.push(pair<Point3D, Direction>(p, d));
				break;
			case POP:
				p=pointstack.top().first;
				d=pointstack.top().second;
				pointstack.pop();
				break;
			case POLYSTART:
				pointstack.push(pair<Point3D, Direction>(p, d));
				++polystack;
				polyPoint=pCount-1;
				break;
			case POLYEND:
				p=pointstack.top().first;
				d=pointstack.top().second;
				pointstack.pop();
				--polystack;
				break;
			default:
				break;
		}
	}


	//points=(Point3D*) realloc(points, pCount*sizeof(Point3D));
	//triangles=(unsigned long*) realloc(triangles, tCount*sizeof(unsigned long));
	cPoints=pCount;
	cTriangles=tCount/3;
}

void Calc::draw(Engine *gfx, void (Engine::* lineFunc)(const Point3D&, const Point3D&)){
	double var;
	gfx->setColor(0.67, 0.45, 0.01);
	for (unsigned long i=0; i<cLines; i++){
		var=(double)i/(cLines-1);
			if (var<0.5)
				gfx->setColor(2.0*var, 1.0, 0.0);
			else
				gfx->setColor(1.0, 1.0-(2.0*var-1.0), 0);
		(gfx->*lineFunc)(points->get(lines->get(2*i)), points->get(lines->get(2*i+1)));
	}

	gfx->setColor(0.01, 0.74, 0.03);
	for (unsigned long i=0; i<cTriangles; i++){
		var=(double)i/(cTriangles-1);
			if (var<0.5)
				gfx->setColor(2.0*var, 1.0, 0.0);
			else
				gfx->setColor(1.0, 1.0-(2.0*var-1.0), 0);
		gfx->drawTriangle(points->get(triangles->get(3*i)), points->get(triangles->get(3*i+1)), points->get(triangles->get(3*i+2)));
	}

	//gfx.drawText(20, 20, "Hello world", 1.0f, 0.0f, 0.0f);
	//gfx->draw();
}

#include "engine/povengine.h"

void Calc::draw2(){
	povengine x("test.pov");
	double factor=maxX-minX;
	double factorY=maxY-minY;

	if (factor<factorY)
		factor=factorY;

	x.setWindow(minX-1, minX+factor+1, minY-1, minY+factor+1, maxZ, minZ);

	double var;
	//gfx->setColor(0.67, 0.45, 0.01);
	for (unsigned long i=0; i<cLines; i++){
		/*var=(double)i/(cLines-1);
			if (var<0.5)
				gfx->setColor(2.0*var, 1.0, 0.0);
			else
				gfx->setColor(1.0, 1.0-(2.0*var-1.0), 0);*/
		x.drawLine(points->get(lines->get(2*i)), points->get(lines->get(2*i+1)));
	}

	//gfx->setColor(0.01, 0.74, 0.03);
	for (unsigned long i=0; i<cTriangles; i++){
		/*var=(double)i/(cTriangles-1);
			if (var<0.5)
				gfx->setColor(2.0*var, 1.0, 0.0);
			else
				gfx->setColor(1.0, 1.0-(2.0*var-1.0), 0);*/
		x.drawTriangle(points->get(triangles->get(3*i)), points->get(triangles->get(3*i+1)), points->get(triangles->get(3*i+2)));
	}

	//gfx.drawText(20, 20, "Hello world", 1.0f, 0.0f, 0.0f);
	x.draw();
}
