#ifndef IPSET_H
#define IPSET_H

#include <QDialog>
#include "ui_ipset.h"

namespace Ui {
class IpSet;
}

class IpSet : public QDialog
{
    Q_OBJECT

public:
    explicit IpSet(QWidget *parent = 0);
    ~IpSet();

private slots:
    void on_pushButton_save_clicked();

public:
    Ui::IpSet *ui;
};

#endif // IPSET_H
