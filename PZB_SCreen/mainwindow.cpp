#include "mainwindow.h"
#include "ui_mainwindow.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),DriverID(0),RunningNum(0),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

    //test
    speedvalue = 0;
    distancevalue = 0;
    showColon = true;
    BRHvalue = 0;
    ZLvalue = 0;
    VMZvalue = 0;

    QPalette pal;
    pal.setColor(QPalette::Background,QColor(3,17,24));
    this->setPalette(pal);

    initWidget();


    init();
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::keyPressEvent(QKeyEvent *eve)
{
    if(Qt::Key_Escape == eve->key())
        this->close();
    if(Qt::Key_F1 == eve->key())
        speedvalue += 10;

    if(Qt::Key_F2 == eve->key())
        speedvalue -= 10;
    if(Qt::Key_F3 == eve->key())
        distancevalue += 50;
    if(Qt::Key_F4 == eve->key())
        distancevalue -= 50;
}

void CMainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    painter.setPen(QColor(0, 0, 0));
    //painter.drawLine(0, 703, this->width(), 703);
    painter.drawLine(1, 703, 1, 746);

    painter.setPen(QColor(8, 24, 57));//8, 24, 57
    painter.drawLine(this->width(), 703, this->width(), 746);
    painter.drawLine(0, 746, this->width(), 746);
}

void CMainWindow::init()
{
    if(GlobalConfig::readComDataList("./bin/config.ini") < 0)
    {
        QMessageBox::warning(this, "Warning", QString::fromUtf8("Configuration file reading error ！"));
        exit(0);
    }

    if(GlobalConfig::readConfigFile("./bin/ComDataList") < 0)
    {
        QMessageBox::warning(this, "Warning", QString::fromUtf8("Configuration file reading error ！"));
        exit(0);
    }

    qDebug()<<"PZB IP:"<<GlobalConfig::PZB_IP;
    qDebug()<<"DMI IP:"<<GlobalConfig::DMI_IP;

    dataHandler =  new DataParser();

    Hardware = new HardwareDriver(this);

    dataHandler->start();

    connect(dataHandler, SIGNAL(signalVarChanged(int,int,unsigned long)), SLOT(slotMapVar(int,int,unsigned long)));

    m_beepTimer = new QTimer(this);
    m_beepTimer->setSingleShot(true);
    connect(m_beepTimer, SIGNAL(timeout()), this, SLOT(slotBeepTimer()));

    flushtime = new QTimer(this);
    connect(flushtime,SIGNAL(timeout()),this,SLOT(set_senddata()));
    //flushtime->start(100);

    m_diffTimeTimer = new QTimer(this);
    m_diffTimeTimer->setInterval(500);
    m_diffTimeTimer->setSingleShot(true);
    connect(m_diffTimeTimer, SIGNAL(timeout()), SLOT(slotDiffTime()));
    m_diffTimeTimer->start();


}

void CMainWindow::initWidget()
{

    pageSpeedometer = new CSpeedometer(this);
    pageSpeedometer->move(78,54);

    pageAdditionInfo = new CAdditionInfo(this);
    pageAdditionInfo->move(0,54);

    pageIndicator = new CIndicatorWid(this);
    pageIndicator->move(78,486);

    pageMessage = new CMessageInfo(this);
    pageMessage->move(78,558);

    pageSublevelWin = new CSubLevelWindow(this);
    pageSublevelWin->move(0,54);
    pageSublevelWin->hide();

    pageLightset = new CLightSet(this);
    pageLightset->move(0,54);
    pageLightset->hide();

    pagedataEntry = new DataEntry(this);
    pagedataEntry->move(0,54);
    pagedataEntry->hide();

    pageDriverID = new CDriverID(this);
    pageDriverID->move(0,54);
    pageDriverID->hide();
    \
    pageRunningNum = new CRunningNum(this);
    pageRunningNum->move(0,54);
    pageRunningNum->hide();

    pageFunctiontest = new CFunctionTest(this);
    pageFunctiontest->move(79,558);
    pageFunctiontest->hide();

    pagelist.clear();
    pagelist.append(pageSpeedometer);
    pagelist.append(pageSublevelWin);
    pagelist.append(pageLightset);
    pagelist.append(pagedataEntry);
    pagelist.append(pageDriverID);
    pagelist.append(pageRunningNum);

    time_label = new QLabel(this);
    time_label->setGeometry(380,57,92,36);
    time_label->setText("hh:mm:ss");
    time_label->setStyleSheet("color: gray;font-size:15pt");

    switch_but = new QPushButton(this);
    switch_but->resize(100,40);
    switch_but->move(190,704);

    //switch_but->setText("switch");
    switch_but->setStyleSheet("QPushButton{outline: none;background-image: url(:/image/switch_but.png);border-top: 1px solid black;"
                              "border-left:1px solid black;""border-bottom: 1px solid rgb(8,24,57);"
                              "border-right:1px solid rgb(8,24,57);} ");

    //switch_but->setStyleSheet("outline: none;border-image: url(:/image/switch_but.png)");


    switch_but->setCheckable(true);
    curpage = page_mainpage;

    connect(switch_but,SIGNAL(toggled(bool)),this,SLOT(switchpage(bool)));

    //changePage(curpage,page_sublevelWin);

    connect(pageSublevelWin, SIGNAL(signalSetting(int)), SLOT(slotSublevelWin(int)));
    connect(pagedataEntry,SIGNAL(signalVerification(int)),SLOT(slotVerification(int)));
    connect(pagedataEntry,SIGNAL(backToSetting()),SLOT(slotBackToSetting()));
    connect(pageLightset, SIGNAL(backToSetting()), SLOT(slotBackToSetting()));
    connect(pageDriverID, SIGNAL(backToSetting()), SLOT(slotBackToSetting()));
    connect(pageRunningNum, SIGNAL(backToSetting()), SLOT(slotBackToSetting()));
    connect(pageLightset,SIGNAL(setLightLevel(int)),SLOT(slotSetLightLevel(int)));
    connect(pageDriverID, SIGNAL(senddriverID(int)), SLOT(slotsendDriverID(int)));
    connect(pageRunningNum, SIGNAL(sendrunningnum(int)), SLOT(slotsendrunningnum(int)));
    connect(pageFunctiontest, SIGNAL(backToMainwid()), SLOT(slotBackToMainwid()));


}


void CMainWindow::slotMapVar(int status,int index,unsigned long value)
{
    if(0 == status)
    {

        switch (index) {
        case 0:
            qDebug()<<"currentspeed"<<value;
            pageSpeedometer->setcurrentspeed(value);
            break;
        case 1:
            qDebug()<<"Permittedspeed"<<value;
            pageSpeedometer->setPermittedspeed(value);
            break;
        case 2:
            qDebug()<<"Targetspeed"<<value;
            pageSpeedometer->setTargetspeed(value);
            break;
        case 3:
            pageAdditionInfo->setdistance_value(value);
            break;
        case 4:
            pageFunctiontest->setFuncTestinf(value);
            qDebug()<<"Functiontest 关闭按钮可用,测试结束"; ;
        case 5:
            pageFunctiontest->setTestRequeststat(value);
            break;
        case 6:

            break;
        case 7:

            break;
        case 8:

            break;
        case 9:

            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            Hardware->beep(value);
            break;
        case 13:
            qDebug()<<"LM_B"<<value;
            pageIndicator->setIndicatorDis(0,value);
            break;
        case 14:
            qDebug()<<"LM_85"<<value;
            pageIndicator->setIndicatorDis(1,value);
            break;
        case 15:
            qDebug()<<"LM_70"<<value;
            pageIndicator->setIndicatorDis(2,value);
            break;
        case 16:
            qDebug()<<"LM_55"<<value;
            pageIndicator->setIndicatorDis(3,value);
            break;
        case 17:
            qDebug()<<"LM_G"<<value;
            pageIndicator->setIndicatorDis(4,value);
            break;
        case 18:
            qDebug()<<"LM_S"<<value;
            pageIndicator->setIndicatorDis(5,value);
            break;
        case 19:
            qDebug()<<"LM_1000HZ"<<value;
            pageIndicator->setIndicatorDis(6,value);
            break;
        case 20:
            qDebug()<<"LM_500HZ"<<value;
            pageIndicator->setIndicatorDis(7,value);
            break;
        case 21:
            qDebug()<<"LM_Befehl40"<<value;
            pageIndicator->setIndicatorDis(8,value);
            break;
        case 22:
            qDebug()<<"LM_PZB"<<value;
            pageIndicator->setIndicatorDis(9,value);
            break;
        case 23:
            qDebug()<<"LM_Stor"<<value;
            break;
        case 24:

            break;
        case 25:
            qDebug()<<"systemtime";
            break;
        case 26:
            qDebug()<<"systemtime_offset";
            break;
        case 27:
            pageMessage->setMessageID(0,value);
            break;
        case 28:
            pageMessage->setMessageAttr(0,value);
            break;
        case 29:
            pageMessage->setMessageBackcolor(0,value);
            break;
        case 30:
            pageMessage->setMessageFontcolor(0,value);
            break;
        case 32:
            pageMessage->setMessageID(1,value);
            break;
        case 33:
            pageMessage->setMessageAttr(1,value);
            break;
        case 34:
            pageMessage->setMessageBackcolor(1,value);
            break;
        case 35:
            pageMessage->setMessageFontcolor(1,value);
            break;
        case 37:
            pageMessage->setMessageID(2,value);
            break;
        case 38:
            pageMessage->setMessageAttr(2,value);
            break;
        case 39:
            pageMessage->setMessageBackcolor(2,value);
            break;
        case 40:
            pageMessage->setMessageFontcolor(2,value);
            break;
        case 42:

            break;
        case 43:

            break;
        case 44:
            qDebug()<<"PZB_DMI_ZDstatus"<<value;
            pagedataEntry->setZDstatus(value);
            break;
        case 48:
            qDebug()<<"制动类型PZB_DMI_7Seg_BRA"<<value;
            pagedataEntry->setTrainData(0,value);
            break;
        case 49:
            qDebug()<<"制动类型PZB_DMI_7Seg_BRH100"<<value;
            BRHvalue = BRHvalue%100 + value*100;
            pagedataEntry->setTrainData(1,BRHvalue);
            break;
        case 50:
            qDebug()<<"制动类型PZB_DMI_7Seg_BRH10"<<value;
            BRHvalue = (value*10)+(BRHvalue/100*100);
            pagedataEntry->setTrainData(1,BRHvalue);
            break;
        case 51:
            qDebug()<<"制动类型PZB_DMI_7Seg_ZL100"<<value;
            ZLvalue = ZLvalue%100 + value*100;
            pagedataEntry->setTrainData(2,ZLvalue);
            break;
        case 52:
            qDebug()<<"制动类型PZB_DMI_7Seg_ZL10"<<value;
            ZLvalue = (value*10)+ZLvalue/100*100;
            pagedataEntry->setTrainData(2,ZLvalue);
            break;
        case 53:
            qDebug()<<"制动类型PZB_DMI_7Seg_VMZ100"<<value;
            VMZvalue = VMZvalue%100 + value*100;
            pagedataEntry->setTrainData(3,VMZvalue);
            break;
        case 54:
            qDebug()<<"制动类型PZB_DMI_7Seg_VMZ10"<<value;
            VMZvalue = (value*10)+VMZvalue/100*100;
            pagedataEntry->setTrainData(3,VMZvalue);
            break;
        case 55:

            break;
        case 56:

            break;
        default:
            break;
        }
    }
    else if(-1 == status)
    {
        qDebug()<<"identification Error";
    }
    else if(-2 == status)
    {
        qDebug()<<"ID Error";
    }
    else if(-3 == status)
    {
        qDebug()<<"cycle Error";
    }
    else if(-4 == status)
    {
        qDebug()<<"addr Error";
    }
    else if(-5 == status)
    {
        qDebug()<<"status Error";
    }
    else if(-6 == status)
    {
        qDebug()<<"pro_ver Error";
    }
    else if(-7 == status)
    {
        qDebug()<<"length Error";
    }
    else if(-8 == status)
    {
        qDebug()<<"timestamp Error";
    }
    else if(-9 == status)
    {
        qDebug()<<"CRC Error";
    }
}


void CMainWindow::slotDiffTime()
{
    uint PZB_DMI_Train_time = dataHandler->readMemVar(17,0,32);
    //unsigned long PZB_DMI_Train_Time_offset = dataHandler->readMemVar(23,0,8);


    //QDateTime time1 = QDateTime::fromMSecsSinceEpoch(PZB_DMI_Train_time);
    QDateTime time1 = QDateTime::fromTime_t(PZB_DMI_Train_time);
    if(showColon)
    {
        time_label->setText(time1.toString("hh")+":"+time1.toString("mm")+":"+time1.toString("ss"));
        showColon = false;
    }
    else {
        time_label->setText(time1.toString("hh")+" "+time1.toString("mm")+" "+time1.toString("ss"));
        showColon = true;
    }

    if(PZB_DMI_Train_time!=0xffffffff)
    {
        setSystemTime(PZB_DMI_Train_time);
    }
    m_diffTimeTimer->start();
}

void CMainWindow::setSystemTime(uint t)
{
    time_t systime, recvtime;
    time(&systime);
    recvtime = (time_t)t;
    if(abs(recvtime-systime) > 5)
    {
        stime(&recvtime);
    }
}

void CMainWindow::set_senddata()
{/*
    QFile file("./bin/senddata");

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString strValue;

        int a = 0;
        while(!stream.atEnd())
        {
            QString strValue = stream.readLine();
            QStringList strList = strValue.split("\t");
            if(strList.size() != 2)
            {
                qDebug()<<"send_data file error";
            }
            QString value = strList.at(1);

            dataHandler->writeMemVar(GlobalConfig::sendMVBList.at(a).byte,GlobalConfig::sendMVBList.at(a).bit,GlobalConfig::sendMVBList.at(a).size,value.toInt());

            a++;
         }

    }
    else
    {
        qDebug()<<"read send_data file failed!";
    }
    file.close();
*/
}

void CMainWindow::slotSublevelWin(int index)
{
    if(index == 0)
    {
        changePage(curpage,page_lightset);
    }
    else if(index == 1)
    {
        changePage(curpage,page_runningnum);
        pageRunningNum->setRunningNumVal(RunningNum);
    }
    else if(index == 2)
    {
        changePage(curpage,page_dataentry);
    }
    else if(index == 3)
    {
        changePage(curpage,page_driverID);
        pageDriverID->setDriverIDVal(DriverID);
    }
    else if(index == 4)
    {
        changePage(curpage,page_mainpage);
        dataHandler->writeMemVar(GlobalConfig::sendMVBList.at(5).byte,GlobalConfig::sendMVBList.at(5).bit,GlobalConfig::sendMVBList.at(5).size,1);
        pageFunctiontest->show();
        pageFunctiontest->butlist.at(1)->setVisible(false);
        pageFunctiontest->butlist.at(2)->setVisible(false);
        pageFunctiontest->setText("waiting for answer");
        pageFunctiontest->butlist.at(0)->setDisabled(true);
        pageFunctiontest->requestTimeout->start();

        pageMessage->setVisible(false);

    }
}

void CMainWindow::slotBackToSetting()
{
    changePage(curpage, page_sublevelWin);
}

void CMainWindow::slotVerification(int value)
{
    dataHandler->writeMemVar(GlobalConfig::sendMVBList.at(6).byte,GlobalConfig::sendMVBList.at(6).bit,GlobalConfig::sendMVBList.at(6).size,value);
    qDebug()<<"将火车数据传输到PZB";
}

void CMainWindow::changePage(PageList oldpage, PageList newpage)
{
    if(oldpage == newpage)
        return;
    if(oldpage == page_mainpage)
    {
        pageSpeedometer->setVisible(false);
        pageIndicator->setVisible(false);
        pageAdditionInfo->setVisible(false);
        pageMessage->setVisible(false);
        time_label->setVisible(false);
    }
    if(newpage == page_mainpage)
    {
        pageSpeedometer->setVisible(true);
        pageIndicator->setVisible(true);
        pageAdditionInfo->setVisible(true);
        pageMessage->setVisible(true);
        time_label->setVisible(true);
    }
    pagelist.at(oldpage)->setVisible(false);
    pagelist.at(newpage)->setVisible(true);

    curpage = newpage;

    if(curpage >= 2)
        switch_but->hide();
    else
        switch_but->show();
}

void CMainWindow::slotBeepTimer()
{

}

void CMainWindow::slotSetLightLevel(int val)
{
    Hardware->setBrightness(val);
}

void CMainWindow::slotBackToMainwid()
{
    changePage(curpage, page_mainpage);
    pageFunctiontest->setVisible(false);
    pageMessage->setVisible(true);
}

void CMainWindow::slotsendDriverID(int value)
{
    dataHandler->writeMemVar(GlobalConfig::sendMVBList.at(14).byte,GlobalConfig::sendMVBList.at(14).bit,GlobalConfig::sendMVBList.at(14).size,value);
    changePage(curpage, page_sublevelWin);
    DriverID = value;
}

void CMainWindow::slotsendrunningnum(int value)
{
    dataHandler->writeMemVar(GlobalConfig::sendMVBList.at(13).byte,GlobalConfig::sendMVBList.at(13).bit,GlobalConfig::sendMVBList.at(13).size,value);
    changePage(curpage, page_sublevelWin);
    RunningNum = value;
}

void CMainWindow::switchpage(bool flag)
{
    if(flag)
    {
        changePage(curpage,page_sublevelWin);
    }
    else
    {
        changePage(curpage,page_mainpage);
    }

}



