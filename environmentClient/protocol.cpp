#include "protocol.h"

Protocol::Protocol(QObject *parent) : QObject(parent)
{

}
//协议打包函数
QByteArray Protocol::packData(QString type, QString requestType,QString boxID)
{
    //定义Json对象，用来加载零散数据
    QJsonObject json;
    json.insert("type",type);
    json.insert("requestType",requestType);
    json.insert("boxID",boxID);
    //因为Json对象不能直接进行网络传输，所以需要转换成Json文档
    QJsonDocument jsonDoc(json);
    //把Json文档转换成qbyteArray,进行网络传输
    return jsonDoc.toJson();
}

QByteArray Protocol::packData2(QString type, QString tablename, QString hour)
{
    //定义Json对象，用来加载零散数据
    QJsonObject json;
    json.insert("type",type);
    json.insert("name",tablename);
    json.insert("hour",hour);
    //因为Json对象不能直接进行网络传输，所以需要转换成Json文档
    QJsonDocument jsonDoc(json);
    //把Json文档转换成qbyteArray,进行网络传输
    return jsonDoc.toJson();
}
