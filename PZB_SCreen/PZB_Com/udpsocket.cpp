#include "udpsocket.h"

UDPSocket::UDPSocket()
{
    st_udp = socket(AF_INET,SOCK_DGRAM,0);//定义一个socket
    //建立一个socket,第一个参数是指定socket要用哪个协议,AF_INET代表要用TCP/IP协议
    //第二个参数SOCK_DGRAM意思是要用UDP协议
    //第三个参数一般默认填0
    if(recvBuffer)
    {
        delete []recvBuffer;
    }
    recvBuffer = new unsigned char [recvSize];
    memset(recvBuffer,0,recvSize);
}

UDPSocket::~UDPSocket()
{
    close(st_udp);
   if(recvBuffer)
   {
       delete recvBuffer;
       recvBuffer = 0;
   }

}

/**
 * @brief UDP发送数据
 * @param sendbuf   发送的结构体(报文头+数据)
 * @retval >0 发送成功，返回发送数据字节数
 * @retval <0 发送失败
 */
int UDPSocket::socket_send(struct pd_udp_send_23002 *sendbuf)
{
    //st_send = socket(AF_INET, SOCK_DGRAM, 0);
    //struct sockaddr_in send_addr;
    memset(&send_addr, 0, sizeof(send_addr));//初始化结构addr
    send_addr.sin_family = AF_INET;//代表要使用一个TCP/IP的地址
    send_addr.sin_port = htons(REMOTE_PORT);//host to net short  htons(SEND_PORT)
    send_addr.sin_addr.s_addr = inet_addr(GlobalConfig::PZB_IP.toStdString().c_str());

    size_t rc = 0;

    //发送udp数据
    rc = sendto(st_udp,sendbuf,sizeof(*sendbuf),0,(struct sockaddr *)&send_addr,sizeof(struct sockaddr));
    return rc;
}


/**
 * @brief UDP接收数据
 * @param
 * @retval >0 接收成功，返回接收的数据字节数
 * @retval <0 接收失败
 */
int UDPSocket::socket_recv()
{
    memset(recvBuffer,0,recvSize);
    //struct sockaddr_in addr;
    memset(&recv_addr, 0, sizeof(recv_addr));//初始化结构addr
    recv_addr.sin_family = AF_INET;//代表要使用一个TCP/IP的地址
    recv_addr.sin_port = htons(LOCAL_PORT);//host to net short  htons(SEND_PORT)

    socklen_t recv_addr_len = sizeof(recv_addr);

    size_t rc = recvfrom(st_udp,recvBuffer,recvSize,0,(struct sockaddr *)&recv_addr,&recv_addr_len);

    return rc;
}

/**
 * @brief UDP绑定端口
 * @param
 * @retval 0 绑定成功
 * @retval <0 绑定失败
 */
int UDPSocket::socket_bind()
{
    memset(&bind_addr,0,sizeof(bind_addr));//初始化addr
    bind_addr.sin_family = AF_INET;//代表要使用一个TCP/IP的地址
    bind_addr.sin_port = htons(LOCAL_PORT);
    bind_addr.sin_addr.s_addr = htonl(INADDR_ANY);//作为接收方，不需要指定具体的IP地址，接受的主机是什么IP，我就在什么IP接受数据
    //inet_pton(AF_INET, GlobalConfig::DMI_IP.toStdString().c_str(), (void *)&bind_recv_addr.sin_addr.s_addr);
    bind_addr.sin_addr.s_addr = inet_addr(GlobalConfig::DMI_IP.toStdString().c_str());


    return bind(st_udp, (struct sockaddr *)&bind_addr, sizeof(bind_addr));//将端口号和程序绑定
}


/**
 * @brief 获取接收数据的值
 * @param
 * @retval recvBuffer 返回接收数据的数组
 */
unsigned char* UDPSocket::getRecvPointer()
{
    return recvBuffer;
}


