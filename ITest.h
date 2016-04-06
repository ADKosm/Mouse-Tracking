#ifndef ITEST_H
#define ITEST_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDesktopWidget>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QDir>
#include <QFile>
#include <QTextStream>

class ITest {
public:
    ITest() {}
    virtual ~ITest() {}
    virtual void run() = 0;
    static int getRandomNumber(int low, int high) {
        return qrand() % ((high + 1) - low) + low;
    }
};

#endif // ITEST_H
