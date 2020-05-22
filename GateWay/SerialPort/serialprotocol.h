#ifndef SERIALPROTOCOL_H
#define SERIALPROTOCOL_H
/*串口协议类*/
#include <QObject>
#include<QTimer>//定时器头文件
#include"serialdev.h"//串口设备类

//发送数据结构体
typedef struct
{
    quint8      head[2];//帧头
    quint8      save;//保留位
    quint8      addr[2];//短地址
    quint8      length;//帧长度
    quint8      node;//节点编号
    quint8      device;//设备编号
    QByteArray  data;//数据
    quint8      tail;//帧尾
}SendData;
//接收数据结构体
typedef struct
{
    quint8      head[2];//帧头
    quint8      save;//保留位
    quint8      addr[2];//短地址
    quint8      length;//帧长度
    quint8      node;//节点编号
    quint8      device;//设备编号
    QByteArray  data;//数据
    quint8      tail;//帧尾
}ReceiveData;
class SerialProtocol : public QObject
{
    Q_OBJECT
public:
    explicit SerialProtocol(QObject *parent = 0);
    void packData(quint8 node,quint8 device);
    QByteArray packDataToArray();
    void handleData();
signals:
    void transmitData(quint8 node,quint8 device,QByteArray data);
public slots:
    void timerSlot();
    void receiveDataSlot(QByteArray data);
private:
    SendData sendData;//发送数据的结构体变量
    ReceiveData receiveData;//接收数据的结构体变量
    QByteArray data;//具体的请求控制数据
    QTimer    *timer;//定时器,以固定频率请求设备数据
    quint8    buffer[128];//保存完整数据帧的缓存
    int       len;//当前buffer的有效长度
};

#endif // SERIALPROTOCOL_H
