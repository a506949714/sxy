#ifndef GATEWAYSOCKET_H
#define GATEWAYSOCKET_H
/*网关套接字类*/
#include <QObject>
#include <QTcpSocket>

class GatewaySocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit GatewaySocket(QObject *parent = 0);
    void setBoxID(QString id);
    QString getBoxID();
signals:

public slots:

private:
    QString boxID;//网关箱子的编号

};

#endif // GATEWAYSOCKET_H
