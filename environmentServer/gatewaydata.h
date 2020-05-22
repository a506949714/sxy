#ifndef GATEWAYDATA_H
#define GATEWAYDATA_H

typedef struct
{
    int lightLED[4];//4路高亮LED
    int lightRGB[3];//炫彩LED的RGB
    int infrared1;  //人体红外1
    double temp1;   //温度1
    double hum1;    //湿度1
    double co2; //二氧化碳
    double light;   //光照强度
    double ult; //紫外线强度
    int smoke;  //烟雾
    int ch4;    //可燃气体
    int fire;   //火光
    int infrared2;  //人体红外2
    double pm25;    //PM2.5
    double temp2;   //温度2
    double hum2;    //湿度2
    int warnLight;  //报警灯
    int warnRing;   //报警器
    int faceSwitch; //对射传感器
    int reflexSwitch;   //反射传感器
    int steer;  //舵机
    int fan;    //风扇
    int stepperdir;//步进电机方向
    int stepperen;//步进电机位置
    int relay1;  //继电器
    int relay2;  //继电器
    int lock;   //电磁锁
}GatewayData;


#endif // GATEWAYDATA_H
