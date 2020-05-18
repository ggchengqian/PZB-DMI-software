#include "lightset.h"
#include "ui_lightset.h"

CLightSet::CLightSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CLightSet)
{
    ui->setupUi(this);

    labellist.append(ui->label_1);
    labellist.append(ui->label_2);
    labellist.append(ui->label_3);
    labellist.append(ui->label_4);
    labellist.append(ui->label_5);

    connect(ui->backBtn, SIGNAL(released()), this, SLOT(on_backBtn_clicked()));
}

CLightSet::~CLightSet()
{
    delete ui;
}

void CLightSet::on_addBtn_clicked()
{
    if(value < labellist.size())
    {
        value++;
        setLight(value);
    }
}

void CLightSet::on_subBtn_clicked()
{
    if(value > 1)
    {
        value--;
        setLight(value);
    }
}

void CLightSet::on_manualBtn_clicked()
{
    if(!ui->manualBtn->isChecked())
     {
         ui->manualBtn->setChecked(true);
         return;
     }
     setLight(value);
     ui->autoBtn->setChecked(false);
     ui->addBtn->setEnabled(true);
     ui->subBtn->setEnabled(true);
}

void CLightSet::on_autoBtn_clicked()
{
    if(!ui->autoBtn->isChecked())
    {
        ui->autoBtn->setChecked(true);
        return;
    }
    setLight(6);
    ui->manualBtn->setChecked(false);
    ui->addBtn->setEnabled(false);
    ui->subBtn->setEnabled(false);
}


void CLightSet::setLight(int val)
{
    for(int i=0; i<labellist.size(); i++)
    {
        if(i < val)
        {
            labellist[i]->setStyleSheet("background-color:rgb(0, 255, 0)");
        }
        else
        {
            labellist[i]->setStyleSheet("background-color:rgb(147, 147, 147)");
        }
    }
    emit setLightLevel(val);
//    writeSerial(val);
}

void CLightSet::writeSerial(int val)
{
    QString msg;
    switch(val)
    {
    case 0:
        msg = "!#34,0\n";
        break;
    case 1:
        msg = "!#34,50\n";
        break;
    case 2:
        msg = "!#34,100\n";
        break;
    case 3:
        msg = "!#34,150\n";
        break;
    case 4:
        msg = "!#34,200\n";
        break;
    case 5:
        msg = "!#34,240\n";
        break;
    default:
        break;
    }
#if defined(Q_OS_LINUX)
    m_serial = new QFile("/dev/ttyUSB_SC", this);
    if (!m_serial->open(QIODevice::ReadWrite))
    {
        free(m_serial);
        m_serial = NULL;
        qDebug()<< "Open ttyUSB_SC Failed";
    }
    else
    {
        QByteArray data(msg.toLatin1());
        m_serial->write(data);
        m_serial->close();
        qDebug()<<"Open ttyUSB_SC OK";
    }
#else
    qDebug()<< PR_GREEN << msg.toLatin1().data();
#endif
}

void CLightSet::on_backBtn_clicked()
{
    emit backToSetting();
}
