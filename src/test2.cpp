#include "test2.h"
#include <QMessageBox>

Test2::Test2() {
    scene = new TestGraphicsScene2();
    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMouseTracking(true);
}

Test2::~Test2() {}

void Test2::run() {
    view->showFullScreen();
    scene->setObjects();
}

TestGraphicsScene2::TestGraphicsScene2(QObject *parent) : QGraphicsScene(parent) {
    ballSize = 50;
    extraBallsSize = 50;
    extraBallsNumber = 5;

    minV = 2.0;
    maxV = 6.0;

    targetBallColor = QColor(Qt::red);
    extraBallsColor = QColor(Qt::blue);

    recording = false;
    recordData.reserve(300);
    ballData.reserve(300);
}

TestGraphicsScene2::~TestGraphicsScene2() {
}

QRect TestGraphicsScene2::getAvailableGeometry(QGraphicsScene *scene) {
    QDesktopWidget dwidget;
    return dwidget.availableGeometry(scene->views()[0]);
}

QVector<QPointF> TestGraphicsScene2::transformToPoints(QVector<QGraphicsEllipseItem *> vec) {
    QVector<QPointF> result;
    for(QGraphicsItem * e : vec) result.push_back(e->pos());
    return result;
}

void TestGraphicsScene2::setObjects() {
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

    targetVelocity = ITest::getRandomVector(minV, maxV);

    for(int i = 0; i < extraBallsNumber; i++) {
        QGraphicsEllipseItem * el = this->addEllipse(0, 0, extraBallsSize, extraBallsSize);
        el->setBrush(QBrush(extraBallsColor));
        el->hide();
        extraBalls.push_back(el);
        
        QVector2D vel = ITest::getRandomVector(minV, maxV);

        extraVelocities.push_back(vel);
    }

    escText = this->addText("Press Esc to close test");
    escText->setPos(0, 0);

    time_id = QDateTime::currentDateTime();

    stepRunner = new QTimer(this);
    connect(stepRunner, SIGNAL(timeout()), this, SLOT(step()));
    stepRunner->start(20);
}

void TestGraphicsScene2::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsItem * item = this->itemAt(mouseEvent->scenePos(), QTransform());

    if(!item) return;

    if(sButton->equal(item)) {
        startRecord();
    }else if(item == targetBall) {
        if(recording) stopRecord();
    }
}

void TestGraphicsScene2::step() {
    for(int i = 0; i < extraVelocities.size(); i++) {
        if(extraBalls[i]->x() > screenWidth-extraBallsSize || extraBalls[i]->x() < 0 || extraBalls[i]->y() < 0 || extraBalls[i]->y() > screenHeight-extraBallsSize) {
            extraBalls[i]->setPos(ITest::getRandomNumber(0, screenWidth-extraBallsSize),
                      ITest::getRandomNumber(0, screenHeight-extraBallsSize));
            extraVelocities[i] = ITest::getRandomVector(minV, maxV);
        }
    }
    if(targetBall->x() > screenWidth - ballSize || targetBall->x() < 0 || targetBall->y() < 0 || targetBall->y() > screenHeight - ballSize) {
        targetBall->setPos(ITest::getRandomNumber(0, screenWidth-ballSize),
                  ITest::getRandomNumber(0, screenHeight-ballSize));
        targetVelocity = ITest::getRandomVector(minV, maxV);
        ballSize = ITest::getRandomNumber(5, 200);
        targetBall->setRect(0, 0, ballSize, ballSize);

        recordData.clear();
        recordData.reserve(300);
        ballData.clear();
        ballData.reserve(300);
    }

    for(int i = 0; i < extraVelocities.size(); i++) {
        extraBalls[i]->setPos( (extraVelocities[i]+QVector2D(extraBalls[i]->pos())).toPoint() );
    }
    targetBall->setPos( (targetVelocity+QVector2D(targetBall->pos())).toPoint() );
}

void TestGraphicsScene2::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if(!recording) return;
    recordData.push_back(qMakePair(mouseEvent->scenePos(), time.elapsed()));
    ballData.push_back(qMakePair(targetBall->pos(), time.elapsed()));
}

void TestGraphicsScene2::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Escape) {
        stepRunner->stop();
        sButton->remove();
        this->removeItem(targetBall);
        this->removeItem(escText);
        for(QGraphicsEllipseItem * e : extraBalls) this->removeItem(e);

        delete sButton;
        delete targetBall;
        delete escText;
        delete stepRunner;
        for(QGraphicsEllipseItem * e : extraBalls) delete e;
        extraBalls.clear();
        extraVelocities.clear();

        this->views()[0]->close();
    }
}

void TestGraphicsScene2::stopRecord() {
    recording = false;
    storeData();
    recordData.clear();
    recordData.reserve(300);
    ballData.clear();
    ballData.reserve(300);
    startRecord();
}

void TestGraphicsScene2::storeData() {
    QString path_to_folder = QString("loggedData/test_2/%1").arg(time_id.toString("ddMMhhmmss"));
    QString fileName = QString("%1/%2.test").arg(path_to_folder);

    if(!QDir(path_to_folder).exists()) QDir().mkpath(path_to_folder);

    int lastNumber = 1;
    while(QFile(fileName.arg(lastNumber)).exists()) lastNumber++;
    QFile file(fileName.arg(lastNumber));


    if(file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        serializator s(&out);



        s.add("test", lastNumber)
                ->add("desc", "Second test. One red ball and some blue balls")
                ->add("ballSize", ballSize)
                ->add("screenWidth", screenWidth)
                ->add("screenHeight", screenHeight)
                ->add("extraBallsSize", extraBallsSize)
                ->add("extraBallsNumber", extraBallsNumber)
                ->add("extraBalls", transformToPoints(extraBalls))
                ->add("data", recordData)
                ->add("ballData", ballData, true)
                ->end();
    }
    file.close();
}

void TestGraphicsScene2::startRecord() {
    recording = true;
    sButton->hide();

    time.start();

    for(QGraphicsEllipseItem * e : extraBalls) {
        e->show();
    }

    ballSize = ITest::getRandomNumber(5, 200);

    targetBall->setPos(ITest::getRandomNumber(0, screenWidth-ballSize),
                       ITest::getRandomNumber(0, screenHeight-ballSize));
    targetVelocity = ITest::getRandomVector(minV, maxV);
    targetBall->setRect(0, 0, ballSize, ballSize);
    targetBall->show();
}
