#include "ipset.h"


IpSet::IpSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IpSet)
{
    ui->setupUi(this);
}

IpSet::~IpSet()
{
    delete ui;
}

void IpSet::on_pushButton_save_clicked()
{
    parentWidget()->show();
    delete this;
}
