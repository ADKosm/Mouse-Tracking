#include "graphicsbuttons.h"

startButton::startButton() {
}

startButton::~startButton() {
    delete rect;
    delete text;
}

void startButton::show() {
    text->show();
    rect->show();
}

void startButton::hide() {
    text->hide();
    rect->hide();
}

void startButton::buildButton(int x, int y, int width, int height, QGraphicsScene *scene) {
    rect = scene->addRect(x, y, width, height, QPen(Qt::green), QBrush(Qt::green));
    text = scene->addText("Start");
    text->setFont(QFont("Arial", 20, QFont::Bold));
    text->setPos(rect->boundingRect().center().x()-text->boundingRect().width()/2, rect->boundingRect().center().y()-text->boundingRect().height()/2);
}

bool startButton::equal(QGraphicsItem * item) {
    return (this->rect == item) || (this->text == item);
}

void startButton::remove() {
    rect->scene()->removeItem(rect);
    text->scene()->removeItem(text);
}
