#ifndef POVENGINE_H
#define POVENGINE_H
#include <fstream>
#include "../point3d.h"


class povengine{
	public:
		povengine(char* filename);
		void draw();
		void clear();
		inline void setViewport(int x, int y, int w, int h) {}
		void setWindow(double l, double r, double b, double t, double n, double f);
		inline void rotateX(double r){}
		inline void rotateY(double r){}
		inline void rotateZ(double r){}
		void drawLine(const Point3D&, const Point3D&, double);
		void drawLinePlain(const Point3D&, const Point3D&);
		//void drawText(GLint x, GLint y, char* s, GLfloat r, GLfloat g, GLfloat b);
		void drawTriangle(const Point3D&, const Point3D&, const Point3D&);
		void setColor(float r, float g, float b);

	private:
		std::ofstream outfile;
};

#endif // POVENGINE_H
