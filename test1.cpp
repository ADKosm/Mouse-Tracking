#include "test1.h"
#include <QMessageBox>

Test1::Test1() {
    scene = new TestGraphicsScene1();
    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMouseTracking(true);
}

Test1::~Test1() {}

void Test1::run() {
    view->showFullScreen();
    scene->setObjects();
}

TestGraphicsScene1::TestGraphicsScene1(QObject *parent) : QGraphicsScene(parent) {
    ballSize = 50;
    targetBallColor = QColor(Qt::red);

    recording = false;
    recordData.reserve(300);
}

TestGraphicsScene1::~TestGraphicsScene1() {}

QRect TestGraphicsScene1::getAvailableGeometry(QGraphicsScene *scene) {
    QDesktopWidget dwidget;
    return dwidget.availableGeometry(scene->views()[0]);
}

void TestGraphicsScene1::setObjects() {
    QRect geometry = this->getAvailableGeometry(this);

    screenWidth = geometry.width();
    screenHeight = geometry.height();

    this->setSceneRect(0, 0, screenWidth-2, screenHeight-2);

    sButton = new startButton();
    sButton->buildButton(screenWidth-200, screenHeight-150, 150, 100, this);

    targetBall = this->addEllipse(0, 0, ballSize, ballSize);
    targetBall->setBrush(QBrush(targetBallColor));
    targetBall->setPen(QPen(targetBallColor));
    targetBall->hide();

    escText = this->addText("Press Esc to close test");
    escText->setPos(0, 0);
}

void TestGraphicsScene1::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsItem * item = this->itemAt(mouseEvent->scenePos(), QTransform());

    if(!item) return;

    if(sButton->equal(item)) {
        startRecord();
    }else if(item == targetBall) {
        if(recording) stopRecord();
    }
}

void TestGraphicsScene1::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if(!recording) return;
    recordData.push_back(qMakePair(mouseEvent->scenePos(), time.elapsed()));
}

void TestGraphicsScene1::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Escape) {
        sButton->remove();
        this->removeItem(targetBall);
        this->removeItem(escText);

        delete sButton;
        delete targetBall;
        delete escText;

        this->views()[0]->close();
    }
}

void TestGraphicsScene1::stopRecord() {
    recording = false;
    storeData();
    recordData.clear();
    recordData.reserve(300);
    targetBall->hide();
    sButton->show();
}

void TestGraphicsScene1::storeData() {
    if(!QDir("loggedData").exists()) QDir().mkdir("loggedData");
    if(!QDir("loggedData/test_1").exists()) QDir().mkdir("loggedData/test_1");
    QString fileName = "loggedData/test_1/%1.test";
    int lastNumber = 1;
    while(QFile(fileName.arg(lastNumber)).exists()) lastNumber++;
    QFile file(fileName.arg(lastNumber));

    if(file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        serializator s(&out);

        s.add("test", lastNumber)
                ->add("desc", "First test. One red ball")
                ->add("ballSize", ballSize)
                ->add("ballX", targetBall->pos().x())
                ->add("ballY", targetBall->pos().y())
                ->add("screenWidth", screenWidth)
                ->add("screenHeight", screenHeight)
                ->add("data", recordData, true)
                ->end();
    }
    file.close();
}

void TestGraphicsScene1::startRecord() {
    recording = true;
    sButton->hide();

    time.start();

    targetBall->setPos(ITest::getRandomNumber(0, screenWidth-ballSize),
                       ITest::getRandomNumber(0, screenHeight-ballSize));
    targetBall->show();
}
