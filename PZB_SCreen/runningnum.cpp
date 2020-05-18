#include "runningnum.h"
#include "ui_runningnum.h"

CRunningNum::CRunningNum(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CRunningNum)
{
    ui->setupUi(this);

    numkeyboard = new CNumberKeyboard(this);
    numkeyboard->move(0, 332);
    numkeyboard->hide();

    connect(numkeyboard, SIGNAL(signalNumber(int)), this,SLOT(slotNumber(int)));
    connect(numkeyboard, SIGNAL(signalBackspace()),this, SLOT(slotBackspace()));
    connect(numkeyboard, SIGNAL(signalpoint()),this, SLOT(slotpoint()));

    ui->runningnum_lineEdit->installEventFilter(this);
}

CRunningNum::~CRunningNum()
{
    delete ui;
}

bool CRunningNum::eventFilter(QObject *watched, QEvent *event)
{
    if (watched ==ui->runningnum_lineEdit && event->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard();
    }
    return QWidget::eventFilter(watched,event);
}

void CRunningNum::callKeyBoard()
{
    numkeyboard->show();
}

void CRunningNum::on_cancelBtn_clicked()
{
    numkeyboard->hide();
    ui->runningnum_lineEdit->clear();
    emit backToSetting();
}

void CRunningNum::slotNumber(int num)
{
    ui->runningnum_lineEdit->setText(ui->runningnum_lineEdit->text() + QString().setNum(num));

}

void CRunningNum::slotpoint()
{
    ui->runningnum_lineEdit->setText(ui->runningnum_lineEdit->text() + ".");
}

void CRunningNum::slotBackspace()
{
    ui->runningnum_lineEdit->setText(ui->runningnum_lineEdit->text().left(ui->runningnum_lineEdit->text().length() - 1));
}

void CRunningNum::on_okBtn_clicked()
{
    int runningnum_value = ui->runningnum_lineEdit->text().toInt();
    emit sendrunningnum(runningnum_value);
}

void CRunningNum::setRunningNumVal(int value)
{
    ui->runningnum_lineEdit->setText(QString::number(value));
}
