#include "network.h"
#include<QDebug>

NetWork::NetWork(QObject *parent) : QObject(parent),success(false)
{
    socket=new QTcpSocket;
    //连接指定服务器
    socket->connectToHost("172.16.20.42",10000);
    //验证是否连接成功
    connect(socket,SIGNAL(connected()),this,SLOT(connectSlot()));
    //绑定接收数据的信号到槽
    connect(socket,SIGNAL(readyRead()),this,SLOT(readSlot()));
    //绑定断开信号和槽函数
    connect(socket,SIGNAL(disconnected()),this,SLOT(disConnectSlot()));
}
//返回唯一对象的指针
NetWork *NetWork::getInstance()
{
    static NetWork net;//改变对象的存储位置
    return &net;
}
//发送数据
bool NetWork::sendData(const QByteArray &data)
{
    if(!success)
        return false;
    int len = socket->write(data);
    return len==-1?false:true;
}
//验证连接
void NetWork::connectSlot()
{
    qDebug()<<"连接服务器成功！";
    success=true;
}
//读取服务器数据
void NetWork::readSlot()
{
    QByteArray data;
    while(socket->bytesAvailable()){
        data.append(socket->readAll());
    }
    while(!data.isEmpty()){
        QString str(data);
        qDebug()<<str;
        QByteArray temp=data.mid(0,data.indexOf("}\n")+2);
        data.remove(0,temp.length());
        emit receiveData(temp);
    }
}
//断开连接的槽函数
void NetWork::disConnectSlot()
{
    success=false;
}
