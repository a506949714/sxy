#include "network.h"
#include "networkprotocal.h"

Network::Network(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket;
    socket->connectToHost("172.16.20.42",10010);
    success = false;//默认没有网络连接
    connect(socket,SIGNAL(connected()),this,SLOT(connectSlot()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readSlot()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnectSlot()));
}

Network *Network::getNet()
{
    static Network net;
    return &net;
}

//返回时间戳
QString Network::getTime()
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    return time;
}

//发送数据
bool Network::sendData(const QByteArray &data)
{
    if(!success)
        return false;
    int len = socket->write(data);
    return len==-1?false:true;
}

void Network::connectSlot()
{
    success = true;
    qDebug()<<getTime()<<" 网络连接成功！";
    QByteArray data = NetworkProtocal::getNetPro()->packBoxID("boxID","id","666666");
    sendData(data);
}
//接收服务器数据
void Network::readSlot()
{
    QByteArray data;
    data = socket->readAll();
     qDebug()<<data;
    //
    QJsonDocument jsonDoc=QJsonDocument::fromJson(data);
    QJsonObject json=jsonDoc.object();
    QString type=json.value("type").toString();
    if(type=="ctrldata")
    {
        //以信号参数的形式将数据转发给串口模块
        emit sendSerialData(json);
    }
}

void Network::disconnectSlot()
{
    success = false;
    disconnect(socket);
    socket->deleteLater();
    qDebug()<<getTime()<<" 网络连接断开！";
}
