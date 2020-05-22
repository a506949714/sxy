#include "environment.h"

environment::environment(QWidget *parent) : QWidget(parent)
{
    //this->resize(762,768);
    image=new QImage;//构造图片加载器
    image->load(":/icons/air.jpg");
    timer=new QTimer;
    timer->start(2000);
    timer2=new QTimer;
    timer2->start(6000);
    tempshow=new ShowData(this);
    tempshow->setGeometry(0,300,200,200);
    tempshow->setMaxAndMin(100,0);
    tempshow->setName("温度","℃");
    tempshow->setFixedSize(200,200);
    tempchart=new Chart(this);
    tempchart->initChart();
    tempchart->setGeometry(0,500,400,400);
    tempchart->setXYTitle("温度(%)","时间");
    tempchart->setYRange(0,100);
    tempchart->setXShowFormat(0);
    tempchart->setShowFlag();
    humshow=new ShowData(this);
    humshow->setGeometry(210,300,200,200);
    humshow->setMaxAndMin(100,0);
    humshow->setName("湿度","%");
    humshow->setFixedSize(200,200);
    humchart=new Chart(this);
    humchart->initChart();
    humchart->setGeometry(0,500,400,400);
    humchart->setXYTitle("湿度(%)","时间");
    humchart->setYRange(0,100);
    humchart->setXShowFormat(0);
    humchart->setShowFlag();
    lightshow=new ShowData(this);
    lightshow->setGeometry(0,50,200,200);
    lightshow->setMaxAndMin(30000,0);
    lightshow->setName("光照","LUX");
    lightshow->setFixedSize(200,200);
    co2show=new ShowData(this);
    co2show->setGeometry(210,50,200,200);
    co2show->setMaxAndMin(5000,0);
    co2show->setName("CO2浓度","");
    co2show->setFixedSize(200,200);
    ultshow=new ShowData(this);
    ultshow->setGeometry(420,50,200,200);
    ultshow->setMaxAndMin(15,0);
    ultshow->setName("紫外线","");
    ultshow->setFixedSize(200,200);
    pm25show=new ShowData(this);
    pm25show->setGeometry(630,50,200,200);
    pm25show->setMaxAndMin(500,0);
    pm25show->setName("PM2.5","");
    pm25show->setFixedSize(200,200);
    connect(NetWork::getInstance(),SIGNAL(receiveData(QByteArray)),this,SLOT(receiveSlot(QByteArray)));
    connect(timer,SIGNAL(timeout()),this,SLOT(sendNeedEnvironmentSlot()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(sendEnvironmentTableSlot()));
    h1=new QHBoxLayout;
    h1->setMargin(0);
    h1->setSpacing(0);
    h1->addWidget(lightshow);
    h1->addWidget(co2show);
    h1->addWidget(ultshow);
    h1->addWidget(pm25show);
    h2=new QHBoxLayout;
    h2->setMargin(0);
    h2->setSpacing(0);
    h2->addWidget(tempshow);
    h2->addWidget(humshow);
    h3=new QHBoxLayout;
    h3->setMargin(0);
    h3->setSpacing(0);
    h3->addWidget(tempchart);
    h3->addWidget(humchart);
    v1=new QVBoxLayout;
    v1->setMargin(0);
    v1->setSpacing(0);
    v1->addLayout(h1);
    v1->addLayout(h2);
    v1->addLayout(h3);
    this->setLayout(v1);
}

void environment::paintEvent(QPaintEvent *)
{
    //画背景
    QPainter p(this);
    QRect   tar(0,0,this->width(),this->height());//指定绘制的具体区域（矩形）
    QRect   src(0,0,image->width(),image->height());//指定所绘图片的区域
    p.drawImage(tar,*image,src);
}

void environment::receiveSlot(const QByteArray &data)
{
    QJsonDocument jsonDoc=QJsonDocument::fromJson(data);
    QJsonObject json=jsonDoc.object();
    QString type=json.value("type").toString();
    if(type=="environment-reply")
    {
        double temp,hum,co2,light,ult,pm25;
        temp=json.value("temp").toDouble();
        hum=json.value("hum").toDouble();
        co2=json.value("co2").toDouble();
        light=json.value("light").toDouble();
        ult=json.value("ult").toDouble();
        pm25=json.value("pm25").toDouble();
        tempshow->setData(temp);
        humshow->setData(hum);
        lightshow->setData(light);
        co2show->setData(co2);
        ultshow->setData(ult);
        pm25show->setData(pm25);
//        qDebug()<<"温度:"<<temp;
//        qDebug()<<"湿度:"<<hum;
//        qDebug()<<"CO2:"<<co2;
//        qDebug()<<"光照:"<<light;
//        qDebug()<<"PM2.5:"<<pm25;
    }
    if(type=="historyTemp")
    {
        QJsonObject newjson=json.value("data").toObject();
        tempchart->setShowData2(newjson);
    }
}

void environment::sendNeedEnvironmentSlot()
{
    QByteArray data=Protocol::packData("requestData","environment","666666");
    bool ok=NetWork::getInstance()->sendData(data);//发送数据
    //
    if(!ok)
       return;
    timer->start(2000);
}

void environment::sendEnvironmentTableSlot()
{
    QByteArray data=Protocol::packData2("historydata","Temp","1");
    bool ok=NetWork::getInstance()->sendData(data);//发送数据
    //
    if(!ok)
       return;
    timer->start(6000);
}











