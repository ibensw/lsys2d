#include "engine.h"
//#include <iostream>
#include <math.h>
#include <limits>
using namespace std;

#define ZTRANS -100.0f

Engine::Engine()
{
}

Engine::~Engine(){
	SDL_Quit();
}

void Engine::init(int w, int h){
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		// cout << "SDL ERROR" << endl;
		exit(1);
	}

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	if ( SDL_SetVideoMode(w, h, 0, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE) == NULL ) {
		//fprintf(stderr, "Unable to create OpenGL screen: %s\n", SDL_GetError());
		// cout << "SDL ERROR2" << endl;
		SDL_Quit();
		exit(2);
	}

	SDL_WM_SetCaption("Test", NULL);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
	glClearDepth(1.0f);				// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LEQUAL);				// The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
	//glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0f, (GLfloat)w/(GLfloat)h, 1.1f, std::numeric_limits<float>::max());
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	//glTranslatef( 0.0f, 0.0f, ZTRANS);

	//GLfloat mat_ambient[] = {0.5f, 0.5f, 0.5f, 1.0f};
	//GLfloat mat_diffuse[] = {0.4f, 0.4f, 0.4f, 1.0f};
	//GLfloat mat_specular[]= {0.8f, 0.8f, 0.8f, 1.0f};
	//GLfloat mat_shininess[]={20.0f};

	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	GLfloat lightInt[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat lightPos[] = {2.0f, 6.0f, 3.0f, 0.0f};

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightInt);

	glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION) ;
	glEnable (GL_COLOR_MATERIAL);
}

void Engine::clear(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
}

void Engine::draw(){
	/*setColor(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	// cout << left << "/" << right << endl;
	double lr=(right>-left?right:left);
	double nf=(far>-near?far:near);
	double tot=nf>lr?nf:lr;
	// cout << lr << "/" << nf << endl;
	glVertex3d(-tot, 0.0, tot);
	glVertex3d(tot, 0.0, tot);
	glVertex3d(tot, 0.0, -tot);
	glVertex3d(-tot, 0.0, -tot);
	glEnd();*/

	SDL_GL_SwapBuffers();
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//glLoadIdentity();
}

void Engine::setViewport(int x, int y, int w, int h){
	glViewport(x, y, w, h);
}

void Engine::setWindow(double l, double r, double b, double t, double n, double f){
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0f, (GLfloat)(r-l)/(GLfloat)(t-b), 0.1f, 100.0f );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();*/
	//cout << t << ", " << b << endl;
	double gamma=45.0/180.0*M_PI;
	double c=r-l;
	double dist=sqrt( (c*c) /(2*(1-cos(gamma))) - (c/2.0)*(c/2.0));
	c=t-b;
	double dist2=sqrt( (c*c) /(2*(1-cos(gamma))) - (c/2.0)*(c/2.0));
	// cout << "Z: " << dist << endl;
	// cout << n << endl;
	glTranslatef(-(l+r)/2.0, -(b+t)/2.0, -(dist2>dist?dist2:dist)-n);

	left=l;
	right=r;
	top=t;
	bottom=b;
	near=n;
	far=f;

	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(l, r, b, t);*/
	//glOrtho(l, r, b, t, -1.0, 1.0);
	//glFrustum(l, r, b, t, -100.0, 100.0);
	//gluLookAt(100.0, 100.0, 100.0, (r-l)/2.0, (t-b)/2.0, 0.0, 0.0, 1.0, 0.0);
}

void Engine::drawLinePlain(const Point3D& a, const Point3D& b){
	/* commented lines work even if length != 1 */
	
	glBegin(GL_LINES);
	glVertex3d(a.c[0], a.c[1], a.c[2]);
	glVertex3d(b.c[0], b.c[1], b.c[2]);
	glEnd();

	/*Point3D c=b-a;
	Point3D z(0.0, 0.0, 1.0);
	Point3D axis=z*c;

	//double angle=acos((c^z) / sqrt(c.LengthSquared()*z.LengthSquared()));
	double angle=acos(c^z);

	glPushMatrix();
	//glRotated(r, 0.0, 1.0, 0.0);
	glTranslated(a.c[0], a.c[1], a.c[2]);

	glRotated(angle*180/M_PI, axis.c[0], axis.c[1], axis.c[2]);

	GLUquadricObj *quadratic;
	quadratic=gluNewQuadric();
	//gluCylinder(quadratic, 0.10f, 0.10f, sqrt(c.LengthSquared()) ,32, 1);
	gluCylinder(quadratic, 0.11f, 0.11f, 1.0f ,12, 1);
	gluDeleteQuadric(quadratic);

	glPopMatrix();*/
}

void Engine::drawLine(const Point3D& a, const Point3D& b){
	/* commented lines work even if length != 1 */

	/*glBegin(GL_LINES);
	glVertex3d(a.c[0], a.c[1], a.c[2]);
	glVertex3d(b.c[0], b.c[1], b.c[2]);
	glEnd();*/

	Point3D c=b-a;
	Point3D z(0.0, 0.0, 1.0);
	Point3D axis=z*c;

	//double angle=acos((c^z) / sqrt(c.LengthSquared()*z.LengthSquared()));
	double angle=acos(c^z);

	glPushMatrix();
	//glRotated(r, 0.0, 1.0, 0.0);
	glTranslated(a.c[0], a.c[1], a.c[2]);

	glRotated(angle*180/M_PI, axis.c[0], axis.c[1], axis.c[2]);

	GLUquadricObj *quadratic;
	quadratic=gluNewQuadric();
	//gluCylinder(quadratic, 0.10f, 0.10f, sqrt(c.LengthSquared()) ,32, 1);
	gluCylinder(quadratic, 0.11f, 0.11f, 1.0f ,12, 1);
	gluDeleteQuadric(quadratic);

	glPopMatrix();
}


void Engine::drawTriangle(const Point3D& a, const Point3D& b, const Point3D& c){
	//glPushMatrix();
	//glRotated(r, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3d(a.c[0], a.c[1], a.c[2]);
	glVertex3d(b.c[0], b.c[1], b.c[2]);
	glVertex3d(c.c[0], c.c[1], c.c[2]);
	glEnd();
	//glPopMatrix();
}

void Engine::rotateY(double r){
	glRotated(r, 0.0, 1.0, 0.0);
}

void Engine::rotateX(double r){
	glRotated(r, 1.0, 0.0, 0.0);
}

void Engine::rotateZ(double r){
	glRotated(r, 0.0, 0.0, 1.0);
}

void Engine::drawText(GLint x, GLint y, char* s, GLfloat r, GLfloat g, GLfloat b){
	int lines;
	char* p;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, drawContext->w, 0.0, drawContext->h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glColor3f(r,g,b);
		glRasterPos2i(x, y);
		for(p = s, lines = 0; *p; p++) {
			if (*p == '\n') {
				++lines;
				glRasterPos2i(x, y-(lines*18));
			}
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
		}
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


void Engine::setColor(float r, float g, float b){
	glColor3f(r, g, b);
}
