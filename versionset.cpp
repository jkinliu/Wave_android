#include "versionset.h"


VersionSet::VersionSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VersionSet)
{
    ui->setupUi(this);
}

VersionSet::~VersionSet()
{
    delete ui;
}

void VersionSet::closeDiag()
{
//    parentWidget()->show();
//    delete this;
}

void VersionSet::on_pushButton_save_clicked()
{
//    parentWidget()->show();
//    delete this;
}
