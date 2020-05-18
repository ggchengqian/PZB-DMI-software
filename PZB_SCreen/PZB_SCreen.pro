#-------------------------------------------------
#
# Project created by QtCreator 2020-04-09T12:30:26
#
#-------------------------------------------------

QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PZB_SCreen
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    additioninfo.cpp \
    indicatorwid.cpp \
    speedometer.cpp \
    numberkeyboard.cpp \
    messageinfo.cpp \
    globalconfig.cpp \
    distance.cpp \
    gaugespeed.cpp \
    lamp.cpp \
    dataentry.cpp \
    sublevelwindow.cpp \
    lightset.cpp \
    hardwaredriver.cpp \
    driverid.cpp \
    runningnum.cpp \
    functiontest.cpp \
    PZB_Com/crc.cpp \
    PZB_Com/dataparser.cpp \
    PZB_Com/udpsocket.cpp

HEADERS  += mainwindow.h \
    additioninfo.h \
    indicatorwid.h \
    speedometer.h \
    numberkeyboard.h \
    messageinfo.h \
    globalconfig.h \
    distance.h \
    gaugespeed.h \
    lamp.h \
    dataentry.h \
    sublevelwindow.h \
    lightset.h \
    hardwaredriver.h \
    beep/disphw32.h \
    beep/windefs.h \
    driverid.h \
    runningnum.h \
    functiontest.h \
    PZB_Com/crc.h \
    PZB_Com/dataparser.h \
    PZB_Com/udpsocket.h

FORMS    += mainwindow.ui \
    additioninfo.ui \
    indicatorwid.ui \
    speedometer.ui \
    numberkeyboard.ui \
    messageinfo.ui \
    dataentry.ui \
    sublevelwindow.ui \
    lightset.ui \
    driverid.ui \
    runningnum.ui \
    functiontest.ui




#lib32
#unix:!macx: LIBS += -L$$PWD/lib/ -lenvcon
#
#INCLUDEPATH += $$PWD/.
#DEPENDPATH += $$PWD/.
#
#unix:!macx: PRE_TARGETDEPS += $$PWD/lib/libenvcon.a
#
#
#unix:!macx: LIBS += -L$$PWD/../../../../../opt/sdk-dat-arm/host/usr/arm-buildroot-linux-gnueabihf/sysroot/usr/lib32/ -lexpat
#
#INCLUDEPATH += $$PWD/../../../../../opt/sdk-dat-arm/host/usr/arm-buildroot-linux-gnueabihf/sysroot/usr/lib32
#DEPENDPATH += $$PWD/../../../../../opt/sdk-dat-arm/host/usr/arm-buildroot-linux-gnueabihf/sysroot/usr/lib32


#lib64
unix:!macx: LIBS += -L$$PWD/lib64/ -lenvcon

INCLUDEPATH += $$PWD/lib64
DEPENDPATH += $$PWD/lib64

unix:!macx: PRE_TARGETDEPS += $$PWD/lib64/libenvcon.a

unix:!macx: LIBS += -L$$PWD/../../../../../lib/x86_64-linux-gnu/ -lexpat

INCLUDEPATH += $$PWD/../../../../../lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../../../lib/x86_64-linux-gnu

RESOURCES += \
    res.qrc

