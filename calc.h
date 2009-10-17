#ifndef CALC_H
#define CALC_H

#include <string>
#include <list>
#include <map>
#include <stack>
#include "engine/engine.h"
#include "point3d.h"
#include "parser.h"
#include "memcache.h"
#include "iterator2.h"

using std::string;
using std::stack;
using std::list;
using std::pair;

class Calc
{
	//string s;
	double a;
//	Point3D *points;
	MemCache<Point3D>* points;
//	unsigned long *lines;
	MemCache<unsigned long>* lines;
//	unsigned long *triangles;
	MemCache<unsigned long>* triangles;
	unsigned long cLines;
	unsigned long cPoints;
	unsigned long cTriangles;
	Alphabet* ab;
	Iterator* s;

public:
	double minX;
	double maxX;
	double minY;
	double maxY;
	double minZ;
	double maxZ;

	Calc(Alphabet*);
	virtual ~Calc();
	void init(Iterator* ss, double aa);
	void calculate();
	void draw(Engine* gfx, void (Engine::* lineFunc)(const Point3D&, const Point3D&));
	inline MemCache<Point3D>* getPoints(){return points;}
	inline MemCache<unsigned long>* getLines(){return lines;}
	inline bool isDone(){return true;}
	inline unsigned long countLines(){return cLines;}
	inline unsigned long countPoints(){return cPoints;}
};

#endif // CALC_H
