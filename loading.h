#ifndef LOADING_H
#define LOADING_H

#include <QDialog>
#include <QTimer>
#include <QImage>

namespace Ui {
class loading;
}

class loading : public QDialog
{
    Q_OBJECT

public:
    explicit loading(QWidget *parent = 0);
    ~loading();

private:
    Ui::loading *ui;
    QTimer *timer;
    QImage *waitImage;

public:
    int load_width;
    int load_height;

private slots:
    void loadImage();
};

#endif // LOADING_H
