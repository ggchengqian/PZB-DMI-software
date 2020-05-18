#ifndef INDICATORWID_H
#define INDICATORWID_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include "lamp.h"


namespace Ui {
class CIndicatorWid;
}

class CIndicatorWid : public QWidget
{
    Q_OBJECT

public:
    explicit CIndicatorWid(QWidget *parent = 0);
    ~CIndicatorWid();
    void setIndicatorDis(int index,int displaytype);

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::CIndicatorWid *ui;
    QList<QLabel*> indicator_list;
    Lamp *pzb_lamp[10];
    bool lm_status[8];

    QList<Lamp *> list_LM;
};

#endif // INDICATORWID_H
