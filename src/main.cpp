#include <QTime>
#include <QApplication>
#include "base.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    base w;
    w.show();

    return a.exec();
}
