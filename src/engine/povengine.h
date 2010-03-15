#ifndef POVEngine_H
#define POVEngine_H
#include <fstream>
#include "../point3d.h"
#include "../direction.h"
#include "../memcache.h"
#include "../colormap.h"
#include "engine.h"

class POVEngine: public Engine{
	public:
		POVEngine(const char* filename, const ColorMap* cm);
		void draw();
		void clear();
		void setWindow(double l, double r, double b, double t, double n, double f);
		void drawLine(const Line& l);
		void drawLinePlain(const Line& l);
		void drawTriangle(const Triangle& l);

	private:
		MemCache<Point3D>* points;
		std::ofstream outfile;
		ColorMap* col;
};

#endif // POVEngine_H
