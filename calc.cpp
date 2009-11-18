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

struct DrawState{
	Point3D pos;
	Direction dir;
	double thick;
	double length;
	unsigned int color;
};

void Calc::calculate(){
	printf("angle=%f\n", a);
	Point3D pp(0.0, 0.0, 0.0);
	stack< DrawState > pointstack;
	Point3D f(0.0, 1.0, 0.0); //forward
	Point3D u(0.0, 0.0, 1.0); //up
	Direction dd(f, u);

	DrawState curr;
	curr.pos=pp;
	curr.dir=dd;
	curr.thick=0.1;
	curr.length=1.0;
	curr.color=1;

	if (points)
		delete points;

	if (lines)
		delete lines;

	if (triangles)
		delete triangles;

	points=new MemCache<Point3D>(cPoints, (256*1024*1024)/sizeof(Point3D)); //64MB blocks
	lines=new MemCache<Line>(cLines, (128*1024*1024)/sizeof(Line));
	triangles=new MemCache<Triangle>(cTriangles, (64*1024*1024)/sizeof(Triangle));

	unsigned long pCount=0;
	unsigned long lCount=0;
	unsigned long tCount=0;
	unsigned long polystack=0;
	unsigned long polyPoint=0;
	double param;

	s->front();
	char x;
	while ((x=s->next())){
		switch(ab->lookup(x)){
			case DRAW:
				if (!pCount || points->get(pCount-1) != curr.pos){
					(*points)[pCount++]=curr.pos;
				}
				curr.pos+=(curr.dir.GetForward()*curr.length);
				(*points)[pCount++]=curr.pos;

				(*lines)[lCount++] = Line(pCount-2, pCount-1, curr.thick, curr.color);

				if (curr.pos.c[0]<minX) minX=curr.pos.c[0];
				if (curr.pos.c[0]>maxX) maxX=curr.pos.c[0];
				if (curr.pos.c[1]<minY) minY=curr.pos.c[1];
				if (curr.pos.c[1]>maxY) maxY=curr.pos.c[1];
				if (curr.pos.c[2]<minZ) minZ=curr.pos.c[2];
				if (curr.pos.c[2]>maxZ) maxZ=curr.pos.c[2];
				break;
			case MOVE:
				curr.pos+=(curr.dir.GetForward()*curr.length);
				(*points)[pCount++]=curr.pos;
				if (curr.pos.c[0]<minX) minX=curr.pos.c[0];
				if (curr.pos.c[0]>maxX) maxX=curr.pos.c[0];
				if (curr.pos.c[1]<minY) minY=curr.pos.c[1];
				if (curr.pos.c[1]>maxY) maxY=curr.pos.c[1];
				if (curr.pos.c[2]<minZ) minZ=curr.pos.c[2];
				if (curr.pos.c[2]>maxZ) maxZ=curr.pos.c[2];

				if (polystack && curr.pos!=points->get(polyPoint) && points->get(pCount-2)!=points->get(polyPoint)){
					(*triangles)[tCount++] = Triangle(polyPoint, pCount-2, pCount-1, curr.color);
				}

				break;
			case TURNL:
				curr.dir.TurnLeft(a);
				break;
			case TURNR:
				curr.dir.TurnLeft(-a);
				break;
			case PITCHU:
				curr.dir.PitchUp(a);
				break;
			case PITCHD:
				curr.dir.PitchUp(-a);
				break;
			case ROLLR:
				curr.dir.RollLeft(-a);
				break;
			case ROLLL:
				curr.dir.RollLeft(a);
				break;
			case FULLTURN:
				curr.dir.TurnLeft(M_PI);
				break;
			case PUSH:
				pointstack.push(curr);
				break;
			case POP:
				curr=pointstack.top();
				pointstack.pop();
				break;
			case LENGTHLESS:
				curr.length*=0.9;
				break;
			case LENGTHMORE:
				curr.length*=1.1;
				break;
			case THICKLESS:
				curr.thick*=0.9;
				break;
			case THICKMORE:
				curr.thick*=1.1;
				break;
			case POLYSTART:
				pointstack.push(curr);
				++polystack;
				polyPoint=pCount-1;
				break;
			case POLYEND:
				curr=pointstack.top();
				pointstack.pop();
				--polystack;
				break;
			case COLOR:
				param=s->nextParam();
				if (s){
					curr.color=(unsigned int)param;
				}else{
					++curr.color;
				}
				break;
			default:
				break;
		}
	}

	cPoints=pCount;
	cLines=lCount;
	cTriangles=tCount;
}

void Calc::draw(Engine *gfx, double rot, ColorMap* cm){
	double var;
	gfx->setPoints(points);
	double factor=maxX-minX;
	double factorY=maxY-minY;

	if (factor<factorY)
		factor=factorY;

	gfx->setWindow(minX-1, minX+factor+1, minY-1, minY+factor+1, maxZ, minZ);
	gfx->rotateY(rot);


	gfx->setColor(0.67, 0.45, 0.01);
	for (unsigned long i=0; i<cLines; i++){
		const Line& line=lines->get(i);
		gfx->setColor(cm->operator [](line.color).r, cm->operator [](line.color).g, cm->operator [](line.color).b);
		gfx->drawLine(line);
	}

	gfx->setColor(0.01, 0.74, 0.03);
	for (unsigned long i=0; i<cTriangles; i++){
		const Triangle& triangle=triangles->get(i);
		gfx->setColor(cm->operator [](triangle.color).r, cm->operator [](triangle.color).g, cm->operator [](triangle.color).b);
		gfx->drawTriangle(triangle);
	}

	gfx->draw();
}

#include "engine/povengine.h"

void Calc::draw2(const char* filename, ColorMap* cm){
	povengine x(filename, cm);
	x.setPoints(points);
	double factor=maxX-minX;
	double factorY=maxY-minY;

	if (factor<factorY)
		factor=factorY;

	x.setWindow(minX-1, minX+factor+1, minY-1, minY+factor+1, maxZ, minZ);

	double var;
	//gfx->setColor(0.67, 0.45, 0.01);
	for (unsigned long i=0; i<cLines; i++){
		x.drawLine(lines->get(i));
	}

	//gfx->setColor(0.01, 0.74, 0.03);
	for (unsigned long i=0; i<cTriangles; i++){
		x.drawTriangle(triangles->get(i));
	}

	//gfx.drawText(20, 20, "Hello world", 1.0f, 0.0f, 0.0f);
	x.draw();
}
