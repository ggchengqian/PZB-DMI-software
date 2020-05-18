#include "distance.h"

Distance::Distance(QWidget *parent) : QWidget(parent)
{
    this->minValue = 0;
    this->midValue1 = 100;
    this->midValue2 = 1000;
    this->maxValue = 4000;
    this->longStep = 8;
    this->shortStep = 1;
    this->precision = 0;

    this->longStep = 10;
    this->shortStep = 2;
    this->currentValue = 0;
}

void Distance::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    //painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);



    //绘制渐变背景
    drawBg(&painter);
    //绘制进度
    drawProgress(&painter);
    //绘制标尺
    drawRulerTop(&painter);

   painter.setPen(QColor(0, 0, 0));
   painter.drawLine(0, 1, this->width(), 1);
   painter.drawLine(1, 0, 1, this->height());

   painter.setPen(QColor(8, 24, 57));
   painter.drawLine(this->width(), 0, this->width(), this->height());
   painter.drawLine(0, this->height(), this->width(), this->height());

}

void Distance::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor);
    painter->setBrush(bgColor);
    painter->drawRect(rect());
    painter->restore();
}

void Distance::drawProgress(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(progressColor);

    double length = height()-20;
    double increment0_100 = length/37/25;
    double increment100_1000 = length/37/50;
    double increment1000_4000 = length/37/200;
    double initY = 0;
    if(currentValue >=0 && currentValue <= 100)
    {
        initY = currentValue *increment0_100;
    }
    else if(currentValue > 100 && currentValue <= 1000)
    {
        initY = (currentValue - 100)*increment100_1000 + length/37*4;
    }
    else if(currentValue > 1000 && currentValue <= 4000)
    {
        initY = (currentValue - 1000)*increment1000_4000 + length/37*22;
    }
    else if(currentValue > 4000)
    {
        initY = length;
    }
    else
    {
        initY = 0;
    }

    QRect rect(60, height()-10, 10, -initY);
    painter->drawRect(rect);
    painter->restore();
}

void Distance::drawRulerTop(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor);

    double initY = height()-10;
    double initLefX = 40;

    //绘制上部分及下部分横向标尺刻度
    double length = height()-20;
    //计算每一格移动多少
    double increment = length / 37;
    //线条线条长度
    int LineLen = 10;

    //根据范围值绘制刻度值及刻度值
    for (int i = 0; i < 100; i = i + 25) {
        if (i % 100 == 0) {
            QPointF topPot = QPointF(initLefX, initY);
            QPointF bottomPot = QPointF(initLefX+LineLen, initY);
            painter->setPen(longlineColor);
            painter->drawLine(topPot, bottomPot);

            QString strValue = QString::number(i);
            double textWidth = fontMetrics().width(strValue);
            double textHeight = fontMetrics().height();

            QPointF textPot = QPointF(initLefX-textWidth-5, initY + textHeight/4);

            painter->drawText(textPot, strValue);
        }
        else
        {
            QPointF topPot = QPointF(initLefX, initY);
            QPointF bottomPot = QPointF(initLefX +LineLen, initY);
            painter->setPen(lineColor);
            painter->drawLine(topPot, bottomPot);
        }

        initY -= increment;
    }

    for (int i = 100; i < 1000; i = i + 50) {
        if (i % 250 == 0 || i == 100) {
            QPointF topPot = QPointF(initLefX, initY);
            QPointF bottomPot = QPointF(initLefX+LineLen, initY);
            painter->setPen(longlineColor);
            painter->drawLine(topPot, bottomPot);

            QString strValue = QString::number(i);
            double textWidth = fontMetrics().width(strValue);
            double textHeight = fontMetrics().height();

            QPointF textPot = QPointF(initLefX-textWidth-5, initY + textHeight/4);

            painter->drawText(textPot, strValue);
        }
        else
        {
            QPointF topPot = QPointF(initLefX, initY);
            QPointF bottomPot = QPointF(initLefX +LineLen, initY);
            painter->setPen(lineColor);
            painter->drawLine(topPot, bottomPot);
        }

        initY -= increment;
    }

    for (int i = 1000; i <= 4000; i = i + 200) {
        if (i % 250 == 0 || i == 1000) {
            QPointF topPot = QPointF(initLefX, initY);
            QPointF bottomPot = QPointF(initLefX+LineLen, initY);
            painter->setPen(longlineColor);
            painter->drawLine(topPot, bottomPot);

            QString strValue = QString::number(i);
            double textWidth = fontMetrics().width(strValue);
            double textHeight = fontMetrics().height();

            QPointF textPot = QPointF(initLefX-textWidth-5, initY + textHeight/4);

            painter->drawText(textPot, strValue);
        }
        else
        {
            QPointF topPot = QPointF(initLefX, initY);
            QPointF bottomPot = QPointF(initLefX +LineLen, initY);
            painter->setPen(lineColor);
            painter->drawLine(topPot, bottomPot);
        }

        initY -= increment;
    }
    painter->restore();
}

void Distance::setBgColor(const QColor &bgColor)
{
    this->bgColor = bgColor;
}

void Distance::setLineColor(const QColor &lineColor,const QColor &longlineColor)
{
    this->lineColor = lineColor;
    this->longlineColor = longlineColor;
}

void Distance::setProgressColor(const QColor &progressColor)
{
    this->progressColor = progressColor;
}

void Distance::setValue(int value)
{
    this->currentValue = value;
    update();
}

double Distance::getValue()
{
    return currentValue;
}
