#ifndef CURWAVEV_H
#define CURWAVEV_H

#include "ui_curwavev.h"
#include <QDialog>
#include <QMenu>
#include "plot.h"
#include "download.h"
#include "fileanalysis.h"
#include "setting.h"
#include "ftp.h"

namespace Ui {
class CurWaveV;
}

class CurWaveV : public QDialog
{
    Q_OBJECT

public:
    explicit CurWaveV(QWidget *parent = 0);
    ~CurWaveV();

    void disp_wave(uint8_t *p);

private:
    void setCurTime(uint64_t time);
    void clearWave();
    void addWave(int index);

private:
    QMenu *func_menu;
    download *download_diag;
    FileAnalysis *fileAnalysis_diag;
    Setting *setting_diag;
    bool isWaveEnable;
    double plot_time;
    float time_step;

public:
    Ui::CurWaveV *ui;
    Plot *plot;
    int wave_id;
    QwtInterval *interval_xCur;
    QwtInterval *interval_yCur;
    QList<file_info> list;
    Ftp *ftp;

private slots:
    void closeDiag();
    void closeAna();
    void closeSetting();
    void on_toolButton_func_clicked();
    void openDownloadDialog();
    void openAnalysisDialog();
    void openSettingDialog();
    void on_pushButton_pause_clicked(bool checked);
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // CURWAVEV_H
