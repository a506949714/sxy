#include "networkprotocol.h"
#include "network.h"

NetworkProtocol::NetworkProtocol(QObject *parent) : QObject(parent)
{

}
//返回唯一对象的指针
NetworkProtocol *NetworkProtocol::getNetPro()
{
    static NetworkProtocol netPro;
    return &netPro;
}
//处理节点板2的数据
void NetworkProtocol::handleNode2Data(double temp, double hum, int co2, int light, int ult)
{
    qDebug()<<"温度:"<<temp;
    qDebug()<<"湿度:"<<hum;
    qDebug()<<"CO2:"<<co2;
    qDebug()<<"光照强度:"<<light;
    qDebug()<<"紫外线强度:"<<ult;
    QByteArray data=packData("sensorData",2,"temp",temp,"hum",hum,"co2",co2,"light",light,"ult",ult);
    //借助网络设备类发送
    if(!Network::getNet()->sendData(data))
    {
        qDebug()<<Network::getNet()->getTime()<<"网关上传数据失败!";
    }
}
//协议打包函数
QByteArray NetworkProtocol::packData(QString type, int node, QString key1, double value1, QString key2, double value2, QString key3, double value3, QString key4, double value4, QString key5, double value5)
{
    QJsonObject json;
    json.insert("type",type);
    json.insert("node",node);
    json.insert(key1,value1);
    json.insert(key2,value2);
    json.insert(key3,value3);
    json.insert(key4,value4);
    json.insert(key5,value5);
    QJsonDocument jsonDoc(json);//将json转换为jsonDoc
    return jsonDoc.toJson();//将jsonDoc转换为ByteArray
}

QByteArray NetworkProtocol::packArrayData(QString type, int node, QString key1, QJsonArray array1, QString key2, QJsonArray array2, QString key3, int value)
{
    QJsonObject json;
    json.insert("type",type);
    json.insert("node",node);
    json.insert(key1,array1);
    json.insert(key2,array2);
    json.insert(key3,value);
    QJsonDocument jsonDoc(json);
    return jsonDoc.toJson();
}

QByteArray NetworkProtocol::packBoxID(QString type, QString key, QString value)
{
    QJsonObject json;
    json.insert("type",type);
    json.insert(key,value);
    QJsonDocument jsonDoc(json);
    return jsonDoc.toJson();
}
//接收串口协议类转发来的数据
void NetworkProtocol::receiveSerialProSlot(quint8 node, quint8 device, QByteArray data)
{
    //1.接收到的是2号节点板的所有数据
    if(node==0x02&&device==0x05)
    {
        //1.提取数据
        int temp1=(quint8)data.at(0);
        int temp2=(quint8)data.at(1);
        double temp=temp1+(double)temp2/100.0;//因为底层封装,温度
        int hum1=(quint8)data.at(2);
        int hum2=(quint8)data.at(3);
        double hum=hum1+(double)hum2/100.0;//因为底层封装，湿度
        int co2=(quint8)data.at(4)*256+(quint8)data.at(5);//co2
        int light=(quint8)data.at(6)*256+(quint8)data.at(7);//光照
        int ult=(quint8)data.at(8)*256+(quint8)data.at(9);//紫外线强度
        handleNode2Data(temp,hum,co2,light,ult);
    }
}









