#ifndef PROTOCOL_H
#define PROTOCOL_H
/*通信协议类*/
#include <QObject>
#include <QJsonObject>//Json对象类
#include<QJsonDocument>//Json文档类


class Protocol : public QObject
{
    Q_OBJECT
public:
    explicit Protocol(QObject *parent = nullptr);
    static QByteArray packData(QString type, QString requestType, QString boxID);
    static QByteArray packData2(QString type, QString tablename, QString hour);
signals:

public slots:
};

#endif // PROTOCOL_H
