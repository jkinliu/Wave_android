#include "setting.h"
#include <QDebug>


Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
}

Setting::~Setting()
{
    delete ui;
}

void Setting::on_commandLinkButton_ver_clicked()
{
    this->hide();
    versition_diag = new VersionSet(this);
    connect(versition_diag->ui->pushButton_back,SIGNAL(clicked()),this,SLOT(closeDiag()));
    connect(versition_diag->ui->pushButton_save,SIGNAL(clicked()),this,SLOT(closeDiag()));
    versition_diag->ui->label->setText(ui->commandLinkButton_ver->text());
    versition_diag->show();
}

void Setting::on_commandLinkButton_blk_clicked()
{
    this->hide();
    block_diag = new BlockSet(this);
    connect(block_diag->ui->pushButton_back,SIGNAL(clicked()),this,SLOT(closeClock()));
    connect(block_diag->ui->pushButton_save,SIGNAL(clicked()),this,SLOT(saveClock()));
    block_diag->ui->label_title->setText(ui->commandLinkButton_blk->text());
    block_diag->show();
}

void Setting::on_commandLinkButton_ip_clicked()
{
    this->hide();
    ipSet_diag = new IpSet(this);
    connect(ipSet_diag->ui->pushButton_back,SIGNAL(clicked()),this,SLOT(closeIp()));
    connect(ipSet_diag->ui->pushButton_back,SIGNAL(clicked()),this,SLOT(saveIp()));
    ipSet_diag->ui->label->setText(ui->commandLinkButton_ip->text());
    ipSet_diag->show();
}

void Setting::on_commandLinkButton_inst_clicked()
{
    this->hide();
    install_diag = new InstallSet(this);
    connect(install_diag->ui->pushButton_back,SIGNAL(clicked()),this,SLOT(closeInstall()));
    connect(install_diag->ui->pushButton_back,SIGNAL(clicked()),this,SLOT(saveInstall()));
    install_diag->ui->label->setText(ui->commandLinkButton_inst->text());
    install_diag->show();
}

void Setting::closeDiag()
{
    this->show();
    versition_diag->close();
}

void Setting::closeClock()
{
    this->show();
    block_diag->close();
}

void Setting::saveClock()
{
    closeClock();
}

void Setting::closeIp()
{
    this->show();
    ipSet_diag->close();
}

void Setting::saveIp()
{
    closeIp();
}

void Setting::closeInstall()
{
    this->show();
    install_diag->close();
}

void Setting::saveInstall()
{
    closeInstall();
}
