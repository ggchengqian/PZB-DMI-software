#ifndef MESSAGEINFO_H
#define MESSAGEINFO_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QTimer>
#include "globalconfig.h"

namespace Ui {
class CMessageInfo;
}

class CMessageInfo : public QWidget
{
    Q_OBJECT

public:
    explicit CMessageInfo(QWidget *parent = 0);
    ~CMessageInfo();

    void setMessageID(int index,int ID);
    void setMessageAttr(int index,int Attributes);
    void setMessageBackcolor(int index,int Back_color);
    void setMessageFontcolor(int index,int Font_color);

    QList<QLabel*> message_list;

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::CMessageInfo *ui;
    QTimer *F_time;
    QString backcol;
    QString fontcol;
};

#endif // MESSAGEINFO_H
