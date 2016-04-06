#ifndef TEST1_H
#define TEST1_H

#include "ITest.h"

class TestGraphicsScene1 : public QGraphicsScene {
    Q_OBJECT
public:
    explicit TestGraphicsScene1(QObject *parent = 0);
    ~TestGraphicsScene1();
private:
    int screenWidth;
    int screenHeight;
    int ballSize;
    QColor targetBallColor;
    bool recording;
    QGraphicsRectItem * startButton;
    QGraphicsEllipseItem * targetBall;

    QVector<QPointF> recordData;

    void startRecord();
    void stopRecord();
    void storeData();
private slots:
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
};

class Test1: public ITest {
private:
    QGraphicsView * view;
    TestGraphicsScene1 * scene;
public:
    Test1();
    void run();
    ~Test1();
};

#endif // TEST1_H
