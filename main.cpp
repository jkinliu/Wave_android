#include "wave.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Wave w;
    w.exec();

    return a.exec();
}
