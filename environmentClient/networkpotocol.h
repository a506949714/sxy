#ifndef NETWORKPOTOCOL_H
#define NETWORKPOTOCOL_H
/*网络协议类*/
#include <QObject>
#include<QJsonObject>
#include<QJsonDocument>

class NetworkPotocol : public QObject
{
    Q_OBJECT
public:
    explicit NetworkPotocol(QObject *parent = nullptr);
    static QByteArray packCtrlData(QString type,
                                   QString key1="",QString value1="",
                                   QString key2="",QString value2="",
                                   QString key3="",QString value3="",
                                   QString key4="",QString value4="",
                                   QString key5="",QString value5="");
signals:

public slots:
};

#endif // NETWORKPOTOCOL_H
