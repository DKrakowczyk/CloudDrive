#include "serwer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    serwer w;
    w.show();

    return a.exec();
}
