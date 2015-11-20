#include "wave.h"
#include "ui_wave.h"

#include <QPainter>
#include <QDebug.h>
#include <QTime>
#include <QMessageBox>


static TcpClient *tcpclient_copy;
static Wave *this_obj;
static QMutex *mutex_copy;

static int heart_cnt;
static void setCurTime(uint64_t waveTime);

static void do_prot_recv_cb(prot_t *prot)
{
    uint8_t *p = prot->data;

//    qDebug("cmd = %x, len = %d", prot->cmd, prot->len);
    switch (prot->cmd)
    {
        case CMD_ALL_WAVE:
        {
            this_obj->disp_all_wave(p);
            break;
        }
        case CMD_LAW_WAVE:
        case CMD_A_WAVE:
        case CMD_V_WAVE:
        case CMD_D_WAVE:
        {
            break;
        }
        case CMD_SAMPLE:
        {
            if (prot->len > 0)
            {
                int freq = read_dword(p);  p += 4;

                /*option_copy->*/
//                this_obj->set_sample(freq);
//                this_obj->time_step = 1.0 / freq;
//                this_obj->sample_freq = freq;

//                this_obj->sample->setText(QString("采样率: %1 sps").arg(freq));
            }
            break;
        }
        case CMD_IIR:
        {
            if (prot->len > 0)
            {
                float iir_pass1 = read_float(p);     p += 4;
                float iir_pass2 = read_float(p);     p += 4;

                /*option_copy->*/
//                this_obj->set_iir(iir_pass1, iir_pass2);
            }
            break;
        }
        case CMD_CLOCK:
        {
            if (prot->len > 0)
            {
                uint32_t ip_val = 0;
                uint32_t interval = 0;
                int clock = 0;

                clock = read_dword(p);  p += 4;
                if (prot->len >= 12)
                {
                    ip_val   = read_dword(p);   p += 4;
                    interval = read_dword(p);   p += 4;
                }
                /*option_copy->*/
//                this_obj->set_clock(clock, ip_val, interval);
            }
            break;
        }
        case CMD_TRIGGLE:
        {
            if (prot->len > 0)
            {
                int type = 0;
                int sta  = 0;
                int lta  = 0;
                float sta_lta_h = 0;
                float sta_lta_l = 0;
                float intensity_h = 0;
                float intensity_l = 0;

                type = read_dword(p);   p += 4;
                if (prot->len >= 20)
                {
                    sta = read_dword(p);          p += 4;
                    lta = read_dword(p);          p += 4;
                    sta_lta_h = read_float(p);    p += 4;
                    sta_lta_l = read_float(p);    p += 4;
                }
                else if (prot->len >= 12)
                {
                    intensity_h = read_float(p);  p += 4;
                    intensity_l = read_float(p);  p += 4;
                }

                /*option_copy->*/
//                this_obj->set_triggle(type, sta, lta, sta_lta_h, sta_lta_l, intensity_h, intensity_l);
            }
            break;
        }
        case CMD_ADJUST:
        {
            if (prot->len > 0)
            {
                float ud_ud = read_float(p);     p += 4;
                float ud_ew = read_float(p);     p += 4;
                float ud_sn = read_float(p);     p += 4;

                float ew_ud = read_float(p);     p += 4;
                float ew_ew = read_float(p);     p += 4;
                float ew_sn = read_float(p);     p += 4;

                float sn_ud = read_float(p);     p += 4;
                float sn_ew = read_float(p);     p += 4;
                float sn_sn = read_float(p);     p += 4;

                /*option_copy->*/
//                this_obj->set_adjust(ud_ud, ud_ew, ud_sn,
//                                          ew_ud, ew_ew, ew_sn,
//                                          sn_ud, sn_ew, sn_sn);
            }
            break;
        }
        case CMD_EXPORT:
        {
            break;
        }
        case CMD_SAVE:
        {
            if (prot->len > 0)
            {
                uint8_t wave_type = read_byte(p);   p += 1;
                int pre_time = read_dword(p);       p += 4;
                int aft_time = read_dword(p);       p += 4;

                /*option_copy->*/
//                this_obj->set_save(wave_type, pre_time, aft_time);
            }
            break;
        }
        case CMD_IP:
        {
            if (prot->len > 0)
            {
                uint32_t ip     = read_dword(p);    p += 4;
                uint32_t mask   = read_dword(p);    p += 4;
                uint32_t gateway= read_dword(p);    p += 4;

                /*option_copy->*/
//                this_obj->set_ip(ip, mask, gateway);
            }
            break;
        }
        case CMD_HEARTBEAT:
        {
            break;
        }
        case CMD_SERVER:
        {
            if (prot->len > 0)
            {
                uint32_t master_ip = read_dword(p);    p += 4;
                uint32_t slave_ip  = read_dword(p);    p += 4;

                /*option_copy->*/
//                this_obj->set_server(master_ip, slave_ip);
            }
            break;
        }
        case CMD_INSTALL:
        {
            if (prot->len > 0)
            {
                char field[100] = {0};
                uint8_t mode    = read_byte(p);     p += 1;
                float angle     = read_float(p);    p += 4;
                float longitude = read_float(p);    p += 4;
                float latitude  = read_float(p);    p += 4;
                float height    = read_float(p);    p += 4;

                memcpy(field, p, 32);               p += 32;

                /*option_copy->*/
//                this_obj->set_install_info(mode, angle, longitude, latitude, height, QString::fromUtf8(field));
            }
            break;
        }
        case CMD_VERSION:
        {
            if (prot->len > 0)
            {
                uint32_t arm    = read_dword(p);    p += 4;
                uint32_t dsp    = read_dword(p);    p += 4;

                /*option_copy->*/
//                this_obj->set_version(arm, dsp);
            }
            break;
        }
        case CMD_DEV_ID:
        {
            if (prot->len > 0)
            {
                char station[10]  = {0};
                char location[10] = {0};
                char channel[10]  = {0};
                char network[10]  = {0};

                memcpy(station, p, 5);      p += 5;
                memcpy(location, p, 2);     p += 2;
                memcpy(channel, p, 3);      p += 3;
                memcpy(network, p, 2);      p += 2;

                /*option_copy->*/
//                this_obj->set_devid(QString(station), QString(location), QString(channel), QString(network));
            }
            break;
        }
        case CMD_SERVER_AUTH:
        {
            if (prot->len > 0)
            {
                char password[50] = {0};

                memcpy(password, p, 32);    p += 32;

                /*option_copy->*/
//                this_obj->set_server_auth(QString(password));
            }
            break;
        }
        case CMD_RTC_ADJ:
        {
            if (prot->len > 0)
            {
                int adjust = read_dword(p); p += 4;

                /*option_copy->*/
//                this_obj->set_rtc_adj(adjust);
            }
            break;
        }
        case CMD_TRANSMODE:
        {
            if (prot->len > 0)
            {
                int mode = read_word(p); p += 2;

                /*option_copy->*/
//                this_obj->set_transmode(mode);
            }
            break;
        }
        default:
            break;
    }
    mutex_copy->lock();
    heart_cnt = 0;
    mutex_copy->unlock();
}

static int do_prot_send_cb(uint8_t *buff, int n)
{
    return tcpclient_copy->send_data(QByteArray((char *)buff, n));
}

Wave::Wave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Wave)
{
    ui->setupUi(this);

    tcpclient = NULL;
    ftp = NULL;
    curWaveV = NULL;
    curWave_thread = NULL;
    isLogin = false;
    this_obj = this;

    mutex = new QMutex();
    heart_timer = new QTimer(this);
    heart_timer->setInterval(5000);		// 5000ms
    mutex_copy = mutex;
    heart_cnt = 0;
    connect(heart_timer, &QTimer::timeout, this, &Wave::heart_time_out);

}

Wave::~Wave()
{
    delete ui;
}

void Wave::disp_all_wave(uint8_t *p)
{
    if(curWaveV)
    {
        curWaveV->disp_wave(p);
    }


}

void Wave::ftpConnect(QString ip)
{
    QString user = ui->lineEdit_user->text();
    QString pwd = ui->lineEdit_pwd->text();
    if(ftp)
    {
        delete ftp;
        ftp = NULL;
    }
    if(!ftp)
    {
        ftp = new Ftp();
        connect(ftp, &Ftp::connect_finished,    this, &Wave::ftp_connect);
        connect(ftp, &Ftp::file_lists,          this, &Wave::ftp_lists);
//        connect(ftp, SIGNAL(dataTransferProgress(qint64,qint64)),this, SLOT(updateDataTransferProgress(qint64,qint64)));
//        connect(ftp_timer, SIGNAL(timeout()), this, SLOT(ftp_timeOut()));
//        connect(ftp, &Ftp::get_finished,        this, &Wave::openLocateFolder);
    }
//    ftp->connect_host("192.168.1.122", FTP_USER, FTP_PWD);
    ftp->connect_host(ip, user, pwd);
    ftp->cd_dir("/");
}

void Wave::ftpDisconnect()
{
    if(ftp)
    {
        ftp->disconnect_host();
    }
}

bool Wave::tcpConnect()
{
    if(tcpclient)
    {
        delete tcpclient;
        tcpclient = NULL;
    }

    tcpclient = new TcpClient();
    connect(tcpclient, &TcpClient::connected,      this, &Wave::tcpClientConnected);
    connect(tcpclient, &TcpClient::disconnected,   this, &Wave::tcpClientDiconnected);
    connect(tcpclient, &TcpClient::readyRead,      this, &Wave::tcpClientRead);

    tcpclient_copy = tcpclient;
    QString ip = ui->comboBox_ip->currentText();
    int port = ui->lineEdit_port->text().toInt();
    if (ip.contains(QRegExp(IP_REG_EXP)) && (port > 1024))
    {

        tcpclient->connect_host(ip,port);
        return true;
    }
    else
        QMessageBox::about(this, "警告", "IP或者Port不正确，请确认");

    return false;

}

void Wave::tcpDisconnect()
{
    if(tcpclient)
        tcpclient->disconnect_host();

    heart_timer->stop();
}

void Wave::on_pushButton_login_clicked()
{
    isLogin = false;
    if(tcpConnect())
    {
        ftpConnect(ui->comboBox_ip->currentText());
        this->hide();
        loadImage = new loading(this);
        connect(loadImage,SIGNAL(destroyed(QObject*)),this,SLOT(closeLoading()));
        loadImage->exec();
        delete loadImage;
        loadImage = NULL;
    }

}

void Wave::on_pushButton_exit_clicked()
{
    this->close();
}

void Wave::ftp_connect(bool error)
{
    if(error)
    {
        ftpDisconnect();
    }
}

void Wave::ftp_lists(QList<file_info> &info)
{
    curWaveV->list = info;
    curWaveV->ftp = ftp;
}

void Wave::tcpClientConnected()
{
    heart_cnt = 0;
    heart_timer->start();
    loadImage->close();
//    this->hide();
    isLogin = true;
    if(curWaveV)
    {
        delete curWaveV;
        curWaveV = NULL;
    }
    curWaveV = new CurWaveV(this);
    connect(curWaveV->ui->pushButton_back,SIGNAL(clicked()),this,SLOT(closeDiag()));
//    connect(curWaveV,SIGNAL(destroyed()),this,SLOT(closeDiag()));
    curWaveV->ui->label->setText(ui->comboBox_ip->currentText());
    curWaveV->show();
}

void Wave::tcpClientDiconnected()
{
    // set dis connect flag
    heart_timer->stop();
}

void Wave::tcpClientRead()
{
    QByteArray data = tcpclient->recv_data();

    if (!data.isEmpty())
    {
        prot_parse((uint8_t *)data.data(), data.size(), do_prot_recv_cb);

    }
}

void Wave::closeDiag()
{
    this->show();
    curWaveV->close();

    tcpDisconnect();
    ftpDisconnect();

}

void Wave::heart_time_out()
{
    mutex->lock();
    heart_cnt++;
    if (heart_cnt > 3)
    {
        heart_cnt = 0;
        tcpclient->disconnect_host();
    }
    mutex->unlock();

    prot_send(CMD_HEARTBEAT,   NULL, 0, do_prot_send_cb);
}

void Wave::closeLoading()
{
    if(!isLogin)
        this->show();
}

