#include "additioninfo.h"
#include "ui_additioninfo.h"


CAdditionInfo::CAdditionInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CAdditionInfo)
{
    ui->setupUi(this);
    distance_page = new Distance(this);
    distance_page->setGeometry(0,122,78,274);
    distance_page->setBgColor(QColor(3,17,24));
    distance_page->setLineColor(QColor(128,128,128),QColor(255,255,255));
    distance_page->setProgressColor(QColor(0,255,0));
    distance_page->show();

    ui->distance_Number->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->distance_Number->setStyleSheet("border: none;color:yellow");
    //ui->distance_Number->setStyleSheet("color:yellow;border-left:1px solid balck;border-top:1px solid black;border-right:1px solid rgb(8,24,57);border-bottom:1px solid rgb(8,24,57)");

    //ui->distance_Number->setGeometry(0,80,78,40);
    //设置显示的模式为十进制
    ui->distance_Number->setMode(QLCDNumber::Dec);
    //设置显示方式
    ui->distance_Number->setSegmentStyle(QLCDNumber::Flat);
    //设置晶体管控件QLCDNumber能显示的位数
    ui->distance_Number->setDigitCount(5);
    ui->distance_Number->display(0);
}

CAdditionInfo::~CAdditionInfo()
{
    delete ui;
}

void CAdditionInfo::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //painter.setPen(QColor(255,255,255));
    //painter.drawLine(0, 0, this->width(), 0);
    //painter.drawLine(0, 0, 0, this->height());
    //painter.drawLine(this->width(), 0, this->width(), this->height());
    //painter.drawLine(0, this->height(), this->width(), this->height());

    //painter.drawLine(0, 0, this->width(), 0);
    //painter.drawLine(0, 78, this->width(), 78);
    //painter.drawLine(0, 122, this->width(), 122);
    //painter.drawLine(0, 397, this->width(), 397);
    //painter.drawLine(0, 432, this->width(), 432);
    //painter.drawLine(0, 433, this->width(), 433);
    //painter.drawLine(0, 468, this->width(), 468);
    //painter.drawLine(0, 504, this->width(), 504);
    //painter.drawLine(0, 540, this->width(), 540);
    //painter.drawLine(0, 576, this->width(), 576);
    //painter.drawLine(0, 612, this->width(), 612);

    painter.setPen(QColor(0, 0, 0));
    painter.drawLine(0, 1, this->width(), 1);
    painter.drawLine(0, 78, this->width(), 78);
    painter.drawLine(0, 123, this->width(), 123);
    painter.drawLine(0, 397, this->width(), 397);
    painter.drawLine(0, 432, this->width(), 432);
    painter.drawLine(0, 468, this->width(), 468);
    painter.drawLine(0, 504, this->width(), 504);
    painter.drawLine(0, 540, this->width(), 540);
    painter.drawLine(0, 576, this->width(), 576);
    painter.drawLine(0, 612, this->width(), 612);

    painter.drawLine(0, 0, 0, this->height());


    painter.setPen(QColor(8, 24, 57));
    painter.drawLine(0, 77, this->width(), 77);
    painter.drawLine(0, 122, this->width(), 122);
    painter.drawLine(0, 395, this->width(), 395);
    painter.drawLine(0, 431, this->width(), 431);
    painter.drawLine(0, 467, this->width(), 467);
    painter.drawLine(0, 503, this->width(), 503);
    painter.drawLine(0, 539, this->width(), 539);
    painter.drawLine(0, 575, this->width(), 575);
    painter.drawLine(0, 611, this->width(), 611);
    painter.drawLine(0, this->height(), this->width(), this->height());

    painter.drawLine(this->width(), 0, this->width(), this->height());

}

void CAdditionInfo::setdistance_value(int distance)
{
    distance_page->setValue(distance);
    if(distance >= 10000 && distance <= 12800 )
        ui->distance_Number->display(distance);
    else if(distance > 12800)
        ui->distance_Number->display(12800);
    else if(distance >= 1000 && distance < 10000 )
        ui->distance_Number->display(QString::number(distance));
    else if(distance >= 100 && distance < 1000 )
        ui->distance_Number->display(" "+QString::number(distance)+" ");
    else if(distance >= 10 && distance < 100 )
        ui->distance_Number->display(" "+QString::number(distance)+"  ");
    else if(distance >= 0 && distance < 10 )
        ui->distance_Number->display("  "+QString::number(distance)+"  ");
    else
        qDebug()<<"distance is error";
}

