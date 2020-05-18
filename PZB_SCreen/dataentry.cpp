#include "dataentry.h"
#include "ui_dataentry.h"
#include <QPaintEngine>

DataEntry::DataEntry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataEntry)
{
    ui->setupUi(this);

    ui->Title_label->setText("PZB列车数据输入");
    lineeditstatus = true;
    field_data_list.append(ui->fielddata_1_lineEdit);
    field_data_list.append(ui->fielddata_2_lineEdit);
    field_data_list.append(ui->fielddata_3_lineEdit);
    field_data_list.append(ui->fielddata_4_lineEdit);

    for(int i = 0;i < 4;++i)
    {
        field_data_list.at(i)->installEventFilter(this);
    }

    keyboard = new CNumberKeyboard(this);
    keyboard->move(0, 332);
    keyboard->hide();


    connect(keyboard, SIGNAL(signalNumber(int)), this,SLOT(slotNumber(int)));
    connect(keyboard, SIGNAL(signalBackspace()),this, SLOT(slotBackspace()));
    connect(keyboard, SIGNAL(signalpoint()),this, SLOT(slotpoint()));

    field_list.append(ui->field_1_label);
    field_list.append(ui->field_2_label);
    field_list.append(ui->field_3_label);
    field_list.append(ui->field_4_label);
    field_list.append(ui->field_5_label);
    field_list.append(ui->field_6_label);
    field_list.append(ui->field_7_label);
    field_list.append(ui->field_8_label);

    for(int i =0;i < field_list.size();++i)
    {
        field_list.at(i)->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }


    PZBcommTimeou = new QTimer(this);
    PZBcommTimeou->setInterval(10000);
    connect(PZBcommTimeou, SIGNAL(timeout()), SLOT(slotOvertime()));
}

DataEntry::~DataEntry()
{
    delete ui;
}

void DataEntry::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

}

bool DataEntry::eventFilter(QObject *watched, QEvent *event)
{
    for(int i = 0;i < 4;++i)
    {
        if (watched ==field_data_list.at(i) && event->type() == QEvent::MouseButtonPress && lineeditstatus)
        {
            callKeyBoard();
        }

    }
    return QWidget::eventFilter(watched,event);
}

void DataEntry::slotNumber(int num)
{
    for(int i=0; i<field_data_list.size(); i++)
    {
        if(this->focusWidget() == field_data_list.at(i))
        {
            field_data_list.at(i)->setText(field_data_list.at(i)->text() + QString().setNum(num));
            break;
        }
    }
}

void DataEntry::slotpoint()
{
    for(int i=0; i<field_data_list.size(); i++)
    {
        if(this->focusWidget() == field_data_list.at(i))
        {
            field_data_list.at(i)->setText(field_data_list.at(i)->text() + ".");
            break;
        }
    }
}

void DataEntry::slotBackspace()
{
    for(int i=0; i<field_data_list.size(); i++)
    {
        if(this->focusWidget() == field_data_list.at(i))
        {
            field_data_list.at(i)->setText(field_data_list.at(i)->text().left(field_data_list.at(i)->text().length() - 1));
            break;
        }
    }
}

void DataEntry::on_cancelBtn_clicked()
{
    keyboard->hide();
    ui->okBtn->show();
    ui->btable->show();
    lineeditstatus = true;
    ui->Title_label->setText("PZB列车数据输入");
    for(int i=0; i<field_data_list.size(); i++)
    {
        field_data_list.at(i)->show();
        field_list.at(i)->show();
        field_data_list.at(i)->setText("");
    }
    PZBcommTimeou->stop();

    for(int i=0; i<field_data_list.size(); i++)
    {
        //field_data_list.at(i)->setDisabled(false);
        field_data_list.at(i)->setFocusPolicy(Qt::StrongFocus);
    }

    emit backToSetting();
}

void DataEntry::slotOvertime()
{
    ui->Title_label->setText("输入不被接受-超时");
}

void DataEntry::on_okBtn_clicked()
{
    for(int i=0; i<field_data_list.size(); i++)
    {
        //field_data_list.at(i)->setDisabled(true);
        field_data_list.at(i)->setFocusPolicy(Qt::NoFocus);
    }
    lineeditstatus = false;

    if(ui->Title_label->text() == "PZB列车数据输入")
    {
        keyboard->hide();
        ui->btable->hide();
        ui->Title_label->setText("已接收的列车数据-预期已接收");
    }
    else if(ui->Title_label->text() == "已接收的列车数据-预期已接收")
    {
        ui->Title_label->setText("列车数据受限-需保持警惕");
        ui->okBtn->hide();
        for(int i = 0;i < 4;++i)
        {
            field_data_list.at(i)->hide();
            field_list.at(i)->hide();
        }
        emit signalVerification(1);
        PZBcommTimeou->start();

    }
}

void DataEntry::on_btable_clicked()
{

}



void DataEntry::callKeyBoard()
{
    keyboard->show();
}

void DataEntry::setZDstatus(int value)
{
    switch (value) {
    case 0:
        qDebug()<<"ZDStatus error";
        break;
    case 1:
        ui->Title_label->setText("有效列车数据");
        PZBcommTimeou->stop();
        break;
    case 2:

        break;
    default:
        break;
    }
}

void DataEntry::setTrainData(int index,int value)
{
    switch (index) {
    case 0:
        ui->field_1_label_3->setText(QString::number(value));
        break;
    case 1:
        ui->field_1_label_5->setText(QString::number(value));
        break;
    case 2:
        ui->field_1_label_7->setText(QString::number(value));
        break;
    case 3:
        ui->field_1_label_9->setText(QString::number(value));
        break;
    default:
        break;
    }
}
