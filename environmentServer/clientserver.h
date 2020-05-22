#ifndef CLIENTSERVER_H
#define CLIENTSERVER_H

#include <QObject>
#include <QHash>
#include "gatewaydata.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "clientpotocol.h"
#include"database.h"

class ClientServer : public QObject
{
    Q_OBJECT
private:
    explicit ClientServer(QObject *parent = 0);
public:
    static ClientServer* getClientServer();
    void translateData(QTcpSocket* socket,const QByteArray &data);
signals:
    void sendGateWayServer(const QString& boxID,const QByteArray& data);
public slots:
    void receiveGateData(QString boxID,const QJsonObject& json);
    void newConnectSlot();
    void readSlot();
    void disconnectSlot();
private:
    QHash<QString,GatewayData*> boxHash;
    QTcpServer *server;
    Database   *db;
};

#endif // CLIENTSERVER_H
