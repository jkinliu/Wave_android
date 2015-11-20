#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include "ipset.h"
#include "installset.h"
#include "versionset.h"
#include "blockset.h"
#include "ui_setting.h"

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = 0);
    ~Setting();

private slots:
    void on_commandLinkButton_ver_clicked();

    void on_commandLinkButton_blk_clicked();

    void on_commandLinkButton_ip_clicked();

    void on_commandLinkButton_inst_clicked();

    void closeDiag();
    void closeClock();
    void saveClock();
    void closeIp();
    void saveIp();
    void closeInstall();
    void saveInstall();

private:

    IpSet *ipSet_diag;
    VersionSet *versition_diag;
    InstallSet *install_diag;
    BlockSet *block_diag;

public:
    Ui::Setting *ui;
};

#endif // SETTING_H
