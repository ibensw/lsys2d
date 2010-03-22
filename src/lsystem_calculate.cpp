#include "lsystem.h"
#include <stdlib.h>

Geometry::Geometry():
		minX(0.0), maxX(0.0), minY(0.0), maxY(0.0), minZ(0.0), maxZ(0.0),
		points(0), lines(0), triangles(0)
{}

Geometry::~Geometry(){
	cleanup();
}

void Geometry::cleanup(){
	minX=maxX=minY=maxY=minZ=maxZ=0.0;
	if (lines)
		delete[] lines;
	if (triangles)
		delete[] triangles;
	if (points)
		delete[] points;
	lines=0;
	triangles=0;
	points=0;
}

struct DrawState{
	Point3D pos;
	Direction dir;
	double thick;
	double length;
	unsigned int color;
};

void LSystem::calculate(){
	if (validgeo){
		return;
	}
	geo->cleanup();

	printf("angle=%f\n", sigma);
	Point3D pp(0.0, 0.0, 0.0);
	stack< DrawState > pointstack;
	Point3D f(0.0, 1.0, 0.0); //forward
	Point3D u(0.0, 0.0, 1.0); //up
	Direction dd(f, u);

	DrawState curr;
	curr.pos=pp;
	curr.dir=dd;
	curr.thick=startthick;
	curr.length=startlength;
	printf("startthickness=%f\n", curr.thick);
	curr.color=1;

	/*geo->points=new MemCache<Point3D>(iterator.countPoints(), (256*1024*1024)/sizeof(Point3D)); //64MB blocks
	geo->lines=new MemCache<Line>(iterator.countLines(), (128*1024*1024)/sizeof(Line));
	geo->triangles=new MemCache<Triangle>(iterator.countTriangles(), (64*1024*1024)/sizeof(Triangle));*/
	printf("Requesting:\nPoints:\t\t%lu\nLines:\t\t%lu\nTriangles:\t%lu\n",
	 iterator.countPoints(),
	 iterator.countLines(),
	 iterator.countTriangles());
	geo->points = new Point3D[iterator.countPoints()];
	geo->lines = new Line[iterator.countLines()];
	geo->triangles = new Triangle[iterator.countTriangles()];


	unsigned long pCount=0;
	unsigned long lCount=0;
	unsigned long tCount=0;
	unsigned long polystack=0;
	stack< unsigned long > polypoints;
	double param;

	iterator.front();
	char x;
	while ((x=iterator.next())){
		printf("%c - %i\n", x, pointstack.size());
		switch(alphabet.lookup(x)){
			case DRAW:
			case DRAWHALF:
				param=iterator.nextParam(1.0);

				if (!pCount || geo->points[pCount-1] != curr.pos){
					geo->points[pCount++]=curr.pos;
				}

				if (alphabet.lookup(x) == DRAWHALF){
					curr.pos+=(curr.dir.GetForward()*curr.length*0.5*param);
				}else{
					curr.pos+=(curr.dir.GetForward()*curr.length*param);
				}

				geo->points[pCount++]=curr.pos;

				geo->lines[lCount++] = Line(pCount-2, pCount-1, curr.thick, curr.color);

				if (curr.pos.c[0]<geo->minX) geo->minX=curr.pos.c[0];
				if (curr.pos.c[0]>geo->maxX) geo->maxX=curr.pos.c[0];
				if (curr.pos.c[1]<geo->minY) geo->minY=curr.pos.c[1];
				if (curr.pos.c[1]>geo->maxY) geo->maxY=curr.pos.c[1];
				if (curr.pos.c[2]<geo->minZ) geo->minZ=curr.pos.c[2];
				if (curr.pos.c[2]>geo->maxZ) geo->maxZ=curr.pos.c[2];
				break;
			case MOVE:
			case MOVEHALF:
				param=iterator.nextParam(1.0);
				if (alphabet.lookup(x) == MOVEHALF){
					curr.pos+=(curr.dir.GetForward()*curr.length*0.5*param);
				}else{
					curr.pos+=(curr.dir.GetForward()*curr.length*param);
				}

				geo->points[pCount++]=curr.pos;
				if (curr.pos.c[0]<geo->minX) geo->minX=curr.pos.c[0];
				if (curr.pos.c[0]>geo->maxX) geo->maxX=curr.pos.c[0];
				if (curr.pos.c[1]<geo->minY) geo->minY=curr.pos.c[1];
				if (curr.pos.c[1]>geo->maxY) geo->maxY=curr.pos.c[1];
				if (curr.pos.c[2]<geo->minZ) geo->minZ=curr.pos.c[2];
				if (curr.pos.c[2]>geo->maxZ) geo->maxZ=curr.pos.c[2];

				if (polystack && curr.pos!=geo->points[polypoints.top()] && geo->points[pCount-2]!=geo->points[polypoints.top()]){
					geo->triangles[tCount++] = Triangle(polypoints.top(), pCount-2, pCount-1, curr.color);
				}

				break;
			case TURNL:
				param=iterator.nextParam(sigma);
				curr.dir.TurnLeft(param);
				break;
			case TURNR:
				param=iterator.nextParam(sigma);
				curr.dir.TurnLeft(-param);
				break;
			case PITCHU:
				param=iterator.nextParam(sigma);
				curr.dir.PitchUp(param);
				break;
			case PITCHD:
				param=iterator.nextParam(sigma);
				curr.dir.PitchUp(-param);
				break;
			case ROLLR:
				param=iterator.nextParam(sigma);
				curr.dir.RollLeft(-param);
				break;
			case ROLLL:
				param=iterator.nextParam(sigma);
				curr.dir.RollLeft(param);
				break;
			case FULLTURN:
				curr.dir.TurnLeft(180);
				break;
			case PUSH:
				pointstack.push(curr);
				break;
			case POP:
				curr=pointstack.top();
				pointstack.pop();
				break;
			case LENGTHLESS:
				param=iterator.nextParam(0.9);
				curr.length*=param;
				break;
			case LENGTHMORE:
				param=iterator.nextParam(1.1);
				curr.length*=param;
				break;
			case THICKLESS:
				param=iterator.nextParam(0.7);
				curr.thick*=param;
				break;
			case THICKMORE:
				param=iterator.nextParam(1.4);
				curr.thick*=param;
				break;
			case POLYSTART:
				pointstack.push(curr);
				++polystack;
				polypoints.push(pCount-1);
				break;
			case POLYEND:
				curr=pointstack.top();
				pointstack.pop();
				--polystack;
				polypoints.pop();
				break;
			case COLOR:
				param=iterator.nextParam(curr.color+1);
				curr.color=(unsigned int)param;
				break;
			default:
				break;
		}
	}

	geo->cPoints=pCount;
	geo->cLines=lCount;
	geo->cTriangles=tCount;

	//Shrink if we overestimated, check performance on other system
	printf("Memory shrinkage:\nPoints:\t\t%lu \t%lu\nLines:\t\t%lu \t%lu\nTriangles:\t%lu \t%lu\n",
		 iterator.countPoints(), pCount,
		 iterator.countLines(), lCount,
		 iterator.countTriangles(), tCount);
	geo->points=(Point3D*) realloc(geo->points, pCount*sizeof(Point3D));
	geo->lines=(Line*) realloc(geo->lines, lCount*sizeof(Line));
	geo->triangles=(Triangle*) realloc(geo->triangles, tCount*sizeof(Triangle));

	validgeo=true;
}

