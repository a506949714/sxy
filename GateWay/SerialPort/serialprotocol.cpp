#include "serialprotocol.h"
#include "Network/networkprotocol.h"

SerialProtocol::SerialProtocol(QObject *parent) : QObject(parent)
{
    len=0;
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerSlot()));
    timer->start(4000);
    connect(SerialDev::getInstance(),SIGNAL(receiveData(QByteArray)),this,SLOT(receiveDataSlot(QByteArray)));
    connect(this,SIGNAL(transmitData(quint8,quint8,QByteArray)),NetworkProtocol::getNetPro(),SLOT(receiveSerialProSlot(quint8,quint8,QByteArray)));
}
//打包成结构体变量
void SerialProtocol::packData(quint8 node, quint8 device)
{
    sendData.head[0]=0XFE;//下行数据
    sendData.head[1]=0xfe;
    sendData.save   =0x00;
    sendData.addr[0]=0xff;
    sendData.addr[1]=0xff;
    sendData.length =9+this->data.length();
    sendData.node   =node;
    sendData.device =device;
    sendData.data   =this->data;
    sendData.tail   =0xff;
}
//将结构体变量转换成QByteArray
QByteArray SerialProtocol::packDataToArray()
{
    QByteArray temp;
    temp.append((char*)sendData.head,2);
    temp.append((char*)&sendData.save,1);
    temp.append((char*)sendData.addr,2);
    temp.append((char*)&sendData.length,1);
    temp.append((char*)&sendData.node,1);
    temp.append((char*)&sendData.device,1);
    temp.append(sendData.data);
    temp.append((char*)&sendData.tail,1);
    return temp;
}
//将buffer中的数据存到结构体中
void SerialProtocol::handleData()
{
    receiveData.head[0]=buffer[0];
    receiveData.head[1]=buffer[1];
    receiveData.save   =buffer[2];
    receiveData.addr[0]=buffer[3];
    receiveData.addr[1]=buffer[4];
    receiveData.length =buffer[5];
    receiveData.node   =buffer[6];
    receiveData.device =buffer[7];
    for(int i=0;i<buffer[5]-9;++i)
    {
        receiveData.data[i]=buffer[8+i];
    }
    receiveData.tail   =buffer[buffer[5]-1];
    //将receiveData转发给网络模块
    qDebug()<<"数据帧:"<<receiveData.data.toHex();
    emit transmitData(receiveData.node,receiveData.device,receiveData.data);
}
//请求数据槽函数
void SerialProtocol::timerSlot()
{
    //例：2号节点板
    packData(0x02,0x05);
    //发送函数
    if(!SerialDev::getInstance()->serialState())
    {
        SerialDev::getInstance()->openSerialPort();
    }
    SerialDev::getInstance()->sendData(packDataToArray());
}
//接收转发来的原始数据片段 并进行拼接
void SerialProtocol::receiveDataSlot(QByteArray data)
{
    for(int i=0;i<data.size();++i)
    {
        //处理帧头
        if((quint8)data[i]==0xef&&len>0)
        {
            if(buffer[len-1]==0xef){
                buffer[0]=0xef;
                buffer[1]=0xef;
                len=2;
                continue;
            }
        }
        //处理帧尾
        if(len>5&&(quint8)data[i]==0xff&&len+1==buffer[5])
        {
           buffer[len]=0xff;
           //处理完整的一帧 buffer
           handleData();
           len=0;
           continue;
        }
        //普通数据和残缺帧头，但残缺帧头会被两个if处理
        buffer[len++]=(quint8)data[i];
    }
}










