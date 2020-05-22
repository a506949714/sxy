#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

class Protocol : public QObject
{
    Q_OBJECT
public:
    explicit Protocol(QObject *parent = nullptr);
    static QByteArray packUsers(bool aa);
    static QByteArray packData(QString type,QString key1 = "",QString value1="",
                               QString key2="",QString value2="",
                               QString key3="",QString value3="",
                               QString key4="",QString value4="");//从第一个赋值的数开始后面都要赋值
signals:

public slots:
};

#endif // PROTOCOL_H
