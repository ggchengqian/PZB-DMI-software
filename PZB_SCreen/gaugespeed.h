#ifndef GAUGESPEED_H
#define GAUGESPEED_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <qmath.h>
#include <QDebug>
#define M_PI    3.1415926

class GaugeSpeed : public QWidget
{
    Q_OBJECT
public:
    explicit GaugeSpeed(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
    void drawRing(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void draw_S_Pointer(QPainter *painter);
    void drawPermitted_S_Pointer(QPainter *painter);
    void drawValue(QPainter *painter);
    void drawSpeedValue(QPainter *painter);

private slots:
    //void updateValue();

private:
    double minValue;                //最小值
    double midValue;                //中间值
    double maxValue;                //最大值

    int scaleMajor;                 //大刻度数量
    int scaleMinor;                 //小刻度数量
    int startAngle;                 //开始旋转角度
    int endAngle;                   //结束旋转角度


    int ringWidth;                  //圆环宽度

    QColor ringColor;          //圆环颜色

    QColor pointerColor;            //指针颜色
    QColor textColor;               //文字颜色
    double currentValue;            //当前值
    double PermittedValue;            //当前值

public:

public Q_SLOTS:

    //设置最大最小值
    //void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    //设置目标值
    //void setValue(double value);
    void setcurrent_S_Value(int currentValue1);
    void setPermitted_S_Value(int PermittedValue1);


Q_SIGNALS:
    //void valueChanged(int value);
};

#endif // GAUGESPEED_H
