#include "dataparser.h"
#include <QDebug>
#include <QByteArray>
#include "unistd.h"

DataParser::DataParser()
{
    g_UDP_Send = (struct pd_udp_send_23002*)malloc(sizeof(struct pd_udp_send_23002));
    memset(g_UDP_Send, 0, sizeof(struct pd_udp_send_23002));
    memset(&iRcvByte, 0, 48);
    timeAlive = 0;
}

/**
 * @brief 开始线程
 * @param
 * @retval
 */
void DataParser::run()
{
    qDebug()<<"start new thread";
    m_state = true;

    M_Udpsocket = new UDPSocket();
    int res = M_Udpsocket->socket_bind();
    if(res < 0)
    {
        qDebug()<<"Error:bind()";
        return;
    }
    else
    {
        qDebug()<<"Bind() Success";
    }
    writeMemVar(0,0,0,0);
    while(m_state)
    {
        receiveData();
        sendData();


        usleep(1000*100);
    }

    m_state = false;

    //exec();
}

/**
 * @brief 停止线程
 * @param
 * @retval
 */
void DataParser::stop()
{
    free(g_UDP_Send);
    //M_Udpsocket = NULL;
    m_state = false;
}

/**
 * @brief 校验报文头
 * @param pdata UDP接收数据
 * @param nbytes 报文头所占字节
 * @param iaddr 报文头中iddr变量校验值
 * @param ilength 报文头中ilength变量校验值
 * @retval 0 校验正确
 * @retval <0 校验错误
 */
int DataParser::UpdCheck(unsigned char *pdata, int nbytes, int iaddr, int ilength)
{

    //将缓冲区24字节数据拷贝到报文头结构体的各个变量中
    memcpy(&header, pdata, nbytes);

    //比较是否是报文前8个字节定义的TCNPDUDP对应的8个ASCII值
    if ((pdata[0] != 0x50) || (pdata[1] != 0x5A) || (pdata[2] != 0x42)
        || (pdata[3] != 0x44) || (pdata[4] != 0x4D) || (pdata[5] != 0x49)
        || (pdata[6] != 0x43) || (pdata[7] != 0x4D))
    {
         return -1;
    }
    if(header.ID != htons(1))
        return -2;
    if(header.cycle != htons(100))
        return  -3;
    //htons()作用是将变量由主机字节序转换为网络字节序的整数值(host to net)
    if(header.addr != htons(iaddr))
        return -4;

    if(header.status != htons(0x0001))
        return -5;

    if(header.pro_ver != htons(0x0001))
        return -6;

    if(header.length != htons(ilength))
        return -7;

    uint32_t g_timestamp = ((pdata[20])<<24) + ((pdata[21])<<16) + ((pdata[22])<<8) + (pdata[23]);

    if(timeAlive >= g_timestamp )
    {
        return -8;
    }
    timeAlive = g_timestamp;

    uint32_t crc_value = ccitt_crc8(&pdata[28], ilength);
    if(((crc_value >> 24) & 0xFF)!=pdata[24] || ((crc_value >> 16) & 0xFF)!=pdata[25]
            || ((crc_value >> 8) & 0xFF)!=pdata[26] || (crc_value & 0xFF)!=pdata[27])
    {
        return -9;
    }

    return 0;
}


/**
 * @brief 接收数据
 * @param
 * @retval
 */
void DataParser::receiveData()
{
    recvLen = M_Udpsocket->socket_recv();

    if(recvLen < 0)
    {
        qDebug()<<"udp recvived failed";
        return;
    }

    unsigned char* recvbuf = M_Udpsocket->getRecvPointer();
    iHeadcheck=0;
    iHeadcheck = UpdCheck(recvbuf, 28, header_recv_addr, recv_data_Size);
    if(iHeadcheck == 0)
    {
        memcpy(iRcvByte, &recvbuf[28], recvLen-28);
        for(int i = 0;i < GlobalConfig::recvMVBList.size();++i)
        {
            unsigned long tmp = this->readMemVar(GlobalConfig::recvMVBList[i].byte,GlobalConfig::recvMVBList[i].bit,GlobalConfig::recvMVBList[i].size);

            if(Variable_data[i] != tmp)
            {
                Variable_data[i] = tmp;
                emit signalVarChanged(0,i,tmp);
            }
        }
    }
    else
    {
        //qDebug()<<"message header Error";
        emit signalVarChanged(iHeadcheck,0,0);
        memcpy(iRcvByte, &recvbuf[28], recvLen-28);
    }
}

/**
 * @brief 发送数据
 * @param
 * @retval
 */
void DataParser::sendData()
{
    if(M_Udpsocket->socket_send(g_UDP_Send) < 0)
    {
        qDebug()<<"udp send failed.";
    }
}


/**
 * @brief 读取接收数据
 * @param byte 要读取变量的type位置
 * @param bit 要读取变量的bit位置
 * @param size 要读取变量的size
 * @retval value 返回变量的值
 */
unsigned long DataParser::readMemVar(int byte, int bit, int size)
{
    if(size < 8)
    {
        unsigned char tmp = 0;
        switch(size)
        {
        case 1: tmp = 0x01;break;
        case 2: tmp = 0x03;break;
        case 3: tmp = 0x07;break;
        case 4: tmp = 0x0f;break;
        case 5: tmp = 0x1f;break;
        case 6: tmp = 0x3f;break;
        case 7: tmp = 0x7f;break;
        default: break;
        }
        unsigned char value = iRcvByte[byte];
        return (value>>bit) & tmp;
    }
    else if(size == 8)
        return iRcvByte[byte];
    else if(size == 16)
        return ((iRcvByte[byte])<<8) + (iRcvByte[byte+1]);
    else if(size == 32)
        return ((iRcvByte[byte])<<24) + ((iRcvByte[byte+1])<<16)
                + ((iRcvByte[byte+2])<<8) + (iRcvByte[byte+3]);
    else if(size == 48)
        return ( ((iRcvByte[byte])<<40) + ((iRcvByte[byte+1])<<32)
                + ((iRcvByte[byte+2])<<24) + ((iRcvByte[byte+3])<<16)
                + ((iRcvByte[byte+4])<<8) + (iRcvByte[byte+5]));
    return 0;
}


/**
 * @brief 写入发送数据
 * @param byte 发送变量的type位置
 * @param bit 发送变量的bit位置
 * @param size 发送变量的size
 * @param value 发送变量的值
 * @retval
 */
void DataParser::writeMemVar(int byte, int bit, int size, unsigned long value)
{

    strncpy(g_UDP_Send->header.identification,"PZBDMICM",8);

    //htons()作用是将变量由主机字节序转换为网络字节序的整数值。(host to net)
    g_UDP_Send->header.ID = htons(1);
    g_UDP_Send->header.cycle = htons(100);
    g_UDP_Send->header.addr = htons(header_send_addr);
    //g_UDP_Send->header.status = htons(0x0001);
    g_UDP_Send->header.status = 55641;

    g_UDP_Send->header.pro_ver = htons(0x0001);
    g_UDP_Send->header.length = htons(7);

    //发送时间戳

    uint32_t s_time = (uint32_t)clock();
    g_UDP_Send->header.timestamp[0] = (s_time >> 24) & 0xFF;
    g_UDP_Send->header.timestamp[1] = (s_time >> 16) & 0xFF;
    g_UDP_Send->header.timestamp[2] = (s_time >> 8) & 0xFF;
    g_UDP_Send->header.timestamp[3] = (s_time) & 0xFF;


    if(size < 8)
    {
        unsigned char tmp = 0;
        for(int i=0; i<8; ++i)
        {
            if(i>=bit && i<bit+size)
                continue;
            tmp += (0x01<<i);
        }
        unsigned char val = g_UDP_Send->spareByte[byte];
        val &= tmp;
        g_UDP_Send->spareByte[byte] = (value<<bit) + val;
    }
    else if(size == 8)
        g_UDP_Send->spareByte[byte] = value;
    else if(size == 16)
    {
        g_UDP_Send->spareByte[byte] = value >> 8;
        g_UDP_Send->spareByte[byte+1] = value;
    }
    else if(size == 32)
    {
        g_UDP_Send->spareByte[byte] = value >> 24;
        g_UDP_Send->spareByte[byte+1] = value >> 16;
        g_UDP_Send->spareByte[byte+2] = value >> 8;
        g_UDP_Send->spareByte[byte+3] = value;
    }

    uint32_t S_crc_value = ccitt_crc8((unsigned char *)g_UDP_Send->spareByte, send_data_Size);
    g_UDP_Send->header.CRC[0] = (S_crc_value >> 24) & 0xFF;
    g_UDP_Send->header.CRC[1] = (S_crc_value >> 16) & 0xFF;
    g_UDP_Send->header.CRC[2] = (S_crc_value >> 8) & 0xFF;
    g_UDP_Send->header.CRC[3] = S_crc_value & 0xFF;
}

