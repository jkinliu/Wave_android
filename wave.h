#ifndef WAVE_H
#define WAVE_H

#include <QDialog>
#include <QImage>
#include <QTimer>
#include <QString>
#include <QThread>

#include "global.h"
#include "loading.h"
#include "ftp.h"
#include "tcpclient.h"
#include "protocol.h"
#include "curwavev.h"
#include "curwaveh.h"
//#include <thread>

namespace Ui {
class Wave;
}

class Wave : public QDialog
{
    Q_OBJECT

public:
    explicit Wave(QWidget *parent = 0);
    ~Wave();

    void disp_all_wave(uint8_t *p);

private:
    void ftpConnect(QString ip);
    void ftpDisconnect();

    bool tcpConnect();
    void tcpDisconnect();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_exit_clicked();
    void ftp_connect(bool error);
    void ftp_lists(QList<file_info> &info);

    void tcpClientConnected();
    void tcpClientDiconnected();
    void tcpClientRead();
    void closeDiag();
    void heart_time_out();
    void closeLoading();

private:
    Ui::Wave *ui;

    loading *loadImage;
    CurWaveV *curWaveV;
    CurWaveH *curWaveH;
    bool isLogin;


public:
    // ftp
    Ftp *ftp;

    //tcp
    TcpClient *tcpclient;

    QThread *curWave_thread;

    QMutex *mutex;
    QTimer *heart_timer;


};

#endif // WAVE_H
