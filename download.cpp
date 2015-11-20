#include "download.h"


download::download(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::download)
{
    ui->setupUi(this);

    tableView = ui->tableView;
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    model = new QStandardItemModel(tableView);
    tableView->setModel(model);
    setHearderItem();
}

download::~download()
{
    delete ui;
}

void download::openDir()
{
    connect(ftp, &Ftp::file_lists,          this, &download::ftp_lists);
    ftp->cd_dir("/");
}

void download::setHearderItem()
{
    model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("文件名")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("文件类型")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("文件大小")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("最近修改")));

    tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
}

void download::closeDiag()
{

}

void download::ftp_lists(QList<file_info> &info)
{
    QString path = ftp->get_dir();
    int i,j;
    int fileSize = info.size();

    model->clear();
    this->setHearderItem();
    j = 0;
    if(path != "/")
    {
        model->setItem(0, new QStandardItem("[上级目录]"));
        j = 1;
    }

    for(i = 0;i < fileSize; i++,j++)
    {
        model->setItem(j,0,new QStandardItem(info.at(i).name));
        if(info.at(i).is_dir)
        {
            model->setItem(j,1,new QStandardItem("目录"));
        }
        else
        {
            model->setItem(j,1,new QStandardItem("文件"));
            model->setItem(j,2,new QStandardItem(QString("%1").arg(info.at(i).size)));
        }
        model->setItem(j,3,new QStandardItem(info.at(i).lastTime));
    }
}


void download::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString path = ftp->get_dir();
    if(path != "/" && index.row() == 0)
    {
        int lastIndex = path.lastIndexOf("/");
        if(lastIndex != 0)
            path = path.mid(0,lastIndex);
        else
           path = path.mid(0,lastIndex+1);
        ftp->cd_dir(path);
        return ;
    }
    QString type = model->item(index.row(),1)->text();   // get type
    if(type == "目录")
    {
        if(path.size() != path.lastIndexOf("/") + 1)
        {
           path += "/";
        }
        path += model->item(index.row())->text();  // get name
        ftp->cd_dir(path);
    }
}
