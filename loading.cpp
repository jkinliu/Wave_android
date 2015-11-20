#include "loading.h"
#include "ui_loading.h"
#include <QString>
#include <QDebug>

loading::loading(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loading)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(100);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(loadImage()));
    waitImage = new QImage;

}

loading::~loading()
{
    delete ui;
}

void loading::loadImage()
{
    static int index = 1;
    QString fileImage;
    if(index < 10)
        fileImage = QString(":/images/load00%1.png").arg(index);
    else
        fileImage = QString(":/images/load0%1.png").arg(index);

    waitImage->load(fileImage);

    index ++;
    if(index == 13)
        index = 1;

    ui->label->setPixmap(QPixmap::fromImage(*waitImage));
}
