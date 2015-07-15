#include "qnnui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QNNUI w;
    w.show();

    return a.exec();
}
