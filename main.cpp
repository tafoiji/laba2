#include "laba2gui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Laba2Gui w;
    w.show();
    return a.exec();
}
