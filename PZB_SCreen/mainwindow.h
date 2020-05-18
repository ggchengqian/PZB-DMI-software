#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "additioninfo.h"
#include "indicatorwid.h"
#include "messageinfo.h"
#include "numberkeyboard.h"
#include "speedometer.h"
#include "globalconfig.h"
#include "dataentry.h"
#include "sublevelwindow.h"
#include "PZB_Com/dataparser.h"
#include "lightset.h"
#include "driverid.h"
#include "hardwaredriver.h"
#include "runningnum.h"
#include "functiontest.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QDebug>
#include <QDateTime>

typedef enum PageList
{
    page_mainpage, page_sublevelWin, page_lightset,
    page_dataentry,page_driverID, page_runningnum
}PageList;


namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();
    void setSystemTime(uint t);


protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *eve);

private:
    void initWidget();
    void init();
    void changePage(PageList oldpage, PageList newpage);

private slots:
    void slotDiffTime();

    void slotMapVar(int status,int index,unsigned long value);
    void set_senddata();
    void slotSublevelWin(int index);
    void slotBackToSetting();
    void slotVerification(int value);
    void slotSetLightLevel(int val);
    void slotBeepTimer();
    void slotsendDriverID(int value);
    void slotsendrunningnum(int value);
    void slotBackToMainwid();
    void switchpage(bool flag);

private:
    Ui::CMainWindow *ui;

    CSpeedometer *pageSpeedometer;
    CAdditionInfo *pageAdditionInfo;

    CIndicatorWid *pageIndicator;
    CMessageInfo *pageMessage;
    QPushButton *switch_but;
    DataEntry *pagedataEntry;
    CSubLevelWindow *pageSublevelWin;
    CLightSet *pageLightset;
    CDriverID *pageDriverID;
    CRunningNum *pageRunningNum;
    HardwareDriver *Hardware;
    CFunctionTest *pageFunctiontest;

    QTimer *flushtime;
    QTimer *m_diffTimeTimer;
    QTimer *m_beepTimer;
    QLabel *time_label;

    DataParser *dataHandler;
    unsigned long Variable_data[57];

    //test
    int speedvalue;
    int distancevalue;

    int BRHvalue;
    int ZLvalue;
    int VMZvalue;
    int DriverID;
    int RunningNum;

    bool showColon;

    QList<QWidget*> pagelist;
    PageList curpage;
};
#endif // MAINWINDOW_H
