#ifndef NETWORKPROTOCAL_H
#define NETWORKPROTOCAL_H
/*网络协议类-单例模式*/
#include <QObject>
#include <QJsonObject>      //Json对象
#include <QJsonDocument>    //Json文档
#include <QJsonArray>       //Json数组

class NetworkProtocal : public QObject
{
    Q_OBJECT
private:
    explicit NetworkProtocal(QObject *parent = 0);

public:
    static NetworkProtocal* getNetPro();
    //1号节点板
    void handleNode1Data3(int bodyred);
    void handleNode1Data4(QJsonArray array1, QJsonArray array2,int bodyred);
    //2号节点板
    void handleNode2Data(double temp,double hum,int co2,double light,int ult);
    void handleNode2Data1(double temp,double hum);
    void handleNode2Data2(int co2);
    void handleNode2Data3(double light);
    void handleNode2Data4(int ult);
    //3号节点板
    void handleNode3Data1(int smoke);
    void handleNode3Data2(int CH4);
    void handleNode3Data3(int fire);
    void handleNode3Data4(int bodyred);
    void handleNode3Data5(int smoke,int CH4,int fire,int bodyred);
    //4号节点板
    void handleNode4Data1(double PM2_5);
    void handleNode4Data2(double temp,double hum);
    void handleNode4Data3(double PM2_5,double temp,double hum);
    //5号节点板
    void handleNode5Data3(int countshooting);
    void handleNode5Data4(int reflect);
    void handleNode5Data5(int alarmlamp,int alarm,int countshooting,int reflect);
    //6号节点板
    void handleNode6Data2(int steering);
    //7号节点板
    void handleNode7Data4(int fan,int steeperdir,int steeperen,int relay1,int relay2);
    //8号节点板
    void handleNode8Data2(int lock);

    QByteArray packData(QString type,int node,QString key1="",double value1=0,QString key2="",double value2=0,
                        QString key3="",double value3=0,QString key4="",double value4=0,QString key5="",double value5=0);

    QByteArray packArrayData(QString type,int node,QString key1,QJsonArray array1,QString key2,QJsonArray array2,QString key3,int value);
    QByteArray packBoxID(QString type,QString key,QString value);

signals:

public slots:
    void receiveSerialProSlot(quint8 node,quint8 device,QByteArray data);

};

#endif // NETWORKPROTOCAL_H
