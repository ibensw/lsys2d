#ifndef LSYSTEM_H
#define LSYSTEM_H

#include "calc.h"
#include "iteratator3.h"
#include "alphabet.h"
#include "colormap.h"

#include <map>
#include <vector>

struct Geometry{
	double minX;
	double maxX;
	double minY;
	double maxY;
	double minZ;
	double maxZ;
	/*MemCache<Point3D>* points;
	MemCache<Line>* lines;
	MemCache<Triangle>* triangles;*/
	Point3D* points;
	Line* lines;
	Triangle* triangles;
	unsigned long cLines;
	unsigned long cPoints;
	unsigned long cTriangles;
	Geometry();
	virtual ~Geometry();
	void cleanup();
};

class LSystem{
	public:
		LSystem();
		virtual ~LSystem();

		void openfile(const char* filename);
		void iterate(int i=1);
		void absoluteiterate(int i);
		void calculate();
		void render(Engine*);
		inline ColorMap* getColors(){ return &colors; }
		inline unsigned int StringSize(){ return iterator.length(); }
		inline unsigned int CountLines(){ return geo->cLines; }
		inline unsigned int CountPoints(){ return geo->cPoints; }
		inline unsigned int CountTriangles(){ return geo->cTriangles; }
		inline SIterator* it(){ return &iterator; }

	private:
		Geometry* geo;
		bool validgeo;
		std::vector<double> params;
		Alphabet alphabet;
		//Calc calculator;
		SIterator iterator;
		ColorMap colors;
		double sigma;
		double startlength;
		double startthick;
		int iterations;
};

#endif // LSYSTEM_H
