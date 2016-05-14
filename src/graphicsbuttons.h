#ifndef GRAPHICSBUTTONS_H
#define GRAPHICSBUTTONS_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsItem>

class startButton {
public:
    startButton();
    ~startButton();

    void show();
    void hide();
    void buildButton(int x, int y, int width, int height, QGraphicsScene * scene);

    void remove();

    bool equal(QGraphicsItem * item);
private:
    QGraphicsTextItem * text;
    QGraphicsRectItem * rect;
};

#endif // GRAPHICSBUTTONS_H
