#ifndef NETWORKPROTOCOL_H
#define NETWORKPROTOCOL_H
/*网络协议类-单例模式*/
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>//json数组


class NetworkProtocol : public QObject
{
    Q_OBJECT
private:
    explicit NetworkProtocol(QObject *parent = 0);
public:
    static NetworkProtocol* getNetPro();
    void handleNode2Data(double temp,double hum,int co2,int light,int ult);
    QByteArray packData(QString type,int node,
                        QString key1="",double value1=0,
                        QString key2="",double value2=0,
                        QString key3="",double value3=0,
                        QString key4="",double value4=0,
                        QString key5="",double value5=0);
    QByteArray packArrayData(QString type,int node,
                             QString key1,QJsonArray array1,
                             QString key2,QJsonArray array2,
                             QString key3,int value);
    QByteArray packBoxID(QString type,QString key,QString value);
signals:

public slots:
    void receiveSerialProSlot(quint8 node,quint8 device,QByteArray data);
};

#endif // NETWORKPROTOCOL_H
