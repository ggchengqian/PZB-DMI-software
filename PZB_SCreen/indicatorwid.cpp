#include "indicatorwid.h"
#include "ui_indicatorwid.h"
#include <QPainter>

CIndicatorWid::CIndicatorWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CIndicatorWid)
{
    ui->setupUi(this);

    for(int i = 0;i < 10;++i)
    {
        pzb_lamp[i] = new Lamp(this);
        pzb_lamp[i]->resize(57,72);
        pzb_lamp[i]->setVisible(false);
    }
    //pzb_lamp[3]->resize(59,69);

    pzb_lamp[0]->setBgColor(QColor(0,0,255));
    pzb_lamp[0]->setTextColor(QColor(255,255,255));
    pzb_lamp[0]->setdText("B",25,3);
    //pzb_lamp[0]->move(1,1);

    pzb_lamp[1]->setBgColor(QColor(0,0,255));
    pzb_lamp[1]->setTextColor(QColor(255,255,255));
    pzb_lamp[1]->setdText("85",25,5);
    //pzb_lamp[1]->move(58,1);

    pzb_lamp[2]->setBgColor(QColor(0,0,255));
    pzb_lamp[2]->setTextColor(QColor(255,255,255));
    pzb_lamp[2]->setdText("70",25,5);

    pzb_lamp[3]->setBgColor(QColor(0,0,255));
    pzb_lamp[3]->setTextColor(QColor(255,255,255));
    pzb_lamp[3]->setdText("55",25,5);


    pzb_lamp[4]->setBgColor(QColor(255,0,0));
    pzb_lamp[4]->setTextColor(QColor(255,255,255));
    pzb_lamp[4]->setdText("G",25,5);
    //pzb_lamp[2]->move(115,1);

    pzb_lamp[5]->setBgColor(QColor(255,0,0));
    pzb_lamp[5]->setTextColor(QColor(255,255,255));
    pzb_lamp[5]->setdText("S",25,3);
    //pzb_lamp[3]->move(172,1);

    pzb_lamp[6]->setBgColor(QColor(255,255,0));
    pzb_lamp[6]->setTextColor(QColor(0,0,0));
    pzb_lamp[6]->setdText("1000\nHZ",15,3);
    //pzb_lamp[4]->move(232,1);

    pzb_lamp[7]->setBgColor(QColor(255,0,0));
    pzb_lamp[7]->setTextColor(QColor(255,255,255));
    pzb_lamp[7]->setdText("500\nHZ",15,3);
    //pzb_lamp[5]->move(289,1);

    pzb_lamp[8]->setBgColor(QColor(255,255,255));
    pzb_lamp[8]->setTextColor(QColor(0,0,0));
    pzb_lamp[8]->setdText("Befehl\n40",12,3);
    //pzb_lamp[6]->move(346,1);

    pzb_lamp[9]->setBgColor(QColor(255,255,255));
    pzb_lamp[9]->setTextColor(QColor(0,0,0));
    pzb_lamp[9]->setdText("PZB",12,3);
}

CIndicatorWid::~CIndicatorWid()
{
    delete ui;
}

void CIndicatorWid::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //painter.setPen(QColor(255, 255, 255));
    //painter.drawLine(0, 0, this->width(), 0);
    //painter.drawLine(0, 1, this->width(), 1);
    //painter.drawLine(0, 0, 0, this->height());
    //painter.drawLine(this->width(), 0, this->width(), this->height());
    //painter.drawLine(0, this->height(), this->width(), this->height());
    //painter.drawLine(0, this->height()-1, this->width(), this->height()-1);
    //
    //painter.drawLine(57, 0, 57, this->height());
    //painter.drawLine(114, 0, 114, this->height());
    //painter.drawLine(171, 0, 171, this->height());
    //painter.drawLine(228, 0, 228, this->height());//231
    //painter.drawLine(285, 0, 285, this->height());//288
    //painter.drawLine(345, 0, 345, this->height());

    painter.setPen(QColor(0, 0, 0));
    painter.drawLine(0, 1, this->width(), 1);

    painter.drawLine(1, 0, 1, this->height());
    painter.drawLine(58, 0, 58, this->height());
    painter.drawLine(115, 0, 115, this->height());
    painter.drawLine(172, 0, 172, this->height());
    painter.drawLine(229, 0, 229, this->height());//231
    painter.drawLine(286, 0, 286, this->height());//288
    painter.drawLine(346, 0, 346, this->height());

    painter.setPen(QColor(8, 24, 57));
    painter.drawLine(this->width(), 0, this->width(), this->height());
    painter.drawLine(0, this->height(), this->width(), this->height());

    painter.drawLine(57, 0, 57, this->height());
    painter.drawLine(114, 0, 114, this->height());
    painter.drawLine(171, 0, 171, this->height());
    painter.drawLine(228, 0, 228, this->height());//231
    painter.drawLine(285, 0, 285, this->height());//288
    painter.drawLine(345, 0, 345, this->height());

}

void CIndicatorWid::setIndicatorDis(int index,int displaytype)
{
    pzb_lamp[index]->setAttribute(displaytype);

    if(displaytype == 3||displaytype == 5||displaytype == 6)
    {
        pzb_lamp[index]->status = true;
    }
    else if(displaytype == 0)
    {
        pzb_lamp[index]->status = false;
    }
    if(pzb_lamp[0]->status)
    {
        pzb_lamp[0]->setVisible(true);
        pzb_lamp[0]->move(0,0);
    }
    else
    {
        pzb_lamp[0]->setVisible(false);
    }

    if(pzb_lamp[9]->status)
    {
        pzb_lamp[9]->setVisible(true);
        pzb_lamp[9]->resize(60,72);
        pzb_lamp[9]->move(285,0);
    }
    else
    {
        pzb_lamp[9]->setVisible(false);
    }

    int i = 0;
    for(int j = 1;j < 9;++j)
    {
        if(pzb_lamp[j]->status)
        {
            qDebug()<<j<<true << i;
            pzb_lamp[j]->setVisible(true);
            pzb_lamp[j]->move(57+i*57,1);

            i++;
        }
        else
        {
            pzb_lamp[j]->setVisible(false);
        }
        if(i >= 4)
            break;
    }
}
