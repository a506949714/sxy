#ifndef SERIALDEV_H
#define SERIALDEV_H
/*串口设备类*/
#include <QObject>
#include <QSerialPortInfo>  //串口信息类
#include <QSerialPort>      //串口驱动类
#include <QDebug>

class SerialDev : public QObject
{
    Q_OBJECT
public:
    void initSerialPort();  //初始化串口
    bool openSerialPort();  //打开串口
    QStringList getSerialPortName();    //获取串口名
    static SerialDev* getInstance();
    bool sendData(QByteArray data);     //写数据
    bool serialState();//获取串口状态

signals:
    void receiveData(QByteArray data);

public slots:
    void readSlot();

private:
    explicit SerialDev(QObject *parent = 0);
    QSerialPort *serial;
    QStringList namelist;//本机上拥有的串口名列表
    QString     name;//选取的串口名

};

#endif // SERIALDEV_H
