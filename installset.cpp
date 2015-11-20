#include "installset.h"


QStringList inst_mode_list = QStringList()
        << "水平"
        << "垂直";

QStringList inst_dir1_list = QStringList()
        << "正北"
        << "北偏东"
        << "正东"
        << "东偏南"
        << "正南"
        << "南偏西"
        << "正西"
        << "西偏北";

QStringList inst_dir2_list = QStringList()
        << "偏北"
        << "偏东"
        << "偏南"
        << "偏西";

InstallSet::InstallSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InstallSet)
{
    ui->setupUi(this);

    ui->comboBox_mode->addItems(inst_mode_list);
    ui->comboBox_dir1->addItems(inst_dir1_list);
    ui->comboBox_dir2->addItems(inst_dir2_list);
}

InstallSet::~InstallSet()
{
    delete ui;
}

void InstallSet::on_pushButton_save_clicked()
{
//    this->close();
    parentWidget()->show();
    delete this;
}
