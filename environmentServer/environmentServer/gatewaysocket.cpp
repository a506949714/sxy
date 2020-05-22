#include "gatewaysocket.h"

GatewaySocket::GatewaySocket(QObject *parent) : QTcpSocket(parent)
{

}
//设置箱子编号
void GatewaySocket::setBoxID(QString id)
{
    boxID = id;
}
//获取当前对象的 boxID
QString GatewaySocket::getBoxID()
{
    return boxID;
}
