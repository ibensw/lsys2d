#include "povengine.h"

using namespace std;


povengine::povengine(char* filename){
	if (outfile.is_open()) outfile.close();
	outfile.open(filename);
	outfile << "#include \"colors.inc\"" << endl
			<< "#include \"shapes.inc\"" << endl
			<< "#include \"woods.inc\"" << endl
			<< "background { color SkyBlue }" << endl
			<< "plane {" << endl
			<< " y, 0" << endl
			<< " pigment { color MediumGoldenrod} finish { ambient 0.35 }" << endl
			<< "}" << endl << endl;

}

void povengine::setWindow(double l, double r, double b, double t, double n, double f){
	double gamma=45.0/180.0*M_PI;
	double c=r-l;
	double dist=sqrt( (c*c) /(2*(1-cos(gamma))) - (c/2.0)*(c/2.0));
	c=t-b;
	double dist2=sqrt( (c*c) /(2*(1-cos(gamma))) - (c/2.0)*(c/2.0));

	outfile << "camera {" << endl
			<< " location <" << (l+r)/2.0 << ", " << (b+t)/2.0 << ", " << -(dist2>dist?dist2:dist)-n << ">" << endl
			<< " look_at <" << (l+r)/2.0 << ", " << (b+t)/2.0 << ", 0>" << endl
			<< "}" << endl
//			<< "light_source { <" << (l+r)/2.0 << ", " << (b+t)/2.0 << ", " << -(dist2>dist?dist2:dist)-n << "> color White}" << endl
			<< "light_source { <" << l << ", " << t << ", " << -(dist2>dist?dist2:dist)-n << "> color White fade_distance " << (t-b)/2.0 << " fade_power 1}" << endl << endl;
}

void povengine::draw(){
	outfile.close();
}

void povengine::drawLine(const Point3D& a, const Point3D& b){
	outfile << "cylinder {" << endl
			<< " <" << a.c[0] << ", " << a.c[1] << ", " << a.c[2] << ">," << endl
			<< " <" << b.c[0] << ", " << b.c[1] << ", " << b.c[2] << ">," << endl
			<< " 0.10" << endl
			<< " texture { T_Wood1 }" << endl
			<< " finish { ambient 0.3 diffuse 0.6 }" << endl
			<< "}" << endl << endl;
}

void povengine::drawTriangle(const Point3D& a, const Point3D& b, const Point3D& c){
	outfile << "triangle {" << endl
			<< " <" << a.c[0] << ", " << a.c[1] << ", " << a.c[2] << ">," << endl
			<< " <" << b.c[0] << ", " << b.c[1] << ", " << b.c[2] << ">," << endl
			<< " <" << c.c[0] << ", " << c.c[1] << ", " << c.c[2] << ">" << endl
			<< " pigment { color Green }" << endl //    texture { T_Stone25 scale 4 }
			<< " finish { ambient 0.3 diffuse 0.6 }" << endl
			<< "}" << endl << endl;
}

void povengine::drawLinePlain(const Point3D& a, const Point3D& b){
	drawLine(a, b);
}
