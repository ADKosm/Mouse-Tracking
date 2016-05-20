#ifndef TEST2_H
#define TEST2_H

#include "ITest.h"

class TestGraphicsScene2 : public QGraphicsScene {
    Q_OBJECT
public:
    explicit TestGraphicsScene2(QObject *parent = 0);
    ~TestGraphicsScene2();

    void setObjects();
private:
    int screenWidth;
    int screenHeight;
    int ballSize;
    int extraBallsSize;
    int extraBallsNumber;
    QColor targetBallColor;
    QColor extraBallsColor;
    bool recording;

    float minV;
    float maxV;

    startButton * sButton;
    QGraphicsEllipseItem * targetBall;
    QVector<QGraphicsEllipseItem *> extraBalls;
    QVector<QVector2D> extraVelocities;
    QVector2D targetVelocity;
    QGraphicsTextItem * escText;
    QTime time;
    QDateTime time_id;

    QTimer* stepRunner;

    QVector< QPair<QPointF, int> > recordData;
    QVector< QPair<QPointF, int> > ballData;

    void startRecord();
    void stopRecord();
    void storeData();

    QRect getAvailableGeometry(QGraphicsScene * scene);
    QVector<QPointF> transformToPoints(QVector<QGraphicsEllipseItem *> vec);

private slots:
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void keyPressEvent(QKeyEvent *event);

    void step();
};

class Test2: public ITest {
private:
    QGraphicsView * view;
    TestGraphicsScene2 * scene;
public:
    Test2();
    void run();
    ~Test2();
};

#endif // TEST2_H
