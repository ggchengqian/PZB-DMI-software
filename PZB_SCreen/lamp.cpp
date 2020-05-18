#include "lamp.h"

Lamp::Lamp(QWidget *parent) : QWidget(parent)
{
    this->status == false;
    m_attribute = 0;
    m_state = false;
    this->dis_text = "85";
    this->fontsize = 25;
    this->bgColor = QColor(0,0,255);
    this->textColor = QColor(255,255,255);
    timer = new QTimer(this);
    //timer->setInterval(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(setState()));
    //timer->start();
}


void Lamp::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); 	/* 使用反锯齿(如果可用) */


    drawBg(&painter);
    drawText(&painter);

    painter.setPen(QColor(0, 0, 0));
    painter.drawLine(0, 1, this->width(), 1);
    painter.drawLine(1, 0, 1, this->height());

    painter.setPen(QColor(8, 24, 57));
    painter.drawLine(this->width(), 0, this->width(), this->height());
    painter.drawLine(0, this->height(), this->width(), this->height());

}

void Lamp::drawBg(QPainter *painter)
{
    painter->setPen(Qt::NoPen);


    /* 内部指示颜色 */
    if (3 == m_attribute)
    {
        painter->setBrush(bgColor);
    }
    else if(5 == m_attribute)
    {
        //timer->setInterval(500);
        if(m_state==false)
        {
            painter->setBrush(bgColor);
        }
        else
        {
            painter->setBrush(QColor(3,17,24));
        }
    }
    else if(6 == m_attribute)
    {
        if(m_state==false)
        {
            painter->setBrush(bgColor);
        }
        else
        {
            painter->setBrush(QColor(3,17,24));
        }
    }
    else if(13 == m_attribute)
    {
        if(m_state==false)
        {
            painter->setBrush(QColor(3,17,24));
        }
        else
        {
            painter->setBrush(bgColor);
        }
    }
    else if(14 == m_attribute)
    {

        if(m_state==false)
        {
            painter->setBrush(QColor(3,17,24));
        }
        else
        {
            painter->setBrush(bgColor);
        }
    }
    QRect rect(0, 0, width(), height());
    painter->drawRect(rect);
}

void Lamp::drawText(QPainter *painter)
{
    painter->setPen(textColor);

    QFont font;
    font.setPointSize(fontsize);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(0,0,this->width(),this->height(),Qt::AlignCenter,dis_text);
}

void Lamp::setState()
{
    if(m_state==true)
        m_state=false;
    else
        m_state=true;
    update();
}

void Lamp::setBgColor(const QColor &bgColor)
{
    this->bgColor = bgColor;
}

void Lamp::setTextColor(const QColor &textColor)
{
    this->textColor = textColor;
}

void Lamp::setdText(const QString &text,int fontSize,int attribute)
{
    this->dis_text = text;
    this->fontsize = fontSize;
    //this->m_attribute = attribute;
    //if(5 == attribute || 13 == attribute)
    //    timer->setInterval(500);
    //else if(6 == attribute || 14 == attribute)
    //    timer->setInterval(1000);
    //update();
    //timer->start();
}

void Lamp::setAttribute(int attribute)
{
    this->m_attribute = attribute;
    if(5 == attribute || 13 == attribute)
        timer->setInterval(500);
    else if(6 == attribute || 14 == attribute)
        timer->setInterval(1000);
    update();
    timer->start();
}
