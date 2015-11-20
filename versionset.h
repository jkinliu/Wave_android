#ifndef VERSIONSET_H
#define VERSIONSET_H

#include <QDialog>
#include "ui_versionset.h"

namespace Ui {
class VersionSet;
}

class VersionSet : public QDialog
{
    Q_OBJECT

public:
    explicit VersionSet(QWidget *parent = 0);
    ~VersionSet();

private slots:
    void closeDiag();

    void on_pushButton_save_clicked();

public:
    Ui::VersionSet *ui;
};

#endif // VERSIONSET_H
