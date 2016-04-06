#ifndef TEST1_H
#define TEST1_H

#include "ITest.h"

class TestGraphicsScene1 : public QGraphicsScene {
    Q_OBJECT
public:
    explicit TestGraphicsScene1(QObject *parent = 0);
    ~TestGraphicsScene1();

    void setObjects();
private:
    int screenWidth;
    int screenHeight;
    int ballSize;
    QColor targetBallColor;
    bool recording;
    startButton * sButton;
    QGraphicsEllipseItem * targetBall;
    QGraphicsTextItem * escText;
    QTime time;

    QVector< QPair<QPointF, int> > recordData;

    void startRecord();
    void stopRecord();
    void storeData();

    QRect getAvailableGeometry(QGraphicsScene * scene);
private slots:
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void keyPressEvent(QKeyEvent *event);
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
