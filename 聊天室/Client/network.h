#ifndef NETWORK_H
#define NETWORK_H
//网络类-- 单一模式
#include <QObject>
#include <QTcpSocket>

class NetWork : public QObject
{
    Q_OBJECT
private:
    explicit NetWork(QObject *parent = nullptr);

public:
    static NetWork* getInstance();
    bool sendData(const QByteArray& data);

signals:
    void receiveData(const QByteArray& data);
public slots:
    void connectSlot();
    void readSlot();
    void disConnectSlot();
private:
    QTcpSocket *socket;
    bool success;
};

#endif // NETWORK_H
