#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QDialog>
#include <QTableView>
#include <QStandardItemModel>
#include "ui_download.h"
#include "ftp.h"

namespace Ui {
class download;
}

class download : public QDialog
{
    Q_OBJECT

public:
    explicit download(QWidget *parent = 0);
    ~download();

    void openDir();

private:
    void setHearderItem();

private slots:
    void closeDiag();
    void ftp_lists(QList<file_info> &info);

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
//    Ui::download *ui;
    QTableView *tableView;
    QStandardItemModel *model;

public:
    Ui::download *ui;
    Ftp *ftp;

};

#endif // DOWNLOAD_H
