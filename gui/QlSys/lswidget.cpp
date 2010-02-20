#include "lswidget.h"

LSWidget::LSWidget(QWidget *parent):
		QGLWidget(parent)
{
}

LSWidget::~LSWidget(){
}

void LSWidget::initializeGL(){
	opengl.init(100, 100);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3d(50, 50, 0);
	glVertex3d(100, 100, 0);
	glEnd();
}

void LSWidget::resizeGL(int w, int h){
	opengl.init(w, h);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3d(50, 50, 0);
	glVertex3d(100, 100, 0);
	glEnd();
}
void LSWidget::paintGL(){
	//opengl.init(100, 100, false);
	//opengl.draw();
}
