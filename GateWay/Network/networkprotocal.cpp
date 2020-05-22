#include "networkprotocal.h"
#include <QDebug>
#include "network.h"


NetworkProtocal::NetworkProtocal(QObject *parent) : QObject(parent)
{

}

//返回唯一对象的指针
NetworkProtocal *NetworkProtocal::getNetPro()
{
    static NetworkProtocal netPro;
    return &netPro;
}
//处理节点板1的数据 0x03
void NetworkProtocal::handleNode1Data3(int bodyred)
{
    qDebug()<<"有没有人："<<bodyred;
    QByteArray data = packData("sensorData",1,"bodyred",bodyred);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}
//处理节点板1的数据 0x04
void NetworkProtocal::handleNode1Data4(QJsonArray array1, QJsonArray array2, int bodyred)
{
    qDebug()<<"高亮LED第一行："<<array1.at(0).toInt();
    qDebug()<<"高亮LED第二行："<<array1.at(1).toInt();
    qDebug()<<"高亮LED第三行："<<array1.at(2).toInt();
    qDebug()<<"高亮LED第四行："<<array1.at(3).toInt();
    qDebug()<<"RGB Led灯 R:："<<array2.at(0).toInt();
    qDebug()<<"RGB Led灯 G:："<<array2.at(1).toInt();
    qDebug()<<"RGB Led灯 B:："<<array2.at(2).toInt();
    qDebug()<<"有没有人："<<bodyred;
    QByteArray data = packArrayData("sensorData",1,"led",array1,"rgb",array2,"bodyred",bodyred);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}

//处理节点板2的数据 0x05
void NetworkProtocal::handleNode2Data(double temp, double hum, int co2, double light, int ult)
{
    qDebug()<<"温度："<<temp;
    qDebug()<<"湿度："<<hum;
    qDebug()<<"二氧化碳："<<co2;
    qDebug()<<"光照强度："<<light;
    qDebug()<<"紫外线强度："<<ult;
    QByteArray data = packData("sensorData",2,"temp",temp,"hum",hum,"co2",co2,"light",light,"ult",ult);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}

//节点板2 0x01
void NetworkProtocal::handleNode2Data1(double temp, double hum)
{
    qDebug()<<"温度："<<temp;
    qDebug()<<"湿度："<<hum;
    QByteArray data = packData("sensorData",2,"temp",temp,"hum",hum);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}
//节点板2 0x02
void NetworkProtocal::handleNode2Data2(int co2)
{
    qDebug()<<"二氧化碳："<<co2;
    QByteArray data = packData("sensorData",2,"co2",co2);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}
//节点板2 0x03
void NetworkProtocal::handleNode2Data3(double light)
{
    qDebug()<<"光照强度："<<light;
    QByteArray data = packData("sensorData",2,"light",light);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}
//节点板2 0x04
void NetworkProtocal::handleNode2Data4(int ult)
{
    qDebug()<<"紫外线强度："<<ult;
    QByteArray data = packData("sensorData",2,"ult",ult);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}
//节点板3 0x01
void NetworkProtocal::handleNode3Data1(int smoke)
{
    qDebug()<<"有没有烟："<<smoke;
    QByteArray data = packData("sensorData",3,"smoke",smoke);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}

void NetworkProtocal::handleNode3Data2(int CH4)
{
    qDebug()<<"甲烷浓度状态："<<CH4;
    QByteArray data = packData("sensorData",3,"CH4",CH4);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}

void NetworkProtocal::handleNode3Data3(int fire)
{
    qDebug()<<"有没有火光："<<fire;
    QByteArray data = packData("sensorData",3,"fire",fire);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}

void NetworkProtocal::handleNode3Data4(int bodyred)
{
    qDebug()<<"有没有人："<<bodyred;
    QByteArray data = packData("sensorData",3,"bodyred",bodyred);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}

void NetworkProtocal::handleNode3Data5(int smoke, int CH4, int fire, int bodyred)
{
    qDebug()<<"有没有烟："<<smoke;
    qDebug()<<"甲烷浓度状态："<<CH4;
    qDebug()<<"有没有火光："<<fire;
    qDebug()<<"有没有人："<<bodyred;
    QByteArray data = packData("sensorData",3,"smoke",smoke,"CH4",CH4,"fire",fire,"bodyred",bodyred);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}
//4号节点板 0x01
void NetworkProtocal::handleNode4Data1(double PM2_5)
{
    qDebug()<<"PM2.5浓度："<<PM2_5;
    QByteArray data = packData("sensorData",4,"PM2.5",PM2_5);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}
//4号节点板 0x02
void NetworkProtocal::handleNode4Data2(double temp, double hum)
{
    qDebug()<<"温度："<<temp;
    qDebug()<<"湿度："<<hum;
    QByteArray data = packData("sensorData",4,"temp",temp,"hum",hum);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}
//4号节点板 0x03
void NetworkProtocal::handleNode4Data3(double PM2_5, double temp, double hum)
{
    qDebug()<<"PM2.5浓度："<<PM2_5;
    qDebug()<<"温度："<<temp;
    qDebug()<<"湿度："<<hum;
    QByteArray data = packData("sensorData",4,"PM2.5",PM2_5,"temp",temp,"hum",hum);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}
//5号节点板 0x03
void NetworkProtocal::handleNode5Data3(int countshooting)
{
    qDebug()<<"对射传感器："<<countshooting;
    QByteArray data = packData("sensorData",5,"countshooting",countshooting);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }

}
//5号节点板 0x04
void NetworkProtocal::handleNode5Data4(int reflect)
{
     qDebug()<<"反射传感器："<<reflect;
     QByteArray data = packData("sensorData",5,"reflect",reflect);
     //借助网络设备类发送
     if(!Network::getNet()->sendData(data))
     {
         qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
     }
}
//5号节点板 0x05
void NetworkProtocal::handleNode5Data5(int alarmlamp, int alarm, int countshooting, int reflect)
{
     qDebug()<<"报警灯："<<alarmlamp;
     qDebug()<<"报警器："<<alarm;
     qDebug()<<"对射传感器："<<countshooting;
     qDebug()<<"反射传感器："<<reflect;
     QByteArray data = packData("sensorData",5,"alarmlamp",alarmlamp,"alarm",alarm,"countshooting",countshooting,"reflect",reflect);
     //借助网络设备类发送
     if(!Network::getNet()->sendData(data))
     {
         qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
     }
}
//6号节点板 0x02
void NetworkProtocal::handleNode6Data2(int steering)
{
    qDebug()<<"舵机："<<steering;
    QByteArray data = packData("sensorData",6,"steering",steering);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}
//7号节点板 0x04
void NetworkProtocal::handleNode7Data4(int fan, int steeperdir, int steeperen, int relay1, int relay2)
{
    qDebug()<<"风扇："<<fan;
    qDebug()<<"步进电机方向："<<steeperdir;
    qDebug()<<"步进电机距离："<<steeperen;
    qDebug()<<"继电器1："<<relay1;
    qDebug()<<"继电器2："<<relay2;
    QByteArray data = packData("sensorData",7,"fan",fan,"steeperdir",steeperdir,"steeperen",steeperen,"relay1",relay1,"relay2",relay2);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}

//8号节点板 0x02
void NetworkProtocal::handleNode8Data2(int lock)
{
    qDebug()<<"电磁锁："<<lock;
    QByteArray data = packData("sensorData",8,"lock",lock);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败！";
    }
}
//协议打包函数
QByteArray NetworkProtocal::packData(QString type, int node, QString key1, double value1, QString key2, double value2, QString key3, double value3, QString key4, double value4, QString key5, double value5)
{
    QJsonObject json;
    json.insert("type",type);
    json.insert("node",node);
    json.insert(key1,value1);
    json.insert(key2,value2);
    json.insert(key3,value3);
    json.insert(key4,value4);
    json.insert(key5,value5);
//    json.insert(key6,value6);
//    json.insert(key7,value7);
//    json.insert(key8,value8);
    QJsonDocument jsonDoc(json);//将json转化为jsonDoc
    return jsonDoc.toJson();//将jsonDoc转化为ByteArray
}
//协议打包数组
QByteArray NetworkProtocal::packArrayData(QString type, int node, QString key1, QJsonArray array1, QString key2, QJsonArray array2, QString key3, int value)
{
    QJsonObject json;
    json.insert("type",type);
    json.insert("node",node);
    json.insert(key1,array1);
    json.insert(key2,array2);
    json.insert(key3,value);
    QJsonDocument jsonDoc(json);//将json转化为jsonDoc
    return jsonDoc.toJson();//将jsonDoc转化为ByteArray
}
//打包箱子编号
QByteArray NetworkProtocal::packBoxID(QString type, QString key, QString value)
{
    QJsonObject json;
    json.insert("type",type);
    json.insert(key,value);
    QJsonDocument jsonDoc(json);//将json转化为jsonDoc
    return jsonDoc.toJson();//将jsonDoc转化为ByteArray
}

//接收串口协议类转发来的数据
void NetworkProtocal::receiveSerialProSlot(quint8 node,quint8 device,QByteArray data)
{
    //1.接收到的数据是2号节点板
    if(node==0x02)
    {
        //所有数据
        if(device==0x05)
        {
            //1.提取数据
            int temp1 = (quint8)data.at(0);
            int temp2 = (quint8)data.at(1);
            double temp = temp1+(double)temp2/100.0;//温度  因为底层封装
            int hum1 = (quint8)data.at(2);
            int hum2 = (quint8)data.at(3);
            double hum = hum1+(double)hum2/100;//湿度
            int co2 = (quint8)data.at(4)*256+(quint8)data.at(5);//二氧化碳
            double light = (quint8)data.at(6)*256+(double)data.at(7);//光照强度
            light = light/0.6;//硬件数据不是真实数据
            int ult = (quint8)data.at(8)*256+(quint8)data.at(9);//紫外线强度
            handleNode2Data(temp,hum,co2,light,ult);
        }
        else if(device==0x01)
        {
            int temp1 = (quint8)data.at(0);
            int temp2 = (quint8)data.at(1);
            double temp = temp1+(double)temp2/100.0;//温度  因为底层封装
            int hum1 = (quint8)data.at(2);
            int hum2 = (quint8)data.at(3);
            double hum = hum1+(double)hum2/100;//湿度
            handleNode2Data1(temp,hum);
        }
        else if(device==0x02)
        {
            int co2 = (quint8)data.at(0)*256+(quint8)data.at(1);//二氧化碳
            handleNode2Data2(co2);
        }
        else if(device==0x03)
        {
            double light = (quint8)data.at(0)*256+(double)data.at(1);//光照强度
            light = light/0.6;//硬件数据不是真实数据
            handleNode2Data3(light);
        }
        else if(device==0x04)
        {
            int ult = (quint8)data.at(0)*256+(quint8)data.at(1);//紫外线强度
            handleNode2Data4(ult);
        }
    }
    //2.接收到的数据是1号节点板
    else if(node == 0x01)
    {
        //人体红外
        if(device == 0x03)
        {
            int bodyred = (quint8)data.at(0);
            handleNode1Data3(bodyred);
        }
        //所有数据
        else if(device == 0x04)
        {
            int line1 = (quint8)data.at(0);
            int line2 = (quint8)data.at(1);
            int line3 = (quint8)data.at(2);
            int line4 = (quint8)data.at(3);
            int R = (quint8)data.at(4);
            int G = (quint8)data.at(5);
            int B = (quint8)data.at(6);
            int bodyred = (quint8)data.at(7);
            QJsonArray array1;
            array1.append(line1);
            array1.append(line2);
            array1.append(line3);
            array1.append(line4);
            QJsonArray array2;
            array2.append(R);
            array2.append(G);
            array2.append(B);
            handleNode1Data4(array1,array2,bodyred);
        }
    }
    //3.接收到的数据是3号节点板
    else if(node == 0x03)
    {
        //烟雾
        if(device == 0x01)
        {
            int smoke = (quint8)data.at(0);
            handleNode3Data1(smoke);
        }
        //甲烷
        else if(device == 0x02)
        {
            int CH4 = (quint8)data.at(0);
            handleNode3Data2(CH4);
        }
        //火光
        if(device == 0x03)
        {
            int fire = (quint8)data.at(0);
            handleNode3Data3(fire);
        }
        //人体红外
        else if(device == 0x04)
        {
            int bodyred = (quint8)data.at(0);
            handleNode3Data4(bodyred);
        }
        //所有数据
        else if(device == 0x05)
        {
            int smoke = (quint8)data.at(0);
            int CH4 = (quint8)data.at(1);
            int fire = (quint8)data.at(2);
            int bodyred = (quint8)data.at(3);
            handleNode3Data5(smoke,CH4,fire,bodyred);
        }
    }
    //4.接收到的数据是4号节点板
    else if(node == 0x04)
    {
        //PM2.5
        if(device == 0x01)
        {
            int temp1 = (quint8)data.at(0);
            double temp2 =(quint8)data.at(1) ;
            double PM2_5 = (temp1*256+temp2)/10;
            handleNode4Data1(PM2_5);
        }
        //温湿度
        else if(device == 0x02)
        {
            int temp1 = (quint8)data.at(0);
            int temp2 = (quint8)data.at(1);
            double temp = temp1+(double)temp2/100.0;//温度  因为底层封装
            int hum1 = (quint8)data.at(2);
            int hum2 = (quint8)data.at(3);
            double hum = hum1+(double)hum2/100;//湿度
            handleNode4Data2(temp,hum);

        }
        //所有数据
        else if(device == 0x03)
        {
            int tmp1 = (quint8)data.at(0);
            double tmp2 =(quint8)data.at(1) ;
            double PM2_5 = (tmp1*256+tmp2)/10;
            int temp1 = (quint8)data.at(2);
            int temp2 = (quint8)data.at(3);
            double temp = temp1+(double)temp2/100.0;//温度  因为底层封装
            int hum1 = (quint8)data.at(4);
            int hum2 = (quint8)data.at(5);
            double hum = hum1+(double)hum2/100;//湿度
            handleNode4Data3(PM2_5,temp,hum);
        }
    }
    //5.接收到的数据是5号节点板
    else if(node == 0x05)
    {
        //对射传感器
        if(device == 0x03)
        {
            int countshooting = (quint8)data.at(0);
            handleNode5Data3(countshooting);
        }
        //反射传感器
        else if(device == 0x04)
        {
            int reflect = (quint8)data.at(0);
            handleNode5Data4(reflect);
        }
        //所有数据
        else if(device == 0x05)
        {
            int alarmlamp = (quint8)data.at(0);
            int alarm = (quint8)data.at(1);
            int countshooting = (quint8)data.at(2);
            int reflect = (quint8)data.at(3);
            handleNode5Data5(alarmlamp,alarm,countshooting,reflect);
        }
    }
    //6.接收到的数据是6号节点板
    else if(node == 0x06)
    {
        //舵机
        if(device == 0x02)
        {
            int steering = (quint8)data.at(0);
            handleNode6Data2(steering);
        }
    }
    //7.接收到的数据是7号节点板
    else if(node == 0x07)
    {
        //所有数据
        if(device == 0x04)
        {
            int fan = (quint8)data.at(0);
            int steeperdir = (quint8)data.at(1);
            int steeperen = (quint8)data.at(2);
            int relay1 = (quint8)data.at(3);
            int relay2 = (quint8)data.at(4);
            handleNode7Data4(fan,steeperdir,steeperen,relay1,relay2);
        }
    }
    //8.接收到的数据是8号节点板
    else if(node == 0x08)
    {
        //所有数据
        if(device == 0x02)
        {
            int lock = (quint8)data.at(0);
            handleNode8Data2(lock);
        }
    }


}

