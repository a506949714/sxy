#include "serialdev.h"

SerialDev::SerialDev(QObject *parent) : QObject(parent)
{
    serial =nullptr;
    initSerialPort();
    openSerialPort();
    connect(serial,SIGNAL(readyRead()),this,SLOT(readSlot()));

}

//初始化串口
void SerialDev::initSerialPort()
{
    if(serial !=nullptr)
        return ;

    serial = new QSerialPort;//构造串口对象
    serial->setBaudRate(QSerialPort::Baud57600);//设置波特率
    serial->setDataBits(QSerialPort::Data8);//设置数据位
    serial->setParity(QSerialPort::NoParity);//设置校验
    serial->setFlowControl(QSerialPort::NoFlowControl);//设置流控制
    serial->setStopBits(QSerialPort::OneStop);//设置停止位
}

//打开串口
bool SerialDev::openSerialPort()
{
    qDebug()<<"串口名列表："<<getSerialPortName();
    if(namelist.isEmpty())
    {
        qDebug()<<"没有可用串口！";
        return false;
    }
    serial->setPortName(namelist.at(0));
    if(serial->open(QIODevice::ReadWrite))
    {
        qDebug()<<"打开串口成功！";
        return true;
    }else{
        qDebug()<<"打开串口失败！";
        return false;
    }
}

//获取串口名
QStringList SerialDev::getSerialPortName()
{
    foreach(const QSerialPortInfo& info,QSerialPortInfo::availablePorts())
    {
        namelist.append(info.portName());
    }
    return namelist;
}

SerialDev *SerialDev::getInstance()
{
    static SerialDev serialDev;

    return &serialDev;
}

//写数据
bool SerialDev::sendData(QByteArray data)
{
    if(!serial)
        return false;
    int len = serial->write(data);
    return len==-1 ? false:true;
}

//获取串口状态
bool SerialDev::serialState()
{
    if(!serial)
    {
        return false;
    }
    return serial->isOpen();
}

//读取串口数据
void SerialDev::readSlot()
{
    if(!serial)
        return ;
    QByteArray data;
    if(serial->bytesAvailable())
    {
        data.append(serial->readAll());
    }
    emit receiveData(data);//将数据片段转发给协议处理
    qDebug()<<"接收到的数据："<<data.toHex();

}
