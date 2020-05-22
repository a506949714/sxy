#include "clientserver.h"
#include <QDebug>

ClientServer::ClientServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer;
    server->listen(QHostAddress::AnyIPv4,10000);
    server->setMaxPendingConnections(80);
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnectSlot()));
}

ClientServer *ClientServer::getClientServer()
{
    static ClientServer server;
    return &server;
}
//解析函数
void ClientServer::translateData(QTcpSocket *socket, const QByteArray &data)
{
    //数据转换
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject json = jsonDoc.object();
    qDebug()<<"客户端数据："<<json.value("type").toString();
    QString type = json.value("type").toString();
    //根据type判断数据身份然后进行相应的操作
    //若干个分支语句
    if(type == "requestData")
    {
        qDebug()<<"客户端数据："<<json.value("requestType").toString();
        QString requestType = json.value("requestType").toString();
        if(requestType == "environment")
        {
            //所有的环境数据
            QString boxID = json.value("boxID").toString();
            if(boxID.isEmpty()|| !boxHash.contains(boxID))
            {
                qDebug()<<"盒子ID错误";
                return ;
            }
            QByteArray temp = ClientPotocol::packEnvironmentData(boxHash.value(boxID));
            socket->write(temp);
            qDebug()<<"已发送环境数据";
        }else if(requestType == "warning")
        {
            //需要所有的火警信息
            QString boxID = json.value("boxID").toString();
            if(boxID!="666666")
            {
                qDebug()<<"盒子ID错误";
                return ;
            }
            QByteArray temp = ClientPotocol::packWarningData(boxHash.value(boxID));
            socket->write(temp);
            qDebug()<<"已发火警境数据";
        }
    }
}

void ClientServer::receiveGateData(QString boxID, const QJsonObject &json)
{
    //1.首先判断有没有对应的 结构体
    if(boxHash.contains(boxID))
    {
        GatewayData* gate = boxHash.value(boxID);
        boxHash.insert(boxID,gate);
        int node = json.value("node").toInt();
        switch(node)
        {
        case 1:{
            QJsonArray array = json.value("led").toArray();
            for(int i=0;i<array.size();i++)
            {
                gate->lightLED[i] = array[i].toInt();
            }
            QJsonArray array1 = json.value("rgb").toArray();
            for(int i=0;i<array1.size();i++)
            {
                gate->lightRGB[i]=array1[i].toInt();
            }
            gate->infrared1 = json.value("bodyred").toInt();
        }
            break;
        case 2:
            gate->temp1 = json.value("temp").toDouble();
            gate->hum1 = json.value("hum").toDouble();
            gate->co2 = json.value("co2").toDouble();
            gate->light = json.value("light").toDouble();
            gate->ult = json.value("ult").toDouble();
            break;
        case 3:
            gate->smoke = json.value("smoke").toDouble();
            gate->ch4 = json.value("CH4").toDouble();
            gate->fire = json.value("fire").toDouble();
            gate->infrared2 = json.value("bodyred").toDouble();
            break;
        case 4:
            gate->pm25 = json.value("PM2.5").toDouble();
            gate->temp2 = json.value("temp").toDouble();
            gate->hum2 = json.value("hum").toDouble();
            break;
        case 5:
            gate->warnLight = json.value("alarmlamp").toDouble();
            gate->warnRing = json.value("alarm").toDouble();
            gate->faceSwitch = json.value("countshooting").toDouble();
            gate->reflexSwitch = json.value("reflect").toDouble();
            break;
        case 6:
            gate->steer = json.value("steering").toDouble();
            break;
        case 7:
            gate->fan = json.value("fan").toDouble();
            gate->stepperdir = json.value("steeperdir").toDouble();
            gate->stepperen = json.value("steeperen").toDouble();
            gate->relay1 = json.value("relay1").toDouble();
            gate->relay2 = json.value("relay2").toDouble();
            break;
        case 8:
            gate->lock = json.value("lock").toDouble();
            break;
        }
    }else{
        GatewayData *gate = new GatewayData;
        boxHash.insert(boxID,gate);
        int node = json.value("node").toInt();
        switch (node)
        {
        case 1:     break;
        case 2:
            gate->temp1 = json.value("temp").toDouble();
            gate->hum1 = json.value("hum").toDouble();
            gate->co2 = json.value("co2").toDouble();
            gate->light = json.value("light").toDouble();
            gate->ult = json.value("ult").toDouble();break;
        }
    }
    //......
//        qDebug()<<"高亮LED第一行："<<boxHash.value(boxID)->lightLED[0];
//        qDebug()<<"高亮LED第二行："<<boxHash.value(boxID)->lightLED[1];
//        qDebug()<<"高亮LED第三行："<<boxHash.value(boxID)->lightLED[2];
//        qDebug()<<"高亮LED第四行："<<boxHash.value(boxID)->lightLED[3];
//        qDebug()<<"RGB Led灯 R:："<<boxHash.value(boxID)->lightRGB[0];
//        qDebug()<<"RGB Led灯 G:："<<boxHash.value(boxID)->lightRGB[1];
//        qDebug()<<"RGB Led灯 B:："<<boxHash.value(boxID)->lightRGB[2];
//        qDebug()<<"有没有人："<<boxHash.value(boxID)->infrared1;

        qDebug()<<"温度:"<<boxHash.value(boxID)->temp1;
        qDebug()<<"湿度:"<<boxHash.value(boxID)->hum1;
        qDebug()<<"二氧化碳:"<<boxHash.value(boxID)->co2;
        qDebug()<<"光照强度:"<<boxHash.value(boxID)->light;
        qDebug()<<"紫外线:"<<boxHash.value(boxID)->ult;

        qDebug()<<"有没有烟："<<boxHash.value(boxID)->smoke;
        qDebug()<<"甲烷浓度状态："<<boxHash.value(boxID)->ch4;
        qDebug()<<"有没有火光："<<boxHash.value(boxID)->fire;
        qDebug()<<"有没有人："<<boxHash.value(boxID)->infrared2;

        qDebug()<<"PM2.5浓度："<<boxHash.value(boxID)->pm25;
//        qDebug()<<"温度："<<boxHash.value(boxID)->temp2;
//        qDebug()<<"湿度："<<boxHash.value(boxID)->hum2;

//        qDebug()<<"报警灯："<<boxHash.value(boxID)->warnLight;
//        qDebug()<<"报警器："<<boxHash.value(boxID)->warnRing;
//        qDebug()<<"对射传感器："<<boxHash.value(boxID)->faceSwitch;
//        qDebug()<<"反射传感器："<<boxHash.value(boxID)->reflexSwitch;

//        qDebug()<<"舵机："<<boxHash.value(boxID)->steer;

//        qDebug()<<"风扇："<<boxHash.value(boxID)->fan;
//        qDebug()<<"步进电机方向："<<boxHash.value(boxID)->stepperdir;
//        qDebug()<<"步进电机距离："<<boxHash.value(boxID)->stepperen;
//        qDebug()<<"继电器1："<<boxHash.value(boxID)->relay1;
//        qDebug()<<"继电器2："<<boxHash.value(boxID)->relay2;

//        qDebug()<<"电磁锁："<<boxHash.value(boxID)->lock;
}

void ClientServer::newConnectSlot()
{
    QTcpSocket *socket = server->nextPendingConnection();
    qDebug()<<"客户端新连接:"<<socket->peerAddress().toString();
    connect(socket,SIGNAL(readyRead()),this,SLOT(readSlot()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnectSlot()));
}

void ClientServer::readSlot()
{
    QTcpSocket* socket = (QTcpSocket*)sender();
    QByteArray data;
    while(socket->bytesAvailable())
    {
        data.append(socket->readAll());
    }
    //数据分割
    while(!data.isEmpty())
    {
        QByteArray temp = data.mid(0,data.indexOf("}\n")+2);
        data.remove(0,temp.length());
        //调用解析函数
        translateData(socket,temp);
    }
}
//断开连接槽函数
void ClientServer::disconnectSlot()
{
    QTcpSocket *socket = (QTcpSocket*)sender();
    socket->disconnect();
    socket->deleteLater();
    
}
