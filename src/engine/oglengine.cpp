#include "oglengine.h"
#include <math.h>
#include <limits>
using namespace std;

#define ZTRANS -100.0f

void (*quitf)(void*)=0;
void* argument;

int SDL_Process(const SDL_Event *event){
	switch(event->type){
		case SDL_VIDEORESIZE:
			glViewport(0, 0, event->resize.w, event->resize.h);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective( 50.0f, (GLfloat)event->resize.w/(GLfloat)event->resize.h, 1.1f, std::numeric_limits<float>::max());
			glMatrixMode( GL_MODELVIEW );
		break;
		case SDL_QUIT:
			if (quitf){
				quitf(argument);
			}
		break;
		default:
			return 1;
	}
	return 0;
}

OGLEngine::OGLEngine(int w, int h, string caption){
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		// cout << "SDL ERROR" << endl;
		throw("Could not initialize SDL");
	}

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	if ( SDL_SetVideoMode(w, h, 0, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE) == NULL ) {
		//fprintf(stderr, "Unable to create OpenGL screen: %s\n", SDL_GetError());
		// cout << "SDL ERROR2" << endl;
		SDL_Quit();
		throw(SDL_GetError());
	}

	SDL_WM_SetCaption(caption.c_str(), NULL);
	SDL_SetEventFilter(SDL_Process);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
	glClearDepth(1.0f);				// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LEQUAL);				// The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
	//glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 50.0f, (GLfloat)w/(GLfloat)h, 1.1f, std::numeric_limits<float>::max());
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

	GLfloat lightInt[] = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat lightPos[] = {2.0f, 6.0f, 3.0f, 0.0f};

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightInt);

	glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION) ;
	glEnable (GL_COLOR_MATERIAL);
}

OGLEngine::~OGLEngine(){
	SDL_Quit();
}


void OGLEngine::clear(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
}

void OGLEngine::draw(){
	SDL_GL_SwapBuffers();
}

void OGLEngine::setViewport(int x, int y, int w, int h){
	glViewport(x, y, w, h);
}

void OGLEngine::setWindow(double l, double r, double b, double t, double n, double f){
	double gamma=45.0/180.0*M_PI; //Viewing angle
	double c=r-l;
	double dist=sqrt( (c*c) /(2.0*(1.0-cos(gamma))) - (c/2.0)*(c/2.0));
	c=t-b;
	double dist2=sqrt( (c*c) /(2.0*(1.0-cos(gamma))) - (c/2.0)*(c/2.0));
	// cout << "Z: " << dist << endl;
	// cout << n << endl;
	glTranslatef(-(l+r)/2.0, -(b+t)/2.0, -(dist2>dist?dist2:dist)-n);

	left=l;
	right=r;
	top=t;
	bottom=b;
	near=n;
	far=f;
}

void OGLEngine::drawLinePlain(const Line& l){
	glPushMatrix();
	glRotated(rotX, 1.0, 0.0, 0.0);
	glRotated(rotY, 0.0, 1.0, 0.0);
	glRotated(rotZ, 0.0, 0.0, 1.0);

	Point3D a=points->get(l.p1);
	Point3D b=points->get(l.p2);
	
	glBegin(GL_LINES);
	glVertex3d(a.c[0], a.c[1], a.c[2]);
	glVertex3d(b.c[0], b.c[1], b.c[2]);
	glEnd();
	glPopMatrix();
}

void OGLEngine::drawLine(const Line& l){
	if (plain)
		return drawLinePlain(l);

	Point3D a=points->get(l.p1);
	Point3D b=points->get(l.p2);

	Point3D c=b-a;
	Point3D z(0.0, 0.0, 1.0);
	Point3D axis=z*c;

	double angle=acos((c^z) / sqrt(c.LengthSquared()*z.LengthSquared()));

	glPushMatrix();
	glRotated(rotX, 1.0, 0.0, 0.0);
	glRotated(rotY, 0.0, 1.0, 0.0);
	glRotated(rotZ, 0.0, 0.0, 1.0);
	glTranslated(a.c[0], a.c[1], a.c[2]);

	glRotated(angle*180/M_PI, axis.c[0], axis.c[1], axis.c[2]);

	GLUquadricObj *quadratic;
	quadratic=gluNewQuadric();
	gluCylinder(quadratic, l.thickness, l.thickness, sqrt(c.LengthSquared()) ,32, 1);
	gluDeleteQuadric(quadratic);

	if (roundcyls){
		GLUquadricObj *quadratic2;
		quadratic2=gluNewQuadric();
		gluSphere(quadratic2, l.thickness, 32, 32);
		gluDeleteQuadric(quadratic2);

		glTranslated(0, 0, sqrt(c.LengthSquared()));
		GLUquadricObj *quadratic3;
		quadratic3=gluNewQuadric();
		gluSphere(quadratic3, l.thickness, 32, 32);
		gluDeleteQuadric(quadratic3);

	}

	glPopMatrix();
}


void OGLEngine::drawTriangle(const Triangle& l){
	glPushMatrix();
	glRotated(rotX, 1.0, 0.0, 0.0);
	glRotated(rotY, 0.0, 1.0, 0.0);
	glRotated(rotZ, 0.0, 0.0, 1.0);

	Point3D a=points->get(l.p1);
	Point3D b=points->get(l.p2);
	Point3D c=points->get(l.p3);

	glBegin(GL_POLYGON);
	glVertex3d(a.c[0], a.c[1], a.c[2]);
	glVertex3d(b.c[0], b.c[1], b.c[2]);
	glVertex3d(c.c[0], c.c[1], c.c[2]);
	glEnd();
	glPopMatrix();
}

void OGLEngine::rotateY(double r){
	//glRotated(r, 0.0, 1.0, 0.0);
	rotY=r;
}

void OGLEngine::rotateX(double r){
	rotX=r;
}

void OGLEngine::rotateZ(double r){
	rotZ=r;
}

void OGLEngine::setColor(float r, float g, float b){
	glColor3f(r, g, b);
}

void OGLEngine::onQuit(void (*f)(void*), void* arg){
	argument=arg;
	quitf=f;
}

