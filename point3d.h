#ifndef POINT3D_H
#define POINT3D_H

//#include <ostream>
#include <math.h>

class Point3D
{
public:
	double c[3];

	inline Point3D(){}
	inline Point3D(double x, double y, double z){c[0]=x; c[1]=y; c[2]=z;}
	inline void operator+=(const Point3D& p){
		c[0]+=p.c[0];
		c[1]+=p.c[1];
		c[2]+=p.c[2];
	}
	inline void operator-=(const Point3D& p){
		c[0]-=p.c[0];
		c[1]-=p.c[1];
		c[2]-=p.c[2];
	}
	inline void operator*=(const double d){
		c[0]*=d;
		c[1]*=d;
		c[2]*=d;
	}
	inline Point3D operator*(const double d) const{
		return Point3D(c[0]*d, c[1]*d, c[2]*d);
	}
	inline Point3D operator+(const Point3D& p) const{
		return Point3D(c[0]+p.c[0], c[1]+p.c[1], c[2]+p.c[2]);
	}
	inline Point3D operator-(const Point3D& p) const{
		return Point3D(c[0]-p.c[0], c[1]-p.c[1], c[2]-p.c[2]);
	}
	inline Point3D operator*(const Point3D& p) const{
		return Point3D(-p.c[1]*c[2]+p.c[2]*c[1],
				   p.c[0]*c[2]-c[0]*p.c[2],
				   -p.c[0]*c[1]+c[0]*p.c[1]);
	}
	inline bool operator!=(const Point3D& p) const{
		return (c[0]!=p.c[0] || c[1]!=p.c[1] || c[2]!=p.c[2]);
	}
	inline double operator^(const Point3D& p) const{
		return c[0]*p.c[0]+c[1]*p.c[1]+c[2]*p.c[2];
	}
	inline double LengthSquared() const{
		return c[0]*c[0]+c[1]*c[1]+c[2]*c[2];
	}
	inline void Normalise(){
		double invlen=1.0/sqrt(LengthSquared());
		c[0]*=invlen;
		c[1]*=invlen;
		c[2]*=invlen;
	}
};

/*inline std::ostream& operator<<(std::ostream& oss, const Point3D& p){
	oss << "(" << p.c[0] << ", " << p.c[1] << ", " << p.c[2] << ")";
	return oss;
}*/

struct Line{
	inline Line(){};
	inline Line(unsigned long pp1, unsigned long pp2, double pt, unsigned int pc):
			p1(pp1), p2(pp2), thickness(pt), color(pc){}
	unsigned long p1;
	unsigned long p2;
	double thickness;
	unsigned int color;
};

struct Triangle{
	inline Triangle(){}
	inline Triangle(unsigned long pp1, unsigned long pp2, unsigned long pp3, unsigned int pc):
			p1(pp1), p2(pp2), p3(pp3), color(pc){}
	unsigned long p1;
	unsigned long p2;
	unsigned long p3;
	unsigned int color;
};

#endif // POINT3D_H
