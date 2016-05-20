#ifndef ITEST_H
#define ITEST_H

#include "graphicsbuttons.h"
#include "serializator.h"
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
#include <QPair>
#include <QTime>
#include <QTimer>
#include <QKeyEvent>

class ITest {
public:
    ITest() {}
    virtual ~ITest() {}
    virtual void run() = 0;
    static int getRandomNumber(int low, int high) {
        return qrand() % ((high + 1) - low) + low;
    }
    static float getRandomFloat(float low, float high) {
        return low+(float(qrand())/float(RAND_MAX))*(high-low);
    }
    static QVector2D getRandomVector(float low, float high) {
        return QVector2D(ITest::getRandomFloat(-1.0, 1.0), ITest::getRandomFloat(-1.0, 1.0)).normalized()*ITest::getRandomFloat(low, high);
    }
};

#endif // ITEST_H
