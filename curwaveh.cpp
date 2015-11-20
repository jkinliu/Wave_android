#include "curwaveh.h"
#include "qwt_plot.h"
#include <QDebug>


CurWaveH::CurWaveH(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CurWaveH)
{
    ui->setupUi(this);

    plot = new Plot(ui->qwtPlot);

    interval_xCur = new QwtInterval(0, 10);
    interval_yCur = new QwtInterval(-1, 1);

    plot->set_title("Time(s)", "g");
    plot->set_x_scale(interval_xCur->minValue(),interval_xCur->maxValue());
    plot->set_y_scale(interval_yCur->minValue(), interval_yCur->maxValue());

    mouse_timer = new QTimer;
    connect(mouse_timer,SIGNAL(timeout()),this,SLOT(mousePressedTimeOut()));
    timeOutFlag = false;
}

CurWaveH::~CurWaveH()
{
    delete ui;
}

void CurWaveH::closeDiag()
{
    this->close();
}

void CurWaveH::on_toolButton_func_clicked()
{
    QPoint p;
    func_menu = new QMenu();

    QAction *download = func_menu->addAction("波形下载");
    QAction *analysis = func_menu->addAction("波形分析");
    QAction *setting = func_menu->addAction("设置");
    p.setX(this->mapToGlobal(ui->toolButton_func->pos()).x()+ui->toolButton_func->width()-107);
    p.setY(this->mapToGlobal(ui->toolButton_func->pos()).y()+ui->toolButton_func->height());

    connect(download, SIGNAL(triggered(bool)), this, SLOT(openDownloadDialog()));
    connect(analysis, SIGNAL(triggered(bool)), this, SLOT(openAnalysisDialog()));
    connect(setting, SIGNAL(triggered(bool)), this, SLOT(openSettingDialog()));
    func_menu->exec(p);

}

void CurWaveH::openDownloadDialog()
{
    this->close();
    download_diag = new download(this);
    download_diag->exec();
//    this->exec();
}

void CurWaveH::openAnalysisDialog()
{
    this->close();
    fileAnalysis_diag = new FileAnalysis(this);
    fileAnalysis_diag->exec();
//    this->exec();
}

void CurWaveH::openSettingDialog()
{
    this->close();
    setting_diag = new Setting(this);
    setting_diag->exec();

}

void CurWaveH::mousePressedTimeOut()
{
    timeOutFlag = true;
//    qDebug()<<__func__<<timeOutFlag;
    mouse_timer->stop();
}

void CurWaveH::mousePressEvent(QMouseEvent *event)
{
//    qDebug()<<__func__;
    mouse_timer->start(2000);
}

void CurWaveH::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug()<<__func__;
    if(timeOutFlag)
    {
        event->ignore();
    }
}

void CurWaveH::mouseReleaseEvent(QMouseEvent *event)
{
//    qDebug()<<__func__;
}
