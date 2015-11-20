#ifndef FILEANALYSIS_H
#define FILEANALYSIS_H

#include <QDialog>
#include <QFileSystemModel>
#include <QTreeView>
#include <QStringList>
#include "analysis.h"
#include "ui_fileanalysis.h"

namespace Ui {
class FileAnalysis;
}

class FileAnalysis : public QDialog
{
    Q_OBJECT

public:
    explicit FileAnalysis(QWidget *parent = 0);
    ~FileAnalysis();

private:
    void init_treeView();

private slots:
    void closeDiag();

    void on_treeView_doubleClicked(const QModelIndex &index);

private:

    QFileSystemModel *fileModel;
    QTreeView *treeView;
    Analysis *analysis_diag;

public:
    Ui::FileAnalysis *ui;
};

#endif // FILEANALYSIS_H
