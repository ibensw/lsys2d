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
	MemCache<Point3D>* points;
	MemCache<Line>* lines;
	MemCache<Triangle>* triangles;
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

		void openfile(char* filename);
		void iterate(int i=1);
		void calculate();
		void render(Engine*);
		inline ColorMap* getColors(){ return &colors; }

	private:
		Geometry geo;
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
