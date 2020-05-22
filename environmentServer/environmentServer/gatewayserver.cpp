#include "gatewayserver.h"
#include <QDebug>
#include "clientserver.h"

GatewayServer* GatewayServer::serverPtr=NULL;

GatewayServer::GatewayServer(QObject *parent) : QTcpServer(parent)
{
    this->listen(QHostAddress::AnyIPv4,10010);
    connect(this,SIGNAL(receiveData(QString,QJsonObject)),ClientServer::getClientServer(),SLOT(receiveGateData(QString,QJsonObject)));
}

//返回当前类唯一对象的指针
GatewayServer *GatewayServer::getGateServer()
{
   if(serverPtr==NULL)
   {
       serverPtr=new GatewayServer;
   }
   return serverPtr;
}

void GatewayServer::translateData(GatewaySocket *socket, const QByteArray &data)
{
    QJsonDocument jsonDoc=QJsonDocument::fromJson(data);
    QJsonObject json=jsonDoc.object();
    QString type=json.value("type").toString();
    if(type=="boxID")
    {
        QString id=json.value("id").toString();
        socket->setBoxID(id);//设置socket的箱子编号属性
    }
    else{
        //转发给 客户端服务类
        emit receiveData(socket->getBoxID(),json);
    }
}

void GatewayServer::incomingConnection(qintptr handle)
{
    GatewaySocket *socket=new GatewaySocket;
    socket->setSocketDescriptor(handle);//设置套接字描述符
    qDebug()<<"新连接:"<<socket->peerAddress().toString();
    this->addPendingConnection(socket);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readSlot()));
    //
    QThread *th=new QThread;
    socket->moveToThread(th);//将socket移入到th线程中
    th->start();//启动线程
    hash.insert(socket,th);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disConnectSlot()));
}
//读取数据 槽函数
void GatewayServer::readSlot()
{
    GatewaySocket *socket=(GatewaySocket*)sender();
    QByteArray data;
    while(socket->bytesAvailable())
    {
        data.append(socket->readAll());
    }
    //接收到网关发来的数据data
    //分割
    qDebug()<<data;
    while (!data.isEmpty()) {
       QByteArray temp=data.mid(0,data.indexOf("}\n")+2);
       data.remove(0,temp.length());
       //调用解析函数（提取箱子编号）
       translateData(socket,temp);
    }
}
//客户端断开的相应操作
void GatewayServer::disConnectSlot()
{
    GatewaySocket *socket = (GatewaySocket*)sender();
    qDebug()<<"断开连接"<<socket->peerAddress().toString();
    socket->disconnect();
    socket->deleteLater();
    hash.value(socket)->terminate();//强制退出线程
    hash.remove(socket);
}
