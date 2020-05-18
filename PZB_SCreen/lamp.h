#ifndef LAMP_H
#define LAMP_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QDebug>

class Lamp : public QWidget
{
    Q_OBJECT
public:
    explicit Lamp(QWidget *parent = 0);
    bool status;

Q_SIGNALS:

public Q_SLOTS:
    void setState();

protected:
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawText(QPainter *painter);

private:
    bool m_alarm;
    bool m_state;

    QColor bgColor;                 //背景颜色
    QColor textColor;               //文字颜色
    QString dis_text;
    int fontsize;

    QTimer *timer;
    int m_attribute;

public Q_SLOTS:
    void setBgColor(const QColor &bgColor);
    void setTextColor(const QColor &bgColor);
    void setdText(const QString &text,int fontSize,int attribute);
    void setAttribute(int attribute);


};

#endif // LAMP_H
