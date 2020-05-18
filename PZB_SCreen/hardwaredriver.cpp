#include "hardwaredriver.h"
#include <QProcess>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <QDebug>

#define setBeeperVolume(v) (::ENV_setRegister(212, v, false) == ENV_OK)//蜂蜜器

HardwareDriver::HardwareDriver(QObject *parent) : QObject(parent)
{
    beepInit();
}

void HardwareDriver::beepInit()
{
    ENV_init();                             //初始化
    ENV_activateAutomaticBrightness(false,0); //TRUE：自动调节背光 FALSE：不自动
    ENV_activateBeeper(0, true);
    beeper4hz.bKeyStops = false;
    beeper4hz.dwDuration = 0xFFFFFFFF ;
    beeper4hz.dwNum = 2 ;
    beeper4hz.stSound[0].dwTime = 250 ;
    beeper4hz.stSound[1].dwTime = 250 ;

    beeper1hz.bKeyStops = false;
    beeper1hz.dwDuration = 0xFFFFFFFF ;
    beeper1hz.dwNum = 2 ;
    beeper1hz.stSound[0].dwTime = 500 ;
    beeper1hz.stSound[1].dwTime = 500 ;

    beeperconstant.bKeyStops = false;
    beeperconstant.dwDuration = 0xFFFFFFFF;
    beeperconstant.dwNum = 1 ;
    beeperconstant.stSound[0].dwTime = 1000;

    beeperoff.dwDuration =0;
    beeperoff.dwNum = 0;
    //亮度设置
       ENV_setBrightnessRelative(ENV_DISPLAY,static_cast<int>(m_theBrightness*2.5));
    //蜂鸣器声音设置
    setBeeperVolume(5);
}

void HardwareDriver::startBeep()
{
    ENV_setBeeper(0, &beeper1hz);
}

void HardwareDriver::stopBeep()
{
    ENV_setBeeper(0, &beeperoff);
}

void HardwareDriver::beep(int value)
{
    switch (value) {
    case 0:
        ENV_setBeeper(0, &beeperoff);
        qDebug()<<"beeperoff";
        break;
    case 1:
        ENV_setBeeper(0, &beeperconstant);
        qDebug()<<"beeperconstant";
        break;
    case 2:
        ENV_setBeeper(0, &beeper4hz);
        qDebug()<<"beeper4hz";
        break;
    case 3:
        ENV_setBeeper(0, &beeper1hz);
        qDebug()<<"beeper1hz";
        break;
    default:
        break;
    }

}

void HardwareDriver::setBrightness(int nValue)
{
    int m_theBrightness = 0;
    if(nValue != 6)
    {
        ENV_activateAutomaticBrightness(false,0);  //manul mode
        switch(nValue)
        {
        case 0:
            m_theBrightness = 15;
            break;
        case 1:
            m_theBrightness = 40;
            break;
        case 2:
            m_theBrightness = 55;
            break;
        case 3:
            m_theBrightness = 70;
            break;
        case 4:
            m_theBrightness = 85;
            break;
        case 5:
            m_theBrightness = 100;
            break;
        }
        //亮度设置
        ENV_setBrightnessRelative(ENV_DISPLAY,static_cast<int>(m_theBrightness*2.5));
    }
    else if(nValue == 6)
        ENV_activateAutomaticBrightness(true,0);   //auto mode
}
