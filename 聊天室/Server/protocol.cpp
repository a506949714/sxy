#include "protocol.h"

Protocol::Protocol(QObject *parent) : QObject(parent)
{

}

//打包协议函数
QByteArray Protocol::packData(QString type, QString key1, QString value1, QString key2, QString value2, QString key3, QString value3, QString key4, QString value4)
{
    //定义Json对象，用来加载零散数据
    QJsonObject json;
    json.insert("type",type);
    json.insert(key1,value1);
    json.insert(key2,value2);
    json.insert(key3,value3);
    json.insert(key4,value4);
    //因为Json对象不能直接进行网络传输，所以需要转换成Json文档
    QJsonDocument jsonDoc(json);
    //把Json文档转换成QByteArray,进行网络传输
    return jsonDoc.toJson();
}

QByteArray Protocol::packList(QString type, QString key1, const QJsonArray &array)
{
    QJsonObject json;
    json.insert("type",type);
    json.insert(key1,array);
    QJsonDocument jsonDoc(json);
    return jsonDoc.toJson();
}
