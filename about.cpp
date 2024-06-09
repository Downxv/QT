#include "about.h"
#include "ui_about.h"
#include<qDebug>

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    this->movie = new QMovie(":/rs/a.gif");
    ui->label_2->setMovie(this->movie);
    this->movie->start();
    qDebug() << "set movie";
}

about::~about()
{
    delete ui;
}
