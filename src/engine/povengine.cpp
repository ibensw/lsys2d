#include "povengine.h"

using namespace std;

POVEngine::POVEngine(const char* filename, const ColorMap* cm){
	if (outfile.is_open()) outfile.close();
	outfile.open(filename);

	outfile << "global_settings { assumed_gamma 1 }" << endl;

	for (map<unsigned int, Color>::const_iterator it=cm->colors.begin(); it != cm->colors.end(); it++){
		outfile << "#declare COLOR" << (*it).first << " = rgb<" << (*it).second.r << ", " << (*it).second.g << ", " << (*it).second.b << ">;" << endl;
	}

	outfile << endl << "background { color rgb <0.196078, 0.6, 0.8> }" << endl
			<< "plane {" << endl
			<< " y, 0" << endl
			<< " pigment { color rgb<0.917647, 0.917647, 0.678431>} finish { ambient 0.35 }" << endl
			<< "}" << endl << endl;

}

void POVEngine::setWindow(double l, double r, double b, double t, double n, double f __attribute__ ((unused))){
	double gamma=45.0/180.0*M_PI;
	double c=r-l;
	double dist=sqrt( (c*c) /(2*(1-cos(gamma))) - (c/2.0)*(c/2.0));
	c=t-b;
	double dist2=sqrt( (c*c) /(2*(1-cos(gamma))) - (c/2.0)*(c/2.0));

	outfile << "camera {" << endl
			<< " location <" << (l+r)/2.0 << ", " << (b+t)/2.0 << ", " << -(dist2>dist?dist2:dist)-n << ">" << endl
			<< " look_at <" << (l+r)/2.0 << ", " << (b+t)/2.0 << ", 0>" << endl
			<< " angle 50.0" << endl
			<< "}" << endl
//			<< "light_source { <" << (l+r)/2.0 << ", " << (b+t)/2.0 << ", " << -(dist2>dist?dist2:dist)-n << "> color White}" << endl
			<< "light_source { <" << l << ", " << t << ", " << -(dist2>dist?dist2:dist)-n << "> color rgb<1, 1, 1> fade_distance " << (t-b)/2.0 << " fade_power 1}" << endl << endl;
}

void POVEngine::draw(){
	outfile.close();
}

void POVEngine::drawLine(const Line& l){
	Point3D a=points->get(l.p1);
	Point3D b=points->get(l.p2);

	outfile << "cylinder {" << endl
			<< " <" << a.c[0] << ", " << a.c[1] << ", " << a.c[2] << ">," << endl
			<< " <" << b.c[0] << ", " << b.c[1] << ", " << b.c[2] << ">," << endl
			<< " "<< l.thickness << endl
			<< " pigment { color COLOR" << l.color << " }" << endl
			<< " finish { ambient 0.3 diffuse 0.6 }" << endl
			<< "}" << endl;

	outfile << "sphere {" << endl
			<< " <" << a.c[0] << ", " << a.c[1] << ", " << a.c[2] << ">," << endl
			<< " " << l.thickness << endl
			<< " pigment { color COLOR" << l.color << " }" << endl
			<< " finish { ambient 0.3 diffuse 0.6 }" << endl
			<< "}" << endl;

	outfile << "sphere {" << endl
			<< " <" << b.c[0] << ", " << b.c[1] << ", " << b.c[2] << ">," << endl
			<< " " << l.thickness << endl
			<< " pigment { color COLOR" << l.color << " }" << endl
			<< " finish { ambient 0.3 diffuse 0.6 }" << endl
			<< "}" << endl;
}

void POVEngine::drawTriangle(const Triangle& l){
	Point3D a=points->get(l.p1);
	Point3D b=points->get(l.p2);
	Point3D c=points->get(l.p3);

	outfile << "triangle {" << endl
			<< " <" << a.c[0] << ", " << a.c[1] << ", " << a.c[2] << ">," << endl
			<< " <" << b.c[0] << ", " << b.c[1] << ", " << b.c[2] << ">," << endl
			<< " <" << c.c[0] << ", " << c.c[1] << ", " << c.c[2] << ">" << endl
			<< " pigment { color COLOR" << l.color << " }" << endl //    texture { T_Stone25 scale 4 }
			<< " finish { ambient 0.3 diffuse 0.6 }" << endl
			<< "}" << endl << endl;
}

void POVEngine::drawLinePlain(const Line& l){
	drawLine(l);
}
