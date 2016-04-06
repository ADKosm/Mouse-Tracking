#ifndef BASE_H
#define BASE_H

#include <QWidget>
#include "tests.h"
#include <QVector>
#include <QPushButton>
#include <QSignalMapper>

namespace Ui {
class base;
}

class base : public QWidget
{
    Q_OBJECT

public:
    explicit base(QWidget *parent = 0);
    ~base();

private:
    Ui::base *ui;
    QVector<ITest *> tests;
    QSignalMapper * mapper;

private slots:
    void runTest(int number);
};

#endif // BASE_H
