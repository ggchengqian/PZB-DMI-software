#include "numberkeyboard.h"
#include "ui_numberkeyboard.h"
#include "globalconfig.h"
#include <QPainter>
#include <QSignalMapper>

CNumberKeyboard::CNumberKeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CNumberKeyboard)
{
    ui->setupUi(this);

    nWidth = this->width();
    nHeight = this->height();

    numberlist.append(ui->Key_0_but);
    numberlist.append(ui->Key_1_but);
    numberlist.append(ui->Key_2_but);
    numberlist.append(ui->Key_3_but);
    numberlist.append(ui->Key_4_but);
    numberlist.append(ui->Key_5_but);
    numberlist.append(ui->Key_6_but);
    numberlist.append(ui->Key_7_but);
    numberlist.append(ui->Key_8_but);
    numberlist.append(ui->Key_9_but);

    ui->backspaceBtn->setFocusPolicy(Qt::NoFocus);
    ui->Key_point_but->setFocusPolicy(Qt::NoFocus);

    connect(ui->backspaceBtn, SIGNAL(clicked()), SIGNAL(signalBackspace()));
    connect(ui->Key_point_but, SIGNAL(clicked()), SIGNAL(signalpoint()));

    QSignalMapper *sm = new QSignalMapper(this);
    for(int i=0; i<numberlist.size(); ++i)
    {
        connect(numberlist.at(i), SIGNAL(clicked()), sm, SLOT(map()));
        sm->setMapping(numberlist.at(i), i);
        numberlist.at(i)->setFocusPolicy(Qt::NoFocus);
    }
    connect(sm, SIGNAL(mapped(int)), SIGNAL(signalNumber(int)));
}

CNumberKeyboard::~CNumberKeyboard()
{
    delete ui;
}

void CNumberKeyboard::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPainterPath path1, path2;
//  p.setPen(QPen(color_B6));
//  p.setBrush(QBrush(color_B6));
//  path1.moveTo(0, 0);
//  path1.lineTo(nWidth, 0);
//  path1.lineTo(nWidth-4, 4);
//  path1.lineTo(4, 4);
//  path1.lineTo(4, nHeight-4);
//  path1.lineTo(0, nHeight);
//  path1.lineTo(0, 0);
//  p.drawPath(path1);
//  path2.moveTo(nWidth, 0);
//  path2.lineTo(nWidth, nHeight);
//  path2.lineTo(0, nHeight);
//  path2.lineTo(4, nHeight-4);
//  path2.lineTo(nWidth-4, nHeight-4);
//  path2.lineTo(nWidth-4, 4);
//  path2.lineTo(nWidth, 0);
//  p.setBrush(QBrush(color_B7));
//  p.setPen(QPen(color_B7));
//  p.drawPath(path2);
//  p.setPen(QPen(color_B5));
//  p.setBrush(QBrush(color_B5));
//  p.drawRect(QRect(4, 4, nWidth-9, nHeight-9));
}
