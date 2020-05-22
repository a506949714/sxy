#ifndef PROTOCOL_H
#define PROTOCOL_H
/*通信协议类*/
#include <QObject>
#include <QJsonObject>      //Json对象类
#include <QJsonDocument>    //Json文档类


class Protocol : public QObject
{
    Q_OBJECT
public:
    explicit Protocol(QObject *parent = nullptr);
    static QByteArray packData(QString type,QString key1 = "",QString value1="",
                               QString key2="",QString value2="",
                               QString key3="",QString value3="",
                               QString key4="",QString value4="");//从第一个赋值的数开始后面都要赋值
    static QByteArray packList(QString type,QString key1,const QJsonArray& array);
signals:

public slots:
};

#endif // PROTOCOL_H
