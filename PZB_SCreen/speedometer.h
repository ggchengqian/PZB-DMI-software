#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QWidget>
#include <QPainter>
#include <gaugespeed.h>
#include <QLCDNumber>

namespace Ui {
class CSpeedometer;
}

class CSpeedometer : public QWidget
{
    Q_OBJECT

public:
    explicit CSpeedometer(QWidget *parent = 0);
    ~CSpeedometer();

    void setcurrentspeed(int currentvalue);
    void setPermittedspeed(int PermittedValue);
    void setTargetspeed(int Targetspeed);

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::CSpeedometer *ui;
    GaugeSpeed *gaugeSpeed_page;
    QLCDNumber *target_Speed_LCD[3];
};

#endif // SPEEDOMETER_H
