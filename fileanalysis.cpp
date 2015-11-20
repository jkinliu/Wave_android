#include "fileanalysis.h"


FileAnalysis::FileAnalysis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileAnalysis)
{
    ui->setupUi(this);
    init_treeView();
}

FileAnalysis::~FileAnalysis()
{
    delete ui;
}

void FileAnalysis::init_treeView()
{
    fileModel = new QFileSystemModel(this);
    treeView = ui->treeView;
    fileModel->setRootPath("");
    treeView->setModel(fileModel);
    treeView->setColumnWidth(0,200);

    // 设置过滤器
    QStringList filter;
    filter << "*.mseed";
    fileModel->setNameFilters(filter);
    fileModel->setNameFilterDisables(false);
}

void FileAnalysis::closeDiag()
{
    this->show();
    analysis_diag->close();
}

void FileAnalysis::on_treeView_doubleClicked(const QModelIndex &index)
{
    if(fileModel->type(index) == "mseed File")
    {
        this->hide();
        analysis_diag = new Analysis(this);
        analysis_diag->analysisWave(fileModel->filePath(index),fileModel->fileName(index));
        connect(analysis_diag->ui->pushButton_back,SIGNAL(clicked()),this,SLOT(closeDiag()));
        analysis_diag->exec();
//        this->show();
    }
}
