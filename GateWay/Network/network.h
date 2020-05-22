#ifndef NETWORK_H
#define NETWORK_H
/*网络类 单例类*/
#include <QObject>
#include <QTcpSocket>   //基于Tcp协议的套接字
#include <QDateTime>    //日期时间类
#include <QDebug>

class Network : public QObject
{
    Q_OBJECT
private:
    explicit Network(QObject *parent = 0);

public:
    static Network* getNet();
    QString getTime();
    bool sendData(const QByteArray& data);
signals:
    void sendSerialData(const QJsonObject& json);
public slots:
    void connectSlot();
    void readSlot();
    void disconnectSlot();
private:
    QTcpSocket *socket;
    bool    success; //网络连接状态

};

#endif // NETWORK_H
