#include "networkpotocol.h"

NetworkPotocol::NetworkPotocol(QObject *parent) : QObject(parent)
{

}

QByteArray NetworkPotocol::packCtrlData(QString type, QString key1, QString value1, QString key2, QString value2, QString key3, QString value3, QString key4, QString value4, QString key5, QString value5)
{
    QJsonObject json;
    json.insert("type",type);
    json.insert(key1,value1);
    json.insert(key2,value2);
    json.insert(key3,value3);
    json.insert(key4,value4);
    json.insert(key5,value5);
    QJsonDocument jsonDoc(json);
    return jsonDoc.toJson();
}
