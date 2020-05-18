#include "messageinfo.h"
#include "ui_messageinfo.h"

CMessageInfo::CMessageInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMessageInfo)
{
    ui->setupUi(this);
    F_time = new QTimer(this);

    message_list.append(ui->label);
    message_list.append(ui->label_2);
    message_list.append(ui->label_3);

}

CMessageInfo::~CMessageInfo()
{
    delete ui;
}

void CMessageInfo::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //painter.setPen(QColor(255, 255, 255));
    //painter.drawLine(0, 0, this->width(), 0);
    //painter.drawLine(0, 0, 0, this->height());
    //painter.drawLine(0, this->height(), this->width(), this->height());
    //
    //painter.drawLine(0, 48, this->width(), 48);
    //painter.drawLine(0, 96, this->width(), 96);

    painter.setPen(QColor(0, 0, 0));
    painter.drawLine(0, 1, this->width(), 1);

    painter.drawLine(0, 48, this->width(), 48);
    painter.drawLine(0, 96, this->width(), 96);
    painter.drawLine(0, 0, 0, this->height());

    painter.setPen(QColor(8, 24, 57));
    painter.drawLine(this->width()-1, 0, this->width()-1, this->height());
    painter.drawLine(0, 47, this->width(), 47);
    painter.drawLine(0, 95, this->width(), 95);
    painter.drawLine(0, this->height()-1, this->width(), this->height()-1);

}

void CMessageInfo::setMessageID(int index,int ID)
{

    if(0 == ID)
    {
        message_list.at(index)->clear();
    }
    else
    {
        message_list.at(index)->clear();
        message_list.at(index)->setText(GlobalConfig::Message_ID.at(ID-1));
    }


}

void CMessageInfo::setMessageAttr(int index,int Attributes)
{

}

void CMessageInfo::setMessageBackcolor(int index,int Back_color)
{
    if(0 == Back_color)
    {
        backcol = "background-color: rgb(3,17,24)";
    }
    else
    {
    backcol = "";
    backcol = "background-color: rgb("+ QString::number(GlobalConfig::Message_Color.at(Back_color).R) +","+ QString::number(GlobalConfig::Message_Color.at(Back_color).G) +","+ QString::number(GlobalConfig::Message_Color.at(Back_color).B) +")";
    }

    message_list.at(index)->setStyleSheet("border-left:1px solid balck;border-top:1px solid black;border-right:1px solid rgb(8,24,57);border-bottom:1px solid rgb(8,24,57);"+backcol+";"+fontcol);

}

void CMessageInfo::setMessageFontcolor(int index,int Font_color)
{
    fontcol = "";
    fontcol = "color: rgb("+ QString::number(GlobalConfig::Message_Color.at(Font_color).R) +","+ QString::number(GlobalConfig::Message_Color.at(Font_color).G) +","+ QString::number(GlobalConfig::Message_Color.at(Font_color).B) +")";
    message_list.at(index)->setStyleSheet("border-left:1px solid balck;border-top:1px solid black;border-right:1px solid rgb(8,24,57);border-bottom:1px solid rgb(8,24,57);"+backcol+";"+fontcol);
}
