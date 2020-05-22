#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    //构造server
    server = new QTcpServer;
    //监听
    server->listen(QHostAddress::AnyIPv4,2020);
    //最大连接数
    server->setMaxPendingConnections(80);//默认30
    //构造数据库对象
    sql = new Datebase;
    //绑定新连接信号与槽
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnectSlot()));

}

void Server::translateData(const QByteArray &data, QTcpSocket *socket)
{
    //首先 数据转换
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject json = jsonDoc.object();
    //提取数据
    double light = json.value("light").toDouble();
    double temp = json.value("temp").toDouble();
    double hum = json.value("hum").toDouble();
    if(!sql->insertdata(temp,hum,light))
        qDebug()<<"插入失败！";
    for( int i=0; i< list.size(); ++i)
    {
        if(list.at(i)!=socket)
        {
            list.at(i)->write(Protocol::packd(light,temp,hum));
        }
    }
}


//处理新连接
void Server::newConnectSlot()
{
    //给新连接客户端分配套接字
    QTcpSocket* socket = server->nextPendingConnection();
    //打印客户端IP
    qDebug()<<"新连接："<<socket->peerAddress().toString();
    //绑定客户端新消息和槽
    connect(socket,SIGNAL(readyRead()),this,SLOT(readSlot()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disConnectSlot()));
    //保存socket
    list.append(socket);
}

//读取客户端数据
void Server::readSlot()
{
    //
    QTcpSocket *socket = (QTcpSocket*)sender();
    QByteArray data;
    while(socket->bytesAvailable())    //返回当前套接字中未接受的数据字节数
    {
        data.append(socket->readAll());
    }
    translateData(data,socket);
    //
    /*while(!data.isEmpty())
    {
        QByteArray temp = data.mid(0,data.indexOf("}\n")+2);
        data.remove(0,temp.length());

    }*/


}

//客户端断开处理
void Server::disConnectSlot()
{
    QTcpSocket *socket = (QTcpSocket*)sender();
    qDebug()<<socket->peerAddress().toString()<<"断开连接";

    socket->disconnect();//断开绑定
    list.removeOne(socket);//删除指定元素
    socket->deleteLater();//适当的时候释放内存

}


