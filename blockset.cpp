#include "blockset.h"


QStringList clock_source = QStringList()
        << "NTP"
        << "BD";

BlockSet::BlockSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlockSet)
{
    ui->setupUi(this);
    ui->comboBox_blk->addItems(clock_source);
}

BlockSet::~BlockSet()
{
    delete ui;
}

void BlockSet::on_pushButton_save_clicked()
{
    parentWidget()->show();
    delete this;
}
