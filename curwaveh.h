#ifndef CURWAVEH_H
#define CURWAVEH_H

#include <QDialog>
#include <QMenu>
#include <QTimer>
#include <QMouseEvent>
#include "plot.h"
#include "download.h"
#include "fileanalysis.h"
#include "setting.h"
#include "ui_curwaveh.h"

namespace Ui {
class CurWaveH;
}

class CurWaveH : public QDialog
{
    Q_OBJECT

public:
    explicit CurWaveH(QWidget *parent = 0);
    ~CurWaveH();

private:

    QMenu *func_menu;
    download *download_diag;
    FileAnalysis *fileAnalysis_diag;
    Setting *setting_diag;
    QTimer *mouse_timer;

    bool timeOutFlag;

public:
    Plot *plot;
    QwtInterval *interval_xCur;
    QwtInterval *interval_yCur;
    Ui::CurWaveH *ui;

private slots:
    void closeDiag();
    void on_toolButton_func_clicked();
    void openDownloadDialog();
    void openAnalysisDialog();
    void openSettingDialog();
    void mousePressedTimeOut();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
};

#endif // CURWAVEH_H
