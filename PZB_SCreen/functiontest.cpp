#include "functiontest.h"
#include "ui_functiontest.h"

CFunctionTest::CFunctionTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFunctionTest)
{
    ui->setupUi(this);

    butlist.append(ui->pushButton);
    butlist.append(ui->pushButton_2);
    butlist.append(ui->pushButton_3);

    requestTimeout = new QTimer(this);
    requestTimeout->setInterval(3000);
    connect(requestTimeout, SIGNAL(timeout()), SLOT(slotOvertime()));
}

CFunctionTest::~CFunctionTest()
{
    delete ui;
}

void CFunctionTest::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QColor(0, 0, 0));
    painter.drawLine(0, 1, this->width(), 1);
    painter.drawLine(0, 0, 0, this->height());

    painter.setPen(QColor(8, 24, 57));
    painter.drawLine(this->width()-1, 0, this->width()-1, this->height());
    painter.drawLine(0, this->height()-1, this->width(), this->height()-1);
}

void CFunctionTest::slotOvertime()
{
    ui->label->setText("PZB测试不可用(请求超时)");
    ui->pushButton->setDisabled(false);
}

void CFunctionTest::on_pushButton_clicked()
{
    ui->label->clear();
    requestTimeout->stop();
    emit backToMainwid();
}

void CFunctionTest::setText(QString messagetext)
{
    ui->label->setText(messagetext);
}

void CFunctionTest::setTestRequeststat(int value)
{
    if(value == 1)
    {
        requestTimeout->stop();
        ui->pushButton->setDisabled(true);
        ui->label->setText("功能测试正在进行中……");
    }
}

void CFunctionTest::setFuncTestinf(int value)
{
    if(value == 1)
    {
        ui->label->setText("测试运行结束");
        ui->pushButton->setDisabled(false);
        ui->pushButton_2->setVisible(true);
        ui->pushButton_3->setVisible(true);
    }
}
