#include "base.h"
#include "ui_base.h"
#include <QMessageBox>

base::base(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::base)
{
    ui->setupUi(this);

    mapper = new QSignalMapper(this);

    tests.push_back(new Test1());
    tests.push_back(new Test2());

    for(int i = 0; i < tests.size(); i++) {
        QPushButton * button = new QPushButton(QString("Test %1").arg(QString::number(i+1)));
        button->setMinimumHeight(100);
        connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(button, i);
        this->ui->verticalLayout->addWidget(button);
    }

    connect(mapper, SIGNAL(mapped(int)), this, SLOT(runTest(int)));
}

base::~base()
{
    for(int i = 0; i < tests.size(); i++) delete tests[i];
    delete ui;
}

void base::runTest(int number) {
    tests[number]->run();
}
