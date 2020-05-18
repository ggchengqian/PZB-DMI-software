#ifndef ADDITIONINFO_H
#define ADDITIONINFO_H

#include <QWidget>
#include <QList>
#include <QLabel>
#include <QPainter>
#include "distance.h"
#include <QDebug>

namespace Ui {
class CAdditionInfo;
}

class CAdditionInfo : public QWidget
{
    Q_OBJECT

public:
    explicit CAdditionInfo(QWidget *parent = 0);
    ~CAdditionInfo();
    void setdistance_value(int distance);

protected:
    void paintEvent(QPaintEvent *);


private:
    Ui::CAdditionInfo *ui;

    //QList<QLabel*> Addinfo_list;
    Distance *distance_page;

    QString Distance_text;
};

#endif // ADDITIONINFO_H
