#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>   //基于TCP协议的服务类
#include <QTcpSocket>   //基于TCP协议的套接字
#include <QByteArray>   //网络字节数组
#include <QList>        //链表
#include <QJsonObject>      //Json对象类
#include <QJsonDocument>    //Json文档类
#include <QJsonArray>
#include "datebase.h"
#include "protocol.h"
#include <QHash>            //哈希表

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void translateData(const QByteArray& data,QTcpSocket* socket);


signals:

public slots:
    void newConnectSlot();  //处理新连接
    void readSlot();        //读取客户端数据
    void disConnectSlot();  //断开连接

private:
    QTcpServer *server;
    QTcpSocket *socket;
    QList<QTcpSocket *> list;
    Datebase *sql;
};

#endif // SERVER_H
