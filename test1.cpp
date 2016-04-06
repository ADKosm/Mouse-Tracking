#include "test1.h"
#include <QMessageBox>

Test1::Test1() {}

Test1::~Test1() {}

void Test1::run() {
    scene = new TestGraphicsScene1();
    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMouseTracking(true);
    view->showFullScreen();
}

TestGraphicsScene1::TestGraphicsScene1(QObject *parent) : QGraphicsScene(parent) {
    screenWidth = QApplication::desktop()->width();
    screenHeight = QApplication::desktop()->height();
    ballSize = 50;
    targetBallColor = QColor(Qt::red);

    this->setSceneRect(0, 0, screenWidth-2, screenHeight-2);

    recording = false;
    recordData.reserve(300);
    startButton = this->addRect(screenWidth-200, screenHeight-150, 150, 100);
    startButton->setBrush(QBrush(Qt::green));
    startButton->setPen(QPen(Qt::green));

    targetBall = this->addEllipse(0, 0, ballSize, ballSize);
    targetBall->setBrush(QBrush(targetBallColor));
    targetBall->setPen(QPen(targetBallColor));
    targetBall->hide();
}

TestGraphicsScene1::~TestGraphicsScene1() {}

void TestGraphicsScene1::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsItem * item = this->itemAt(mouseEvent->scenePos(), QTransform());

    if(!item) return;

    if(item == startButton) {
        startRecord();
    }else if(item == targetBall) {
        if(recording) stopRecord();
    }
}

void TestGraphicsScene1::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if(!recording) return;
    recordData.push_back(mouseEvent->scenePos());
}

void TestGraphicsScene1::stopRecord() {
    recording = false;
    storeData();
    recordData.clear();
    recordData.reserve(300);
    targetBall->hide();
    startButton->show();
}

void TestGraphicsScene1::storeData() {
    if(!QDir("loggedData").exists()) QDir().mkdir("loggedData");
    QString fileName = "loggedData/test_1_%1";
    int lastNumber = 1;
    while(QFile(fileName.arg(lastNumber)).exists()) lastNumber++;
    QFile file(fileName.arg(lastNumber));
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        out << "[\n";

        for(QPointF p : recordData) {
            out << QString(" [%1, %2], \n").arg(p.x()).arg(p.y());
        }
        out << QString(" [%1, %2] \n").arg(recordData.last().x()).arg(recordData.last().y());

        out << "]\n";
    }
    file.close();
}

void TestGraphicsScene1::startRecord() {
    recording = true;
    startButton->hide();

    targetBall->setPos(ITest::getRandomNumber(0, screenWidth-ballSize),
                       ITest::getRandomNumber(0, screenHeight-ballSize));
    targetBall->show();
}
