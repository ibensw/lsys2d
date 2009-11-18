#ifndef CALC_H
#define CALC_H
#include "point3d.h"
#include "parser.h"
#include "iteratator3.h"
#include "direction.h"
#include <string>
#include <list>
#include <map>
#include <stack>
#include "engine/engine.h"
#include "memcache.h"
#include "colormap.h"

using std::string;
using std::stack;
using std::list;
using std::pair;

class Calc
{
	//string s;
	SIterator* s;
	double a;
	MemCache<Point3D>* points;
	MemCache<Line>* lines;
	MemCache<Triangle>* triangles;
	unsigned long cLines;
	unsigned long cPoints;
	unsigned long cTriangles;
	Alphabet* ab;

public:
	double minX;
	double maxX;
	double minY;
	double maxY;
	double minZ;
	double maxZ;

	Calc(Alphabet*);
	virtual ~Calc();
	void init(SIterator* ss, double aa);
	void calculate();
	void draw(Engine* gfx, double, ColorMap* cm);
	inline MemCache<Point3D>* getPoints(){return points;}
	inline bool isDone(){return true;}
	inline unsigned long countLines(){return cLines;}
	inline unsigned long countPoints(){return cPoints;}
	void draw2(const char*, ColorMap* cm);
};

#endif // CALC_H
