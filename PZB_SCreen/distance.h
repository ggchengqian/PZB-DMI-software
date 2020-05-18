#ifndef DISTANCE_H
#define DISTANCE_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QPainter>

class Distance : public QWidget
{
    Q_OBJECT
public:
    explicit Distance(QWidget *parent = 0);

protected:
    //void mousePressEvent(QMouseEvent *);
    //void mouseMoveEvent(QMouseEvent *);
    //void setPressedValue(QPoint pressedPoint);
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawProgress(QPainter *painter);
    void drawRulerTop(QPainter *painter);

private:
    double minValue;                //最小值
    double midValue1;
    double midValue2;
    double maxValue;                //最大值
    int precision;                  //精确度,小数点后几位

    int longStep;                   //长线条等分步长
    int shortStep;                  //短线条等分步长
    bool rulerTop;                  //刻度线在上面

    bool animation;                 //是否启用动画显示
    double animationStep;           //动画显示时步长

    QColor bgColor;                 //背景颜色
    QColor lineColor;               //短线条颜色
    QColor longlineColor;           //长线条颜色
    QColor progressColor;           //进度颜色

    double currentValue;            //当前值

private slots:
    //void updateValue();

public Q_SLOTS:

    //设置目标值
    void setValue(int value);

    //获取目标值
    double getValue();


    //设置背景颜色
    void setBgColor(const QColor &bgColor);
    //设置线条颜色
    void setLineColor(const QColor &lineColor,const QColor &longlineColor);
    //设置进度颜色
    void setProgressColor(const QColor &progressColor);

Q_SIGNALS:
    //void valueChanged(double value);
};

#endif // DISTANCE_H
