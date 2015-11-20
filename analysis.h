#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <QDialog>
#include <QFile>
#include "global.h"
#include "protocol.h"
#include "plot.h"
#include "unpackdata.h"
#include "steimdata.h"
#include "packdata.h"
#include "lmplatform.h"
#include "libmseed.h"
#include "ui_analysis.h"

typedef struct
{
	struct fsdh_s fsdh;		/* 32Byte */

	uint16_t blkt_type;     /* Blockette type */
	uint16_t next_blkt;

	struct blkt_1000_s Blt1000;	/* 4Byte */

	uint16_t blkt2_type;     /* Blockette type */

	struct blkt_1001_s Blt1001;	/* 4Byte */
} mseed_header_t;

typedef struct
{
    int8_t month;
    int8_t day;
}date_t;

namespace Ui {
class Analysis;
}

class Analysis : public QDialog
{
    Q_OBJECT

public:
    explicit Analysis(QWidget *parent = 0);
    ~Analysis();

    void analysisWave(QString path,QString name);

private:
    int unpack_data(uint8_t *inbuff, int32_t *outputbuff, int samplecnt);
    int read_record_header(mseed_header_t *mseed_header);
    int read_record_data(uint8_t *buff, int n);

    bool isLeapYear(int16_t year);
    date_t getMonthAndDay(int16_t days,bool leapYear);

private:

    Plot *plot;
    QwtInterval *interval_xCur;
    QwtInterval *interval_yCur;

    QFile *mseed_file;

public:
    Ui::Analysis *ui;


public:
};

#endif // ANALYSIS_H
