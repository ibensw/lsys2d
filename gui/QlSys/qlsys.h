#ifndef QLSYS_H
#define QLSYS_H

#include <QtGui/QMainWindow>
#include <QString>
#include "../../src/lsystem.h"
#include "../../src/engine/oglengine.h"

namespace Ui
{
    class QlSysClass;
}

class QlSys : public QMainWindow
{
    Q_OBJECT

public:
    QlSys(QWidget *parent = 0);
    ~QlSys();

private:
    Ui::QlSysClass *ui;
    LSystem* lsys;
    OGLEngine* opengl;
    void doiterate(int i);
    void docalculate();
    void dorender();

public slots:
    void iterationsChanged(int);
    void renderClicked();
    void renderCloseClicked();
    void expPovClicked();
    void povRenClicked();
    void openClicked();
    void testRerender();
};

#endif // QLSYS_H
