#ifndef BLOCKSET_H
#define BLOCKSET_H

#include "ui_blockset.h"
#include <QDialog>

namespace Ui {
class BlockSet;
}

class BlockSet : public QDialog
{
    Q_OBJECT

public:
    explicit BlockSet(QWidget *parent = 0);
    ~BlockSet();

private slots:

    void on_pushButton_save_clicked();

public:
    Ui::BlockSet *ui;
};

#endif // BLOCKSET_H
