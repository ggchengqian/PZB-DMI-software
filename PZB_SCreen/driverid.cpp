#include "driverid.h"
#include "ui_driverid.h"

CDriverID::CDriverID(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDriverID)
{
    ui->setupUi(this);

    numkey = new CNumberKeyboard(this);
    numkey->move(0, 332);
    numkey->hide();

    connect(numkey, SIGNAL(signalNumber(int)), this,SLOT(slotNumber(int)));
    connect(numkey, SIGNAL(signalBackspace()),this, SLOT(slotBackspace()));
    connect(numkey, SIGNAL(signalpoint()),this, SLOT(slotpoint()));

    ui->driverID_lineEdit->installEventFilter(this);
}

CDriverID::~CDriverID()
{
    delete ui;
}

bool CDriverID::eventFilter(QObject *watched, QEvent *event)
{
    if (watched ==ui->driverID_lineEdit && event->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard();
    }
    return QWidget::eventFilter(watched,event);
}

void CDriverID::callKeyBoard()
{
    numkey->show();
}

void CDriverID::slotNumber(int num)
{
    ui->driverID_lineEdit->setText(ui->driverID_lineEdit->text() + QString().setNum(num));

}

void CDriverID::slotpoint()
{
    ui->driverID_lineEdit->setText(ui->driverID_lineEdit->text() + ".");
}

void CDriverID::slotBackspace()
{
    ui->driverID_lineEdit->setText(ui->driverID_lineEdit->text().left(ui->driverID_lineEdit->text().length() - 1));
}

void CDriverID::on_cancelBtn_clicked()
{
    numkey->hide();
    ui->driverID_lineEdit->clear();
    emit backToSetting();
}

void CDriverID::on_okBtn_clicked()
{
    int driverID_value = ui->driverID_lineEdit->text().toInt();
    emit senddriverID(driverID_value);
}

void CDriverID::setDriverIDVal(int value)
{
    ui->driverID_lineEdit->setText(QString::number(value));
}
