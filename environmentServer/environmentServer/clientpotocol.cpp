#include "clientpotocol.h"

ClientPotocol::ClientPotocol(QObject *parent) : QObject(parent)
{

}
//环境监测
QByteArray ClientPotocol::packEnvironmentData(GatewayData *gate)
{
    QJsonObject json;
    json.insert("type","environment-reply");
    json.insert("temp",gate->temp1);
    json.insert("hum",gate->hum1);
    json.insert("co2",gate->co2);
    json.insert("light",gate->light);
    json.insert("ult",gate->ult);
    json.insert("pm25",gate->pm25);
    QJsonDocument jsonDoc(json);
    return jsonDoc.toJson();
}
//环境警报
QByteArray ClientPotocol::packWarningData(GatewayData *gate)
{
    QJsonObject json;
    json.insert("type","warning-reply");
    json.insert("smoke",gate->smoke);
    json.insert("fire",gate->fire);
    json.insert("CH4",gate->ch4);
    json.insert("bodyred",gate->infrared2);
    QJsonDocument jsonDoc(json);
    return jsonDoc.toJson();
}
