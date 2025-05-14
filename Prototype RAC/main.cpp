#include "RACGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RACGUI w;
    w.show();
    return a.exec();
}
