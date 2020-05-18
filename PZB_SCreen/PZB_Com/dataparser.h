/*******************************************************
* XDS PZB系统DMI软件
* -----------------------------------------------------
* Filename: #include "recvdata.h"
* Creation Date: 2020-04-01
* Created By: chengqian
* Description:	接收及发送数据的处理线程
* -----------------------------------------------------
********************************************************/

#ifndef DTATPARSER_H
#define DTATPARSER_H
#include <QWidget>
#include <QThread>
#include <QUdpSocket>
#include <QObject>
#include <QMessageBox>
#include <QString>
#include <arpa/inet.h>
#include "udpsocket.h"
#include "crc.h"

class DataParser : public QThread
{
    Q_OBJECT
public:
    DataParser();
    void run();
    void stop();
    int UpdCheck(unsigned char *pdata, int nbytes, int iaddr, int ilength);
    void receiveData();
    void sendData();
    unsigned long readMemVar(int byte, int bit, int size);
    void writeMemVar(int byte, int bit, int size, unsigned long value);
    int iHeadcheck;

public slots:

signals:
    void signalVarChanged(int status,int index,unsigned long value);

private:
    //UDPCom *udpcom;
    bool m_xMask;
    unsigned char iRcvByte[MAX_BYTE];
    unsigned char iRcvBit[MAX_BYTE][MAX_BIT];

    unsigned long Variable_data[57];

    UDPSocket *M_Udpsocket;
    struct pd_udp_send_23002 *g_UDP_Send;
    int recvLen;
    struct message_header header;
    bool m_state;
    uint32_t timeAlive;
    //struct UDP_Data_Rcv g_UDP_Rcv;
};

#endif // DTATPARSER_H
