#include <QtGui/QApplication>
#include "qlsys.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QlSys w;
    w.show();
    return a.exec();
}
