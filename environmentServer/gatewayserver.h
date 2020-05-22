#ifndef GATEWAYSERVER_H
#define GATEWAYSERVER_H
/*网关服务类 单例类*/
#include <QObject>
#include <QTcpServer>
#include <gatewaysocket.h>
#include <QList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QThread>  //平台无关的线程类
#include <QHash>    //

class GatewayServer : public QTcpServer
{
    Q_OBJECT
private:
    explicit GatewayServer(QObject *parent = 0);
public:
    static GatewayServer* getGateServer();
    void translateData(GatewaySocket* socket,const QByteArray& data);
protected:
    void incomingConnection(qintptr handle);

signals:
    void receiveData(QString boxID,const QJsonObject& json);
public slots:
    void readSlot();
    void disConnectSlot();
    void receiveClientServerSlot(const QString& boxID,const QByteArray& data);
private:
    QTcpServer *server;
    QList<GatewaySocket* > list;
    QHash<GatewaySocket* ,QThread* > hash;
    static GatewayServer *serverPtr;

};

#endif // GATEWAYSERVER_H
