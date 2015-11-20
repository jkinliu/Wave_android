#include "analysis.h"


Analysis::Analysis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Analysis)
{
    ui->setupUi(this);
    plot = new Plot(ui->qwtPlot);

    interval_xCur = new QwtInterval(0, 10);
    interval_yCur = new QwtInterval(-1, 1);

    plot->set_title("Time(s)", "g");
    plot->set_x_scale(interval_xCur->minValue(),interval_xCur->maxValue());
    plot->set_y_scale(interval_yCur->minValue(), interval_yCur->maxValue());

}

Analysis::~Analysis()
{
    delete ui;
}

void Analysis::analysisWave(QString path,QString name)
{
    float fmseed = 0;
    float timeAna = 0;
    int j;
    bool ret;
    QPointF mseed_point;

    plot->insert_curve("",0);
    ui->label->setText(name);



    mseed_file = new QFile(path);
    ret = mseed_file->open(QIODevice::ReadWrite | QIODevice::Unbuffered);
    if(!ret)
    {
        qDebug()<<"File Open faild";
        return ;
    }

    uint8_t mseed_buff[1024] = {0};

    mseed_header_t mseed_header;
    date_t date;
    while(read_record_header(&mseed_header))
    {
        date = getMonthAndDay(mseed_header.fsdh.start_time.day,isLeapYear(mseed_header.fsdh.start_time.year));
        if(read_record_data(mseed_buff,sizeof(mseed_buff)) >= 1)
        {
            int32_t *mseed_data = (int32_t *)malloc(mseed_header.fsdh.numsamples*4);
            if(mseed_data)
            {
                int size = 0;

                size = unpack_data(mseed_buff, mseed_data, mseed_header.fsdh.numsamples);
                for(j = 0;j < size; j++)
                {
                    timeAna += 0.01;
                    fmseed = mseed_data[j] / 100000.0;  //在写入mseed数据时，放大100000倍，保存整形数据
                    mseed_point = QPointF(timeAna, fmseed);
                    plot->add_point(0,mseed_point);
                }

                free(mseed_data);
            }

        }
    }

    plot->setSamples();
//    ui->label_2->setText(name);
//    ui->label_3->setText("采样率100");
    if (mseed_file)
    {
        mseed_file->close();
        delete mseed_file;
        mseed_file = NULL;
    }
}

int Analysis::unpack_data(uint8_t *inbuff, int32_t *outputbuff, int samplecnt)
{
    int32_t x0, xn;
	int32_t *diffbuff = (int32_t *) malloc(samplecnt*4);
	if ( diffbuff == NULL )
	{
		qDebug("msr_unpack_data: Cannot allocate diff buffer\n");
		return -1;
	}

	int nsamples = msr_unpack_steim2 ((FRAME *)inbuff, 192, samplecnt, samplecnt, outputbuff,
			diffbuff, &x0, &xn, 0, 0);

	free(diffbuff);

	return nsamples;
}

int Analysis::read_record_header(mseed_header_t *mseed_header)
{
    int ret;
    //SACHeader_t header;
    char *p = (char *)mseed_header;

    memset(p, 0, sizeof(mseed_header_t));

//    sac_file->seek(0);
    ret = mseed_file->read(p, sizeof(mseed_header_t));

    return ret==sizeof(mseed_header_t) ? true : false;
}

int Analysis::read_record_data(uint8_t *buff, int n)
{
    int ret;
    int len = n>192 ? 192 : n;
    char *p = (char *)buff;

    ret = mseed_file->read(p, len);

    return ret==len ? true : false;
}

bool Analysis::isLeapYear(int16_t year)
{
    if((year%4 == 0 && year%100 != 0) || (year%400 == 0))
        return true;
    return false;
}

date_t Analysis::getMonthAndDay(int16_t days, bool leapYear)
{
    int tempDays = 0;
    date_t date ;
    int month;
    int lastMonDay = 0;
    int monDay = 0;

    if(days <= DAY_31)
    {
        date.month = 1;
        date.day = days;
        return date;
    }

    month = days/30;
    for(int i = 1;i <= month;i++)
    {
        switch(i)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            monDay = DAY_31;
            break;
        case 2:
            if(leapYear)
                monDay = DAY_29;
            else
                monDay = DAY_28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            monDay = DAY_30;
            break;
        }
        tempDays += monDay;
        if(i == month)
            lastMonDay = monDay;
    }
    if(tempDays == days)
    {
        date.month = month;
        date.day = lastMonDay;
    }
    else if(tempDays < days)
    {
        date.month = month + 1;
        date.day = days - tempDays;
    }
    return date;
}
