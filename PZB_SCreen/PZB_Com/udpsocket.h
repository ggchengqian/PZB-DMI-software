/*******************************************************
* XDS PZB系统DMI软件
* -----------------------------------------------------
* Filename: #include "udpsocket.h"
* Creation Date: 2020-3-31
* Created By: chengqian
* Description:	UDP通信(接收发送数据)的封装库
* -----------------------------------------------------
********************************************************/

#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <QString>
#include <QDebug>
#include "globalconfig.h"

#define recvSize 86
#define send_data_Size 15
#define recv_data_Size 58
#define MAX_BYTE 48
#define MAX_BIT 8
#define header_recv_addr 0x010A
#define header_send_addr 0x01FD

const uint16_t LOCAL_PORT = 23001;
const uint16_t REMOTE_PORT = 23002;


struct message_header
{
    char identification[8];      //8 bit
    uint16_t ID;                    //16 bit
    uint16_t cycle;                 //16 bit
    uint16_t addr;                  //16 bit
    uint16_t status;                //16 bit
    uint16_t pro_ver;               //16 bit
    uint16_t length;                //16 bit
    uint8_t timestamp[4];             //32 bit
    uint8_t CRC[4];                   //32 bit
};

//接收来自PZB的UDP端口 周期：100ms
struct pd_udp_recv_23001
{
    struct message_header header;
    char spareByte[recv_data_Size];
};

//发送到PZB的UDP端口 周期：100ms,
//short为2个byte大小  定义数据接口中接收变量2、4个byte的需要当前为2、4、8的整数偏移量
struct pd_udp_send_23002
{
    struct message_header header;
    char spareByte[send_data_Size];
};

#define SOCKET int

class UDPSocket
{
public:
    UDPSocket();
    ~UDPSocket();

    int socket_send(struct pd_udp_send_23002 *pd);
    int socket_recv();
    int socket_bind();
    unsigned char* getRecvPointer();

private:
    SOCKET st_udp;
    unsigned char *recvBuffer = NULL;
    struct sockaddr_in bind_addr;
    struct sockaddr_in send_addr;
    struct sockaddr_in recv_addr;
};

#endif // UDPSOCKET_H
