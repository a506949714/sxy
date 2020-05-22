#include "server.h"
#include <QDebug>
#include "protocol.h"

Server::Server(QObject *parent) : QObject(parent)
{
    //构造server
    server = new QTcpServer;
    //监听
    server->listen(QHostAddress::AnyIPv4,10086);
    //最大连接数
    server->setMaxPendingConnections(80);//默认30
    //构造数据库对象
    sql = new Datebase;
    //绑定新连接信号与槽
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnectSlot()));
}

//解析数据函数
void Server::translateData(const QByteArray &data, QTcpSocket *socket)
{
    //首先 数据转换
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject json = jsonDoc.object();
    //提取数据身份标识
    QString type = json.value("type").toString();
    if(type == "register")//注册数据
    {
        //提取有效数据
        QString ID,Name,Password;
        ID = json.value("id").toString();
        Name = json.value("name").toString();
        Password = json.value("password").toString();
        int res = sql->registerInfo(ID,Name,Password);
        //注册操作
        if(res == -1)
        {
            socket->write(Protocol::packData("reg-back","result","fail"));
        }else if(res == 0){
            socket->write(Protocol::packData("reg-back","result","have"));
        }else if(res == 1){
            socket->write(Protocol::packData("reg-back","result","success"));
        }

    }
    else if(type == "login")
    {
        QString ID,Password;
        ID = json.value("id").toString();
        Password = json.value("password").toString();
        if(sql->loginCheck(ID,Password))
        {
            //防止重复登录
            if(hash.contains(hash.key(ID)))
                return;
            socket->write(Protocol::packData("log-back","result","success"));
            hash.insert(socket,ID);
            //自动回复在线列表
            socket->write(Protocol::packList("onlinelist-back","array",getOnlineList()));
            //群发自身上线信息
            //遍历哈希表
            QHash<QTcpSocket*,QString>::const_iterator it;
            for(it=hash.begin();it!=hash.end();++it)
            {
                if(it.key()!=socket)
                {
                    QString info;
                    info.append(sql->getName(hash.value(socket)));
                    info.append("(");
                    info.append(hash.value(socket));
                    info.append(")");
                    it.key()->write(Protocol::packData("newonline-back","info",info));
                }
            }
        }else{
            socket->write(Protocol::packData("log-back","result","fail"));
        }
    }
    else if(type == "wechat")
    {
        QString text,time,name;
        text = json.value("text").toString();
        time = json.value("time").toString();
        name = sql->getName(hash.value(socket));
        //使用迭代器遍历哈希表
        QHash<QTcpSocket*,QString>::const_iterator it;
        for(it=hash.begin();it!=hash.end();++it)
        {
            if(it.key() != socket)
            {
                it.key()->write(Protocol::packData("wechat-back","time",time,"text",text,"name",name));
            }
        }

    }
    else if(type == "onechat")
    {
        QString text,time,id;
        text = json.value("text").toString();
        time = json.value("time").toString();
        id = json.value("id").toString();
        QString info;
        info.append(sql->getName(hash.value(socket)));
        info.append("(");
        info.append(hash.value(socket));
        info.append(")");
        //转发
        if(hash.contains(hash.key(id)))
        {
            hash.key(id)->write(Protocol::packData("onechat-back","text",text,"time",time,"info",info));
        }
        else
        {
            //通知socket对方下线
            oneOffLine(id,socket);
        }
    }
}

//获取在线列表（姓名（123456789））
QJsonArray Server::getOnlineList()
{
    QJsonArray array;
    //遍历哈希表
    QHash<QTcpSocket*,QString>::const_iterator it;
    for(it=hash.begin();it!=hash.end();++it)
    {
        QString info;//姓名(123456789)
        info.append(sql->getName(it.value()));
        info.append("(");
        info.append(it.value());
        info.append(")");
        array.append(info);
    }
    return array;
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
    //
    while(!data.isEmpty())
    {
        QByteArray temp = data.mid(0,data.indexOf("}\n")+2);
        data.remove(0,temp.length());
        translateData(temp,socket);
    }

}

//客户端断开处理
void Server::disConnectSlot()
{
    QTcpSocket *socket = (QTcpSocket*)sender();
    qDebug()<<socket->peerAddress().toString()<<"断开连接";
    //群发自身下线信息
    //遍历哈希表
    QHash<QTcpSocket*,QString>::const_iterator it;
    for(it=hash.begin();it!=hash.end();++it)
    {
            QString info;
            info.append(sql->getName(hash.value(socket)));
            info.append("(");
            info.append(hash.value(socket));
            info.append(")");
            it.key()->write(Protocol::packData("offline-back","info",info));
    }
    socket->disconnect();//断开绑定
    list.removeOne(socket);//删除指定元素
    hash.remove(socket);//删除在线信息
    socket->deleteLater();//适当的时候释放内存
}

void Server::oneOffLine(QString id, QTcpSocket *socket)
{
    QString info;
    info.append(sql->getName(id));
    info.append("("+id+")");
    socket->write(Protocol::packData("oneoff-back","info",info));
}
