#ifndef LSWIDGET_H
#define LSWIDGET_H

#include <QGLWidget>
#include "../../src/engine/engine.h"

class LSWidget : public QGLWidget
{
	Q_OBJECT

	public:
		LSWidget(QWidget *parent);
		~LSWidget();

	protected:
		void initializeGL();
		void resizeGL(int w, int h);
		void paintGL();

	private:
		Engine opengl;
};

#endif // LSWIDGET_H
