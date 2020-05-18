/*******************************************************
* XDS PZB系统DMI软件
* -----------------------------------------------------
* Filename: #include "recvdata.h"
* Creation Date: 2020-04-03
* Created By: chengqian
* Description:	读取配置文件
* -----------------------------------------------------
********************************************************/

#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

#include <QList>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDebug>

typedef struct DataNode
{
    QString varName;
    unsigned char byte;
    unsigned char bit;
    unsigned char size;
} DataNode;

typedef struct M_color
{
    int value;
    int R;
    int G;
    int B;
} M_color;

class GlobalConfig
{
public:
    GlobalConfig();
    static int readComDataList(QString path);
    static int readConfigFile(QString path);
    static QList<DataNode> recvMVBList;
    static QList<DataNode> sendMVBList;
    static QList<QString> Message_ID;
    static QList<M_color> Message_Color;
    static QString PZB_IP;
    static QString DMI_IP;
};

#endif // GLOBALCONFIG_H
