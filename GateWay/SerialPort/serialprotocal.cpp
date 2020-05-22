#include "serialprotocal.h"
#include "Network/networkprotocal.h"
#include "Network/network.h"

SerialProtocal::SerialProtocal(QObject *parent) : QObject(parent),nodeID(0x02),deviceID(0x05)
{
    len = 0;
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerSlot()));
    timer->start(1000);
    connect(SerialDev::getInstance(),SIGNAL(receiveData(QByteArray)),this,SLOT(receiveDataSlot(QByteArray)));
    connect(this,SIGNAL(transmitData(quint8,quint8,QByteArray)),NetworkProtocal::getNetPro(),SLOT(receiveSerialProSlot(quint8,quint8,QByteArray)));
    connect(Network::getNet(),SIGNAL(sendSerialData(QJsonObject)),this,SLOT(receiveNetDataSlot(QJsonObject)));
}

//打包结构体变量
void SerialProtocal::packData(quint8 node, quint8 device)
{
    sendData.head[0] = 0XFE;
    sendData.head[1] = 0XFE;
    sendData.save = 0x00;
    sendData.addr[0] = 0XFF;
    sendData.addr[1] = 0XFF;
    sendData.length = 9;
    sendData.node = node;
    sendData.device = device;
    sendData.data = QByteArray();
    sendData.tail = 0xFF;
}

//将结构体变量转换为 QByteArray
QByteArray SerialProtocal::packDataToArray()
{
    QByteArray temp;
    temp.append((char*)sendData.head,2);
    temp.append((char*)&sendData.save,1);
    temp.append((char*)sendData.addr,2);
    temp.append((char*)&sendData.length,1);
    temp.append((char*)&sendData.node,1);
    temp.append((char*)&sendData.device,1);
    temp.append(sendData.data);
    temp.append((char*)&sendData.tail,1);

    return temp;
}
//填充 控制结构体变量
void SerialProtocal::packData2(quint8 node, quint8 device)
{
    sendData2.head[0] = 0XFE;
    sendData2.head[1] = 0XFE;
    sendData2.save = 0x00;
    sendData2.addr[0] = 0XFF;
    sendData2.addr[1] = 0XFF;
    sendData2.length = 9+data.length();
    sendData2.node = node;
    sendData2.device = device;
    sendData2.data = data;
    sendData2.tail = 0xFF;
}
//提取控制数据并转换数据格式
QByteArray SerialProtocal::packData2ToArray()
{
    QByteArray temp;
    temp.append((char*)sendData2.head,2);
    temp.append((char*)&sendData2.save,1);
    temp.append((char*)sendData2.addr,2);
    temp.append((char*)&sendData2.length,1);
    temp.append((char*)&sendData2.node,1);
    temp.append((char*)&sendData2.device,1);
    temp.append(sendData2.data);
    temp.append((char*)&sendData2.tail,1);
    return temp;
}

//将buffer中的数据存到结构体中
void SerialProtocal::handleData()
{
    receiveData.head[0] = buffer[0];
    receiveData.head[1] = buffer[1];
    receiveData.save    = buffer[2];
    receiveData.addr[0] = buffer[3];
    receiveData.addr[1] = buffer[4];
    receiveData.length  = buffer[5];
    receiveData.node    = buffer[6];
    receiveData.device  = buffer[7];
    for(int i=0;i<buffer[5]-9;++i)
    {
        receiveData.data[i] = buffer[8+i];
    }
    receiveData.tail    = buffer[buffer[5]-1];
    //..将receiveData转发给网络模块
    qDebug()<<"数据帧："<<receiveData.data.toHex();
    emit transmitData(receiveData.node,receiveData.device,receiveData.data);
}

//改变节点编号和设备编号
void SerialProtocal::changeID()
{
    if(nodeID == 0x01)
    {
        switch(deviceID)
        {
            case 0x03:
                deviceID++;
                break;
            case 0x04:
                deviceID = 0x01;
                nodeID++;
                break;
            default:
                deviceID = 0x03;
                break;
        }
    }
    else if(nodeID ==0x02)
    {
        if(deviceID == 0x05)
        {
            nodeID++;
            deviceID = 0x01;
        }
        else{
            deviceID = deviceID+1;
        }

    }
    else if(nodeID ==0x03){
        if(deviceID == 0x05)
        {
            nodeID++;
            deviceID = 0x01;
        }
        else{
            deviceID = deviceID+1;
        }
    }
    else if(nodeID ==0x04){
        if(deviceID == 0x03)
        {
            nodeID++;
            deviceID = 0x03;
        }
        else{
            deviceID = deviceID+1;
        }

    }
    else if(nodeID ==0x05){
        if(deviceID == 0x05)
        {
            nodeID++;
            deviceID = 0x02;
        }
        else{
            deviceID = deviceID+1;
        }
    }
    else if(nodeID ==0x06){
        nodeID++;
        deviceID = 0x04;

    }
    else if(nodeID ==0x07){
        nodeID++;
        deviceID = 0x02;
    }
    else if(nodeID ==0x08){
        nodeID = 0x01;
        deviceID = 0x03;
    }
}

void SerialProtocal::changeAllID()
{
    nodeID = (nodeID+1)%9;
    if(nodeID == 0x01)
    {
        deviceID = 0x04;
    }
    else if(nodeID == 0x02)
    {
        deviceID = 0x05;
    }
    else if(nodeID == 0x03)
    {
        deviceID = 0x05;
    }
    else if(nodeID == 0x04)
    {
        deviceID = 0x03;
    }
    else if(nodeID == 0x05)
    {
        deviceID = 0x05;
    }
    else if(nodeID == 0x06)
    {
        deviceID = 0x02;
    }
    else if(nodeID == 0x07)
    {
        deviceID = 0x04;
    }
    else if(nodeID == 0x08)
    {
        deviceID = 0x02;
    }
}
//环境监测、警报系统
void SerialProtocal::checkenvironment()
{
    nodeID = (nodeID+1)%5+2;
    if(nodeID == 0x02)
    {
        deviceID = 0x05;
    }
    else if(nodeID == 0x03)
    {
        deviceID = 0x05;
    }else if(nodeID == 0x04)
    {
        deviceID = 0x01;
    }
}

//请求数据槽函数
void SerialProtocal::timerSlot()
{
    //例子:2号节点板
    packData(nodeID,deviceID);
    checkenvironment();
    //发送函数
    if(!SerialDev::getInstance()->serialState())
    {
        SerialDev::getInstance()->openSerialPort();
    }
    SerialDev::getInstance()->sendData(packDataToArray());
}

//接受串口转发原始数据的片段 并进行拼凑
void SerialProtocal::receiveDataSlot(QByteArray data)
{
    for(int i=0;i<data.size();i++)
    {
        //处理帧头
        if((quint8)data[i]==0XEF&&len>0)
        {
            if(buffer[len-1]==0XEF)
            {
                buffer[0] = 0xEF;
                buffer[1] = 0xEF;
                len=2;
                continue;
            }
        }
        //处理帧尾
        if(len>5 && (quint8)data[i]==0xFF && len+1 == buffer[5])
        {
            buffer[len] = 0XFF;
            //处理完整的一帧 buffer
            handleData();
            len = 0;
            continue;
        }
        //普通数据和残缺帧头，但是残缺帧头会被两个if处理
        buffer[len++] = (quint8)data[i];
    }
}
//接收并解析网络模块转发来的控制数据
void SerialProtocal::receiveNetDataSlot(const QJsonObject &json)
{
    data.clear();//清空data
    QString  name=json.value("name").toString();
    if(name=="highlight")
    {
        //按照协议提取 高亮LED的控制数据
        QString row =json.value("row").toString();
        QString light=json.value("light").toString();
        quint8 mrow=(quint8)row.toInt();
        quint8 mlight=(quint8)light.toInt();
        //将具体数据填充到 data中
        this->data.append((char*)&mrow,1);
        this->data.append((char*)&mlight,1);
        //借助打包函数和发送函数，将指令发送给硬件设备
        packData2(0x01,0x01);
        SerialDev::getInstance()->sendData(packData2ToArray());
    }else if(name=="lightrgb")
    {
        QString g=json.value("g").toString();
        QString r=json.value("r").toString();
        QString b=json.value("b").toString();
        quint8 mg=(quint8)g.toInt();
        quint8 mr=(quint8)r.toInt();
        quint8 mb=(quint8)b.toInt();
        data.append((char*)&mg,1);
        data.append((char*)&mr,1);
        data.append((char*)&mb,1);
        packData2(0x01,0x02);
        qDebug()<<"...";
        SerialDev::getInstance()->sendData(packData2ToArray());
    }
    else if(name=="warninglight")
    {
        QString warninglight=json.value("warninglight").toString();
        quint8 mwarninglight=(quint8)warninglight.toInt();
        data.append((char*)&mwarninglight,1);
        packData2(0x05,0x01);
        SerialDev::getInstance()->sendData(packData2ToArray());
    }
    else if(name=="warningqi")
    {
        QString warningqi=json.value("warningqi").toString();
        quint8 mwarningqi=(quint8)warningqi.toInt();
        data.append((char*)&mwarningqi,1);
        packData2(0x05,0x02);
        SerialDev::getInstance()->sendData(packData2ToArray());
    }
    else if(name=="servo")
    {
        QString servo=json.value("servo").toString();
        quint8 mservo=(quint8)servo.toInt();
        data.append((char*)&mservo,1);
        packData2(0x06,0x01);
        SerialDev::getInstance()->sendData(packData2ToArray());
    }
    else if(name=="fan")
    {
        QString fan=json.value("fan").toString();
        quint8 mfan=(quint8)fan.toInt();
        data.append((char*)&mfan,1);
        packData2(0x07,0x01);
        SerialDev::getInstance()->sendData(packData2ToArray());
    }
    else if(name=="steeper")
    {
        QString steeperdir=json.value("steeperdir").toString();
        QString steeperlen=json.value("steeperlen").toString();
        quint8 msteeperdir=(quint8)steeperdir.toInt();
        quint16 msteeperlen=(quint16)steeperlen.toInt();
        quint8 asteeperlen[2];
        asteeperlen[0]=msteeperlen>>8;
        asteeperlen[1]=msteeperlen;
        data.append((char*)&msteeperdir,1);
        data.append((char*)asteeperlen,2);
        packData2(0x07,0x02);
        SerialDev::getInstance()->sendData(packData2ToArray());
    }
    else if(name=="relay")
    {
        QString relayid=json.value("relayid").toString();
        QString relayen=json.value("relayen").toString();
        quint8  mrelayid=(quint8)relayid.toInt();
        quint8  mrelayen=(quint8)relayen.toInt();
        data.append((char*)&mrelayid,1);
        data.append((char*)&mrelayen,1);
        packData2(0x07,0x03);
        SerialDev::getInstance()->sendData(packData2ToArray());
    }
    else if(name=="lock")
    {
        QString lock=json.value("lock").toString();
        quint8 mlock=(quint8)lock.toInt();
        data.append((char*)&mlock,1);
        packData2(0x08,0x01);
        SerialDev::getInstance()->sendData(packData2ToArray());
    }
}












