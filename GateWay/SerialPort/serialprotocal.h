#ifndef SERIALPROTOCAL_H
#define SERIALPROTOCAL_H
/*串口协议类*/
#include <QObject>
#include <QTimer>   //定时器头文件
#include "serialdev.h" //串口设备类


//发送数据结构体
typedef struct
{
    quint8      head[2];//帧头
    quint8      save;   //保留位
    quint8      addr[2];//短地址
    quint8      length; //帧长度
    quint8      node;   //节点编号
    quint8      device; //设备编号
    QByteArray  data; //数据
    quint8      tail;   //帧尾
}SendData;

//接收数据结构体
typedef struct
{
    quint8      head[2];//帧头
    quint8      save;   //保留位
    quint8      addr[2];//短地址
    quint8      length; //帧长度
    quint8      node;   //节点编号
    quint8      device; //设备编号
    QByteArray  data; //数据
    quint8      tail;   //帧尾
}ReceiveData;

class SerialProtocal : public QObject
{
    Q_OBJECT
public:
    explicit SerialProtocal(QObject *parent = 0);
    void packData(quint8 node,quint8 device);
    QByteArray packDataToArray();
    void packData2(quint8 node,quint8 device);
    QByteArray packData2ToArray();
    void handleData();
    void changeID();//改变节点编号和设备编号
    void changeAllID();
    void checkenvironment();

signals:
    void transmitData(quint8 node,quint8 device,QByteArray data);

public slots:
    void timerSlot();
    void receiveDataSlot(QByteArray data);
    void receiveNetDataSlot(const QJsonObject& json);
private:
    SendData sendData;//发送数据变量
    SendData sendData2;//控制数据的变量
    ReceiveData receiveData;//接收数据变量
    QByteArray data;//具体的请求控制数据
    QTimer  *timer;//定时器，以固定频率请求设备数据
    quint8  buffer[128];//保存完整数据帧的缓存
    int     len;//当前buffer的有效长度
    int     nodeID;
    int     deviceID;

};

#endif // SERIALPROTOCAL_H
