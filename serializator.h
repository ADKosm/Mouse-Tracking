#ifndef SERIALIZATOR_H
#define SERIALIZATOR_H

#include <QFile>
#include <QTextStream>
#include <QPair>
#include <QVector>
#include <QPointF>

class serializator
{
public:
    serializator(QTextStream * stream);
    ~serializator();

    QTextStream * out;

    serializator * add(QString attr, int val, bool final = false);
    serializator * add(QString attr, QString val, bool final = false);
    serializator * add(QString attr, QVector< QPair<QPointF, int> > &val, bool final = false);
    serializator * add(QString attr, QVector<QPointF> val, bool final = false);
    void end();
};

#endif // SERIALIZATOR_H
