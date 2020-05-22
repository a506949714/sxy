#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    //构造server
    server = new QTcpServer;
    //监听
    server->listen(QHostAddress::AnyIPv4,2222);
    //最大连接数
    server->setMaxPendingConnections(80);//默认30
    //构造数据库对象
    sql = new DataBase;
    //绑定新连接信号与槽
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnectSlot()));
}

void Server::translateData(QTcpSocket *socket, const QByteArray &data)
{
        //数据转换
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject json = jsonDoc.object();
        //qDebug()<<"客户端数据:"<<json;
        QString type = json.value("type").toString();
        //根据type判断数据身份然后进行相应的操作
        //若干个分支语句
        if(type == "face")
        {
            QString ID = json.value("ID").toString();
            QList<QString> man;
            man = sql->selectTable("0");
            QString xuehao = man[0];
            QString name = man[1];
            qDebug()<<xuehao<<name;
            //sql->selectTable();
            sql->insertTable(xuehao,name,"0","face");
        }
        else if(type == "card")
        {
            QString number = json.value("number").toString();
            //sql->selectTable();
            //sql->insertTable();
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
    qDebug()<<data;
    translateData(socket,data);
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


