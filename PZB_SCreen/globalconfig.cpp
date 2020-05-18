#include "globalconfig.h"


QList<DataNode> GlobalConfig::recvMVBList;
QList<DataNode> GlobalConfig::sendMVBList;
QList<QString> GlobalConfig::Message_ID;
QList<M_color> GlobalConfig::Message_Color;
QString GlobalConfig::PZB_IP;
QString GlobalConfig::DMI_IP;

GlobalConfig::GlobalConfig()
{
}


/**
 * @brief 读取通信变量配置文件(变量名称、type位置、bit位置，大小)
 * @param path 文件路径
 * @retval 0 读取配置文件成功
 * @retval -1 读取配置文件失败
 */
int GlobalConfig::readComDataList(QString path)
{
    QFile file(path);
    QString strValue;

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString strValue = stream.readLine();

        int indexFlag = -1;
        while(!stream.atEnd())
        {
            strValue = stream.readLine();
            if(strValue[0] == QChar('*'))
            {
                continue;
            }
            QStringList strList = strValue.split("\t");
            if(strValue[0] == QChar('['))
            {
                if(strList.at(0) == QString("[RECV]"))
                    indexFlag = 0;
                else if(strList.at(0) == QString("[SEND]"))
                    indexFlag = 1;
                else if(strList.at(0) == QString("[PZB_IP]"))
                {
                    PZB_IP = strList.at(1);
                }
                else if(strList.at(0) == QString("[DMI_IP]"))
                {
                    DMI_IP = strList.at(1);
                }
                continue;
            }
            DataNode info;
            info.varName = strList.at(1);
            if(strList.at(3) == QString("BOOLEAN1") || strList.at(3) == QString("BOOL"))
                info.size = 1;
            else if(strList.at(3) == QString("UNSIGNED3"))
                info.size = 3;
            else if(strList.at(3) == QString("UNSIGNED4"))
                info.size = 4;
            else if(strList.at(3) == QString("UNSIGNED8") || strList.at(3) == QString("BYTE"))
                info.size = 8;
            else if(strList.at(3) == QString("UNSIGNED16") || strList.at(3) == QString("INTEGER16") || strList.at(3) == QString("WORD"))
                info.size = 16;
            else if(strList.at(3) == QString("UNSIGNED32") || strList.at(3) == QString("DWORD"))
                info.size = 32;
            else if(strList.at(3) == QString("UNSIGNED48"))
            {
                 // qDebug() << strList.at(1) << strList.at(3);
                info.size = 48;
            }
            else
                qDebug() << "TYPE ERROR:" << strList.at(1) << strList.at(3);
            info.varName = strList.at(1);
            info.byte = (unsigned char)strList.at(4).toInt();
            info.bit = (unsigned char)strList.at(5).toInt();
            if(indexFlag == 0)
            {
                recvMVBList.append(info);
            }
            else if(indexFlag == 1)
            {
                if(strList.size() != 6)
                    qDebug() << "Send node error:" << strList.at(0) << strList.at(1);
                sendMVBList.append(info);
            }
        }
        //print configure file information
        /*
        for( int i=0; i< recvMVBList.size(); ++i)
        {
                qDebug()<<recvMVBList.at(i).varName<<"-"<<recvMVBList.at(i).byte <<"-"<<recvMVBList.at(i).bit<<"-"<<recvMVBList.at(i).size;
        }
        for( int i=0; i< sendMVBList.size(); ++i)
        {
                qDebug()<<sendMVBList.at(i).varName<<"-"<<sendMVBList.at(i).byte <<"-"<<sendMVBList.at(i).bit<<"-"<<sendMVBList.at(i).size;
        }
        */

        file.close();
        qDebug()<<"read configdatalist success";
        return 0;
    }
    else
    {
        qDebug() << QString::fromUtf8("数据接口文件读取失败！");
        return -1;
    }
}


/**
 * @brief 读取配置文件(message ID)
 * @param path 文件路径
 * @retval 0 读取配置文件成功
 * @retval -1 读取配置文件失败
 */
int GlobalConfig::readConfigFile(QString path)
{
    QFile file(path);
    QString strValue;

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString strValue = stream.readLine();

        int indexFlag = -1;
        while(!stream.atEnd())
        {
            strValue = stream.readLine();
            if(strValue[0] == QChar('*'))
            {
                continue;
            }
            QStringList strList = strValue.split("\t");
            if(strValue[0] == QChar('['))
            {
                if(strList.at(0) == QString("[message_ID]"))
                    indexFlag = 0;
                else if(strList.at(0) == QString("[message_color]"))
                    indexFlag = 1;
                continue;
            }

            if(0 == indexFlag)
            {
                Message_ID.append(strList.at(1));
            }
            else if(1 == indexFlag)
            {
                M_color mcolor;
                mcolor.value = strList.at(0).toInt();
                mcolor.R = strList.at(1).toInt();
                mcolor.G = strList.at(2).toInt();
                mcolor.B = strList.at(3).toInt();
                Message_Color.append(mcolor);
            }
        }
        //print configure file information

        for( int i=0; i< Message_ID.size(); ++i)
        {
                qDebug()<<Message_ID.at(i);
        }
        for( int i=0; i< Message_Color.size(); ++i)
        {
                qDebug()<<Message_Color.at(i).value<<Message_Color.at(i).R<<Message_Color.at(i).G<<Message_Color.at(i).B;
        }


        file.close();
        qDebug()<<"read configure file success";
        return 0;
    }
    else
    {
        qDebug() << QString::fromUtf8("配置文件读取失败！");
        return -1;
    }
}
