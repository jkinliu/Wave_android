#include "curwavev.h"
#include <QDateTime>
#include <QMessageBox>

QStringList wave_title = QStringList()
        << "LAW-UD"
        << "LAW-EW"
        << "LAW-SN"
        ;

CurWaveV::CurWaveV(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CurWaveV)
{
    ui->setupUi(this);

    plot = new Plot(ui->qwtPlot);

    interval_xCur = new QwtInterval(0, 10);
    interval_yCur = new QwtInterval(-1, 1);

    plot->set_title("Time(s)", "g");
    plot->set_x_scale(interval_xCur->minValue(),interval_xCur->maxValue());
    plot->set_y_scale(interval_yCur->minValue(), interval_yCur->maxValue());

    download_diag = NULL;
    isWaveEnable = false;
    plot_time = 0;
    time_step = 0.01;
    wave_id = WAVE_ID_UD;
    ftp = NULL;

    ui->lineEdit_step->setText("100");

    ui->lcdNumber->setDigitCount(sizeof(DISPTIME_FORMAT));
    ui->lcdNumber->setMode(QLCDNumber::Dec);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    setCurTime(0);


}

CurWaveV::~CurWaveV()
{
    delete ui;
}

void CurWaveV::disp_wave(uint8_t *p)
{
    int i;
    double wave_data[WAVE_MAX] = {0};
    QPointF wave_point[WAVE_MAX];
    uint32_t sec  = 0;
    uint32_t usec = 0;
    bool need_update = false;
    uint64_t wave_time;
    if(time_step == 0)
        return ;

    if(!isWaveEnable)
    {
        isWaveEnable = true;
        plot->insert_curve(wave_title[wave_id],0);
    }

    sec  = read_dword(p);  p += 4;
    usec = read_dword(p);  p += 4;

    plot_time += time_step;

    for (i=0; i<WAVE_MAX; i++)
    {
        wave_data[i]  = read_float(p);    p += 4;
        wave_point[i] = QPointF(plot_time, wave_data[i]);

        if(i != wave_id)
            continue;
        if (plot)
        {
            plot->add_point(0, wave_point[i]);
            plot->setSamples();
            need_update = true;
        }
    }
    // 更新时间轴
    if (need_update)
    {
        double min = interval_xCur->minValue();
        double max = interval_xCur->maxValue();

        //if ((plot_time > max) || (plot_time < min))
        {
            double min_update = plot_time - (max - min);
            double max_update = plot_time ;

            if (min_update < 0)
            {
                min_update = 0;
                max_update = max - min;
            }

            interval_xCur->setMinValue(min_update);
            interval_xCur->setMaxValue(max_update);

            plot->set_x_scale(interval_xCur->minValue(), interval_xCur->maxValue());
        }
    }
    wave_time = (uint64_t)sec*1000 + usec/1000;
    setCurTime(wave_time);
    // 波形数据限制
    if (plot_time > PLOT_TIME_MAX)
    {
        clearWave();
    }
}

void CurWaveV::setCurTime(uint64_t time)
{
    QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(time);
    QString time_str = dateTime.toString(DISPTIME_FORMAT);
    ui->lcdNumber->display(time_str);
}

void CurWaveV::clearWave()
{
    plot->clear_all();

    plot_time = 0;
}

void CurWaveV::on_toolButton_func_clicked()
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

void CurWaveV::openDownloadDialog()
{
    if(!ftp)
    {
        QMessageBox::about(this, "警告", "ftp没有连接上，请确认IP、User和PWD是否正确");
        return ;
    }

    this->hide();
    download_diag = new download(this);
    download_diag->ftp = ftp;
    download_diag->openDir();
    connect(download_diag->ui->pushButton_back,SIGNAL(clicked()),this,SLOT(closeDiag()));
    download_diag->ui->label->setText(ui->label->text());
    download_diag->show();
}

void CurWaveV::openAnalysisDialog()
{
    this->hide();
    fileAnalysis_diag = new FileAnalysis(this);
    connect(fileAnalysis_diag->ui->pushButton_back,SIGNAL(clicked()),this,SLOT(closeAna()));
    fileAnalysis_diag->ui->label->setText(ui->label->text());
    fileAnalysis_diag->show();
//    this->show();
}

void CurWaveV::openSettingDialog()
{
    this->hide();
    setting_diag = new Setting(this);
    connect(setting_diag->ui->pushButton_back,SIGNAL(clicked()),this,SLOT(closeSetting()));
    setting_diag->ui->label->setText(ui->label->text());
    setting_diag->show();
}

void CurWaveV::closeDiag()
{
    this->show();
    download_diag->close();
}

void CurWaveV::closeAna()
{
    this->show();
    fileAnalysis_diag->close();
}

void CurWaveV::closeSetting()
{
    this->show();
    setting_diag->close();
}

void CurWaveV::on_pushButton_pause_clicked(bool checked)
{
    if(checked)
    {
        time_step = 0;
        ui->pushButton_pause->setText("Start");
    }
    else
    {
        time_step = 0.01;
        ui->pushButton_pause->setText("Pause");
        clearWave();
    }
}

void CurWaveV::on_comboBox_currentIndexChanged(int index)
{
    if(wave_id == index)
        return ;
    wave_id = index;
    clearWave();
    plot->del_curve(0);
    isWaveEnable = false;
}

void CurWaveV::on_pushButton_clicked()
{
    if(wave_id == WAVE_ID_UD)
        return ;
    wave_id = WAVE_ID_UD;
    clearWave();
    plot->del_curve(0);
    isWaveEnable = false;
}

void CurWaveV::on_pushButton_2_clicked()
{
    if(wave_id == WAVE_ID_SN)
        return ;
    wave_id = WAVE_ID_SN;
    clearWave();
    plot->del_curve(0);
    isWaveEnable = false;
}

void CurWaveV::on_pushButton_3_clicked()
{
    if(wave_id == WAVE_ID_EW)
        return ;
    wave_id = WAVE_ID_EW;
    clearWave();
    plot->del_curve(0);
    isWaveEnable = false;
}
