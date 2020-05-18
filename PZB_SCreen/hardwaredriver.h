#ifndef HARDWAREDRIVER_H
#define HARDWAREDRIVER_H

#include <QObject>
#include "beep/disphw32.h"
#include "beep/windefs.h"
#include <QTimer>

class HardwareDriver : public QObject
{
    Q_OBJECT
public:
    explicit HardwareDriver(QObject *parent = 0);
    void beepInit();
    void startBeep();
    void stopBeep();
    void beep(int value);
    void setBrightness(int nValue);

signals:

public slots:

private:
    int m_theBrightness;
    ENV_BeeperState_t beeperoff;
    ENV_BeeperState_t beeper4hz;
    ENV_BeeperState_t beeper1hz;
    ENV_BeeperState_t beeperconstant;
};

#endif // HARDWAREDRIVER_H
