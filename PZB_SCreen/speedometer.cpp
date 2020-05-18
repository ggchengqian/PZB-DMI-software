#include "speedometer.h"
#include "ui_speedometer.h"

CSpeedometer::CSpeedometer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSpeedometer)
{
    ui->setupUi(this);

    gaugeSpeed_page = new GaugeSpeed(this);
    gaugeSpeed_page->setGeometry(4,19,394,394);
    gaugeSpeed_page->show();

    gaugeSpeed_page->setMaxValue(400);

    for(int i = 0;i < 3;++i)
    {
        target_Speed_LCD[i] = new QLCDNumber(this);
        target_Speed_LCD[i]->setAttribute(Qt::WA_TranslucentBackground, true);
        target_Speed_LCD[i]->setStyleSheet("border: none;color:yellow");
        target_Speed_LCD[i]->setMode(QLCDNumber::Dec);
        target_Speed_LCD[i]->setSegmentStyle(QLCDNumber::Flat);
        target_Speed_LCD[i]->setDigitCount(1);
    }

    target_Speed_LCD[0]->setGeometry(235-78,410-54,29,52);
    target_Speed_LCD[1]->setGeometry(264-78,410-54,29,52);
    target_Speed_LCD[2]->setGeometry(293-78,410-54,29,52);
}

CSpeedometer::~CSpeedometer()
{
    delete ui;
}

void CSpeedometer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //painter.setPen(QColor(255, 255, 255));
    //painter.drawLine(0, 0, this->width(), 0);
    //painter.drawLine(0, 0, 0, this->height());
    //painter.drawLine(this->width(), 0, this->width(), this->height());
    //painter.drawLine(0, this->height(), this->width(), this->height());

    painter.setPen(QColor(0, 0, 0));
    painter.drawLine(0, 1, this->width(), 1);
    painter.drawLine(1, 0, 1, this->height());

    painter.setPen(QColor(8, 24, 57));
    painter.drawLine(this->width(), 0, this->width(), this->height());
    painter.drawLine(0, this->height(), this->width(), this->height());
}

void CSpeedometer::setcurrentspeed(int currentvalue)
{

    if(currentvalue >= 0 && currentvalue <= 400)
    {
        gaugeSpeed_page->setcurrent_S_Value(currentvalue);
    }
}

void CSpeedometer::setPermittedspeed(int PermittedValue)
{
    if(PermittedValue >= 0 && PermittedValue <= 400)
    {
        gaugeSpeed_page->setPermitted_S_Value(PermittedValue);
    }
}

void CSpeedometer::setTargetspeed(int Targetspeed)
{
    target_Speed_LCD[0]->display(Targetspeed/100);
    target_Speed_LCD[1]->display((Targetspeed%100)/10);
    target_Speed_LCD[2]->display(Targetspeed%10);
}
