#include "gaugespeed.h"

GaugeSpeed::GaugeSpeed(QWidget *parent) : QWidget(parent)
{
    this->ringColor = QColor(195,195,195);          //圆环颜色

    this->pointerColor = QColor(195,195,195);            //指针颜色
    this->textColor = QColor(195,195,195);               //文字颜色
    this->ringWidth = 2;                  //圆环宽度
    this->scaleMajor = 8;                 //大刻度数量
    this->scaleMinor = 5;                 //小刻度数量
    this->startAngle = 36;                 //开始旋转角度
    this->endAngle = 36;                   //结束旋转角度

    this->minValue = 0;                //最小值
    this->midValue = 200;
    this->maxValue = 400;                //最大值
    this->currentValue = 0;
}

void GaugeSpeed::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制渐变背景
    drawRing(&painter);
    //绘制进度
    drawScale(&painter);
    //绘制标尺
    drawScaleNum(&painter);

    draw_S_Pointer(&painter);
    drawSpeedValue(&painter);

    drawPermitted_S_Pointer(&painter);
}

void GaugeSpeed::drawRing(QPainter *painter)
{
    int radius = 180;
    painter->save();

    QPen pen;
    pen.setCapStyle(Qt::FlatCap);
    pen.setWidthF(ringWidth);

    //radius = radius - ringWidth;
    QRectF rect = QRectF(17, 17, radius * 2, radius * 2);

    //计算总范围角度
    double angleAll = 360.0 - startAngle - endAngle;

    //绘制圆环
    pen.setColor(ringColor);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - endAngle - angleAll) * 16, angleAll * 16);

    QFont font;
    font.setPointSize(20);
    font.setBold(false);

    painter->setFont(font);
    painter->drawText(165,307, "km/h");

    painter->restore();
}

void GaugeSpeed::drawScale(QPainter *painter)
{
    int radius = 180;
    painter->save();

    QPen pen;
    pen.setColor(textColor);
    pen.setCapStyle(Qt::RoundCap);
    painter->translate(radius+17,radius+17);
    painter->rotate(startAngle);

    int steps = (scaleMajor * scaleMinor);
    double angleStep = 9.6;
    int index = 0;

    for (int i = 0; i <= steps; i++)
    {
        if (i % scaleMinor == 0 && i <20)
        {
            index++;

            pen.setWidthF(2);
            painter->setPen(pen);
            painter->drawLine(0, radius - 22, 0, radius);
            angleStep = 9.6;
        }
        else if(i % scaleMinor != 0 && i <20)
        {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 15, 0, radius);
            angleStep = 9.6;
        }
        else if(i % scaleMinor == 0 && i >=20)
        {
            index++;

            pen.setWidthF(2);
            painter->setPen(pen);
            painter->drawLine(0, radius - 22, 0, radius);
            angleStep = 4.8;
        }
        else if(i % scaleMinor != 0 && i >=20)
        {
            index++;

            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 15, 0, radius);
            angleStep = 4.8;
        }

        painter->rotate(angleStep);
    }
    painter->restore();
}

void GaugeSpeed::drawScaleNum(QPainter *painter) //paint number
{
    int radius = 134;
    painter->save();
    painter->setPen(textColor);
    //painter->translate(197,197);

    double startRad = (360 - startAngle - 90) * (M_PI / 180);
    double deltaRad = (360 - startAngle - endAngle) * (M_PI / 180) / 6;

    for (int i = 0; i <= 6; i++)
    {
        double sina = qSin(startRad - i * deltaRad);
        double cosa = qCos(startRad - i * deltaRad);
        double value = 0;
        if(i <= 4)
        {
            value = 1.0 * i * ((midValue - minValue) / 4) + minValue;
        }
        else
        {
            value = 1.0 * (i-4) * ((maxValue - midValue) / 2) + midValue;
        }

        QString strValue = QString::number(value);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int x =radius + (radius) * cosa + 52-textWidth/2;
        int y =radius -(radius) * sina + 70+textHeight/2;
        //int x =radius * cosa - 12-textWidth/2;
        //int y =-radius * sina +10 +textHeight/2;

        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        painter->setFont(font);
        painter->drawText(x,y, strValue);
    }
    painter->restore();
}

void GaugeSpeed::draw_S_Pointer(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setCapStyle(Qt::FlatCap);
    pen.setWidthF(40);
    QRectF rect = QRectF(177, 177, 40, 40);

    //绘制指针圆形
    pen.setColor(ringColor);
    painter->setPen(pen);
    painter->drawEllipse(rect);

    int radius = 160;
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);


    painter->translate(197,197);
    QPolygon pts;
    pts.setPoints(8, -8, 0, 8, 0,8,100,3,110, 2,radius,-2,radius,-3,110,-8,100);

    painter->rotate(startAngle);
    double degRotate = startAngle;
    if(currentValue < midValue)
    {
        degRotate = 0.96 * (currentValue - minValue);
    }
    else
    {
        degRotate = 0.48 * (currentValue - midValue) + midValue * 0.96;
    }
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}


void GaugeSpeed::drawSpeedValue(QPainter *painter)
{
    painter->save();
    painter->setPen(QColor(0,0,0));

    QFont font;
    font.setPointSize(25);
    font.setBold(true);
    painter->setFont(font);

    painter->drawText(170,172,54,50,Qt::AlignCenter,QString::number(currentValue));
    painter->restore();
}

void GaugeSpeed::drawPermitted_S_Pointer(QPainter *painter)
{

    int radius = 180;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(255,0,0));


    painter->translate(197,197);
    QPolygon pts;
    pts.setPoints(3, 0, radius, -10, radius+17,10,radius+17);


    double degRotate = startAngle;
    painter->rotate(degRotate);
    if(PermittedValue < midValue)
    {
        degRotate = 0.96 * (PermittedValue - minValue);
    }
    else
    {
        degRotate = 0.48 * (PermittedValue - midValue) + midValue * 0.96;
    }
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeSpeed::setMaxValue(double maxValue)
{
    if(maxValue == 400)
    {
        this->maxValue = 400;
        this->midValue = 200;
        this->minValue = 0;
    }
    update();
}

void GaugeSpeed::setcurrent_S_Value(int currentValue1)
{
    this->currentValue = currentValue1;
    update();
}

void GaugeSpeed::setPermitted_S_Value(int PermittedValue1)
{
    this->PermittedValue = PermittedValue1;
    update();
}

