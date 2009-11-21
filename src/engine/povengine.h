#ifndef POVENGINE_H
#define POVENGINE_H
#include <fstream>
#include "../point3d.h"
#include "../direction.h"
#include "../memcache.h"
#include "../colormap.h"

class povengine{
	public:
		povengine(const char* filename, const ColorMap* cm);
		inline void setPoints(MemCache<Point3D>* s){ points=s; }
		void draw();
		void clear();
		inline void setViewport(int x, int y, int w, int h) {}
		void setWindow(double l, double r, double b, double t, double n, double f);
		inline void rotateX(double r){}
		inline void rotateY(double r){}
		inline void rotateZ(double r){}
		void drawLine(const Line& l);
		void drawLinePlain(const Line& l);
		void drawTriangle(const Triangle& l);
		void setColor(float r, float g, float b);

	private:
		MemCache<Point3D>* points;
		std::ofstream outfile;
		ColorMap* col;
};

#endif // POVENGINE_H
