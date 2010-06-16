#include "lsystem.h"

using namespace std;

LSystem::LSystem(){
	sigma=90.0;
	startlength=1.0;
	startthick=0.1;
	iterations=0;
	iterator.setAlphabet(&alphabet);
	iterator.setParameters(&params);
	geo=0;
	validgeo=false;
}

LSystem::~LSystem(){
	if (geo)
		delete geo;
}

void LSystem::iterate(int i){
	iterations+=i;
	iterator.setIteration(iterations);
	validgeo=false;
}

void LSystem::absoluteiterate(int i){
	iterator.setIteration(i);
	validgeo=false;
}


void LSystem::render(Engine *gfx){
	gfx->setPoints(geo->points);
	double factor=geo->maxX-geo->minX;
	double factorY=geo->maxY-geo->minY;

	if (factor<factorY)
		factor=factorY;

	gfx->setWindow(geo->minX-1, geo->minX+factor+1, geo->minY-1, geo->minY+factor+1, geo->maxZ, geo->minZ);
	
	Color c;
	for (unsigned long i=0; i<geo->cLines; ++i){
		const Line line=geo->lines[i];
		c=colors[line.color];
		gfx->setColor(c.r, c.g, c.b);
		gfx->drawLine(line);
	}

	for (unsigned long i=0; i<geo->cTriangles; ++i){
		const Triangle& triangle=geo->triangles[i];
		c=colors[triangle.color];
		gfx->setColor(c.r, c.g, c.b);
		gfx->drawTriangle(triangle);
	}

	gfx->draw();
}
