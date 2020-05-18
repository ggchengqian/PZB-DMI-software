#include "sublevelwindow.h"
#include "ui_sublevelwindow.h"

CSubLevelWindow::CSubLevelWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSubLevelWindow)
{
    ui->setupUi(this);

    setting_Btn = new QButtonGroup(this);
    setting_Btn->addButton(ui->but_1,Brightness);
    setting_Btn->addButton(ui->but_2,Train_Running_Number);
    setting_Btn->addButton(ui->but_3,DataEntry);
    setting_Btn->addButton(ui->but_4,Driver_ID);
    setting_Btn->addButton(ui->but_5,Test);
    connect(setting_Btn, SIGNAL(buttonClicked(int)), SIGNAL(signalSetting(int)));
}

CSubLevelWindow::~CSubLevelWindow()
{
    delete ui;
}
