#ifndef FTP_H
#define FTP_H

/**
 * xxx.pro
 *  QT += ftp
 */

//#include <QtFtp>
#include <QString>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include "QtFtp/QFtp"

typedef struct
{
    QString name;
    int     size;
    bool    is_dir;
    QString lastTime;
} file_info;

class Ftp : public QFtp
{
    Q_OBJECT

public:
    Ftp();
    ~Ftp();

    bool connect_host(QString ip, QString username, QString password);
    void disconnect_host();
    bool cd_dir(QString dir);
    QList<file_info> get_list();
    bool download(QString filename, QString rename=QString(""));
    bool upload(QString filename);
    bool del(QString filename);
    QString get_dir();

private slots:
    void ftp_command_finished(int id, bool error);
    void ftp_list(const QUrlInfo &url_info);
    void ftp_progress(qint64 read, qint64 total);

signals:
    void connect_finished(bool error);
    void file_lists(QList<file_info> &lists);
    void progress(qint64 read, qint64 total);
    void get_finished();

private:
    QList<file_info> lists;
    QFile *file_download;
    QFile *file_upload;
    QString path;
};

#endif // FTP_H
