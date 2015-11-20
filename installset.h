#ifndef INSTALLSET_H
#define INSTALLSET_H

#include <QDialog>
#include "ui_installset.h"

namespace Ui {
class InstallSet;
}

class InstallSet : public QDialog
{
    Q_OBJECT

public:
    explicit InstallSet(QWidget *parent = 0);
    ~InstallSet();

private slots:

    void on_pushButton_save_clicked();

public:
    Ui::InstallSet *ui;
};

#endif // INSTALLSET_H
