#ifndef CLIENTPOTOCOL_H
#define CLIENTPOTOCOL_H
/*客户端数据协议类*/
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "gatewaydata.h"

class ClientPotocol : public QObject
{
    Q_OBJECT
public:
    explicit ClientPotocol(QObject *parent = nullptr);
    static QByteArray packEnvironmentData(GatewayData* gate);
    static QByteArray packWarningData(GatewayData* gate);
    static QByteArray packHistoryData(QString type,QJsonObject data);
signals:

public slots:
};

#endif // CLIENTPOTOCOL_H
