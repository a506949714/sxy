#include "warning.h"

warning::warning(QWidget *parent) : QWidget(parent)
{
    image=new QImage;//构造图片加载器
    image->load(":/icons/warning.jpg");
    timer=new QTimer;
    timer->start(2000);
    //烟雾
    smokelabel=new QLabel(this);
    smokelabel->setGeometry(100,100,60,60);
    smokelabel->setText("烟雾警告");
    smokelabel->setFixedSize(60,60);
    smokepicture=new QLabel(this);
    smokepicture->setGeometry(170,100,60,60);
    smokepicture->setStyleSheet("border-image:url(:/icons/newwarninglight.gif)");
    smokepicture->setFixedSize(60,60);
    //火光
    firelabel=new QLabel(this);
    firelabel->setGeometry(260,100,60,60);
    firelabel->setText("火光警告");
    firelabel->setFixedSize(60,60);
    firepicture=new QLabel(this);
    firepicture->setGeometry(320,100,60,60);
    firepicture->setStyleSheet("border-image:url(:/icons/newwarninglight.gif)");
    firepicture->setFixedSize(60,60);
    //甲烷
    CH4label=new QLabel(this);
    CH4label->setGeometry(410,100,60,60);
    CH4label->setText("甲烷警告");
    CH4label->setFixedSize(60,60);
    CH4picture=new QLabel(this);
    CH4picture->setGeometry(470,100,60,60);
    CH4picture->setStyleSheet("border-image:url(:/icons/newwarninglight.gif)");
    CH4picture->setFixedSize(60,60);
    // 人体红外
    bodyredlabel=new QLabel(this);
    bodyredlabel->setGeometry(560,100,60,60);
    bodyredlabel->setText("人体红外警告");
    bodyredlabel->setFixedSize(60,60);
    bodyredpicture=new QLabel(this);
    bodyredpicture->setGeometry(620,100,60,60);
    bodyredpicture->setStyleSheet("border-image:url(:/icons/newwarninglight.gif)");
    bodyredpicture->setFixedSize(60,60);
    warningLight=new QPushButton("警报灯",this);
    warningLight->setGeometry(10,220,120,40);
    warninglightValue=false;
    connect(warningLight,SIGNAL(clicked(bool)),this,SLOT(warningLightSlot()));
    warningqi=new QPushButton("警报器",this);
    warningqi->setGeometry(10,270,120,40);
    warningqiValue=false;
    connect(warningqi,SIGNAL(clicked(bool)),this,SLOT(warningqiSlot()));
    servoBtn=new QPushButton("舵机",this);
    servoBtn->setGeometry(10,320,120,40);
    servoValue=false;
    connect(servoBtn,SIGNAL(clicked(bool)),this,SLOT(servoSlot()));
    fanBtn=new QPushButton("风扇",this);
    fanBtn->setGeometry(10,370,120,40);
    fanValue=false;
    connect(fanBtn,SIGNAL(clicked(bool)),this,SLOT(fanSlot()));
    relay1Btn=new QPushButton("继电器1",this);
    relay1Btn->setGeometry(10,420,120,40);
    relay1Value=false;
    connect(relay1Btn,SIGNAL(clicked(bool)),this,SLOT(relay1Slot()));
    relay2Btn=new QPushButton("继电器2",this);
    relay2Btn->setGeometry(10,470,120,40);
    relay2Value=false;
    connect(relay2Btn,SIGNAL(clicked(bool)),this,SLOT(relay2Slot()));
    connect(NetWork::getInstance(),SIGNAL(receiveData(QByteArray)),this,SLOT(receiveSlot(QByteArray)));
    connect(timer,SIGNAL(timeout()),this,SLOT(sendNeedWarningSlot()));
    h1=new QHBoxLayout;
    h1->setMargin(0);
    h1->setSpacing(0);
    h1->addStretch();
    h1->addWidget(smokelabel);
    h1->addWidget(smokepicture);
    h1->addWidget(firelabel);
    h1->addWidget(firepicture);
    h1->addWidget(CH4label);
    h1->addWidget(CH4picture);
    h1->addWidget(bodyredlabel);
    h1->addWidget(bodyredpicture);
    h1->addStretch();
    h2=new QHBoxLayout;
    h2->setMargin(0);
    h2->setSpacing(0);
    h2->addStretch();
    h2->addWidget(warningLight);
    h2->addWidget(warningqi);
    h2->addWidget(servoBtn);
    h2->addWidget(fanBtn);
    h2->addWidget(relay1Btn);
    h2->addWidget(relay2Btn);
    h2->addStretch();
    v1=new QVBoxLayout;
    v1->setMargin(0);
    v1->setSpacing(0);
    v1->addStretch();
    v1->addLayout(h1);
    v1->addStretch();
    v1->addLayout(h2);
    v1->addStretch();
    this->setLayout(v1);
}

void warning::pictureCheck(double smoke, double fire, double CH4, double bodyred)
{
    if(smoke==0)
    {
        smokepicture->setStyleSheet("border-image:url(:/icons/newusedwarninglight.gif)");
    }
    else
    {
        smokepicture->setStyleSheet("border-image:url(:/icons/newwarninglight.gif)");
    }
    if(fire==0)
    {
        firepicture->setStyleSheet("border-image:url(:/icons/newusedwarninglight.gif)");
    }
    else
    {
        firepicture->setStyleSheet("border-image:url(:/icons/newwarninglight.gif)");
    }
    if(CH4==0)
    {
        CH4picture->setStyleSheet("border-image:url(:/icons/newusedwarninglight.gif)");
    }
    else
    {
        CH4picture->setStyleSheet("border-image:url(:/icons/newwarninglight.gif)");
    }
    if(bodyred==1.0)
    {
        bodyredpicture->setStyleSheet("border-image:url(:/icons/newusedwarninglight.gif)");
    }
    else
    {
        bodyredpicture->setStyleSheet("border-image:url(:/icons/newwarninglight.gif)");
    }
}

void warning::paintEvent(QPaintEvent *)
{
    //画背景
    QPainter p(this);
    QRect   tar(0,0,this->width(),this->height());//指定绘制的具体区域（矩形）
    QRect   src(0,0,image->width(),image->height());//指定所绘图片的区域
    p.drawImage(tar,*image,src);
}

void warning::receiveSlot(const QByteArray &data)
{
    QJsonDocument jsonDoc=QJsonDocument::fromJson(data);
    QJsonObject json=jsonDoc.object();
    QString type=json.value("type").toString();
    if(type=="warning-reply")
    {
        double smoke,CH4,fire,bodyred;
        smoke=json.value("smoke").toDouble();
        CH4=json.value("CH4").toDouble();
        fire=json.value("fire").toDouble();
        bodyred=json.value("bodyred").toDouble();
        pictureCheck(smoke,fire,CH4,bodyred);
    }
}

void warning::sendNeedWarningSlot()
{
    QByteArray data=Protocol::packData("requestData","warning","666666");
    bool ok=NetWork::getInstance()->sendData(data);//发送数据
    //
    if(!ok)
       return;
    timer->start(2000);
}

void warning::warningLightSlot()
{
    if(warninglightValue==false)
    {
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","warninglight","boxID","666666","warninglight","1");
        warninglightValue=true;
        NetWork::getInstance()->sendData(data);
    }
    else{
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","warninglight","boxID","666666","warninglight","0");
        warninglightValue=false;
        NetWork::getInstance()->sendData(data);
    }
}

void warning::warningqiSlot()
{
    if(warningqiValue==false)
    {
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","warningqi","boxID","666666","warningqi","1");
        warningqiValue=true;
        NetWork::getInstance()->sendData(data);
    }
    else{
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","warningqi","boxID","666666","warningqi","0");
        warningqiValue=false;
        NetWork::getInstance()->sendData(data);
    }
}

void warning::servoSlot()
{
    if(servoValue==false)
    {
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","servo","boxID","666666","servo","1");
        servoValue=true;
        NetWork::getInstance()->sendData(data);
    }
    else{
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","servo","boxID","666666","servo","0");
        servoValue=false;
        NetWork::getInstance()->sendData(data);
    }
}

void warning::fanSlot()
{
    if(fanValue==false)
    {
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","fan","boxID","666666","fan","1");
        fanValue=true;
        NetWork::getInstance()->sendData(data);
    }
    else{
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","fan","boxID","666666","fan","0");
        fanValue=false;
        NetWork::getInstance()->sendData(data);
    }
}

void warning::relay1Slot()
{
    if(relay1Value==false)
    {
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","relay","boxID","666666","relayid","1","relayen","1");
        relay1Value=true;
        NetWork::getInstance()->sendData(data);
    }
    else{
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","relay","boxID","666666","relayid","1","relayen","0");
        relay1Value=false;
        NetWork::getInstance()->sendData(data);
    }
}

void warning::relay2Slot()
{
    if(relay2Value==false)
    {
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","relay","boxID","666666","relayid","2","relayen","1");
        relay2Value=true;
        NetWork::getInstance()->sendData(data);
    }
    else{
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","relay","boxID","666666","relayid","2","relayen","0");
        relay2Value=false;
        NetWork::getInstance()->sendData(data);
    }
}
