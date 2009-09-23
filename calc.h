#ifndef CALC_H
#define CALC_H

#include <string>
#include <list>
#include <map>
#include <stack>
#include "engine/engine.h"
#include "point3d.h"
#include "parser.h"

using std::string;
using std::stack;
using std::list;
using std::pair;

class Calc
{
	string s;
	double a;
	//map<long, Point2D> points;
	Point3D *points;
	//list<Line> lines;
	unsigned long *lines;
	unsigned long *triangles;
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
	void init(Parser ss, double aa);
	void calculate();
	void draw(Engine* gfx, void (Engine::* lineFunc)(const Point3D&, const Point3D&));
	//inline map<long, Point2D> getPoints(){return points;}
	inline Point3D* getPoints(){return points;}
	//inline list<Line> getLines(){return lines;}
	inline unsigned long* getLines(){return lines;}
	inline bool isDone(){return true;}
	inline unsigned long countLines(){return cLines;}
	inline unsigned long countPoints(){return cPoints;}
};

#endif // CALC_H
