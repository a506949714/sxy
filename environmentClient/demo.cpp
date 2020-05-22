#include "demo.h"

Demo::Demo(QWidget *parent)
    : QWidget(parent),monotorValue(0)
{
    colorBtn=new QPushButton("炫彩LED",this);
    colorBtn->setGeometry(10,100,120,40);
    connect(colorBtn,SIGNAL(clicked(bool)),this,SLOT(colorBtnSlot()));
    hightL1=new QSlider(Qt::Horizontal,this);
    hightL1->setGeometry(10,10,255,10);
    hightL1->setFixedWidth(255);
    hightL1->setMaximum(255);//设置最大值
    connect(hightL1,SIGNAL(sliderReleased()),this,SLOT(highL1Slot()));
    hightL2=new QSlider(Qt::Horizontal,this);
    hightL2->setGeometry(10,30,255,10);
    hightL2->setRange(0,255);//设置滑块的取值范围
    connect(hightL2,SIGNAL(sliderReleased()),this,SLOT(highL2Slot()));
    hightL3=new QSlider(Qt::Horizontal,this);
    hightL3->setGeometry(10,50,255,10);
    hightL3->setFixedWidth(255);
    hightL3->setMaximum(255);//设置最大值
    connect(hightL3,SIGNAL(sliderReleased()),this,SLOT(highL3Slot()));
    hightL4=new QSlider(Qt::Horizontal,this);
    hightL4->setGeometry(10,70,255,10);
    hightL4->setFixedWidth(255);
    hightL4->setMaximum(255);//设置最大值
    connect(hightL4,SIGNAL(sliderReleased()),this,SLOT(highL4Slot()));
    monotor=new QSlider(Qt::Horizontal,this);
    monotor->setGeometry(10,170,200,35);
    monotor->setRange(0,380);
    connect(monotor,SIGNAL(sliderReleased()),this,SLOT(monotorSlot()));
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
    lockBtn=new QPushButton("电磁锁",this);
    lockBtn->setGeometry(10,520,120,40);
    lockValue=false;
    connect(lockBtn,SIGNAL(clicked(bool)),this,SLOT(lockSlot()));
    NetWork::getInstance();
}

Demo::~Demo()
{

}

void Demo::colorBtnSlot()
{
  //弹出颜色对话框
    QColor color=QColorDialog::getColor();
    QString g=QString::number(color.green());
    QString r=QString::number(color.red());
    QString b=QString::number(color.blue());
    QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","lightrgb","boxID","666666","g",g,"r",r,"b",b);
    NetWork::getInstance()->sendData(data);
}

void Demo::highL1Slot()
{
   QByteArray data;
   QString L1Value=QString::number(hightL1->value());
   if(L1Value==0)
      data=NetworkPotocol::packCtrlData("ctrldata","name","highlight","boxID","666666","row","1","light","0");
   else
      data=NetworkPotocol::packCtrlData("ctrldata","name","highlight","boxID","666666","row","1","light","255");
   NetWork::getInstance()->sendData(data);
   //this->update();
}
//控制第二路高亮LED
void Demo::highL2Slot()
{
    QString L2Value=QString::number(hightL2->value());
    QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","highlight","boxID","666666","row","2","light",L2Value);
    NetWork::getInstance()->sendData(data);
    //this->update();
}

void Demo::highL3Slot()
{
    QString L3Value=QString::number(hightL3->value());
    QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","highlight","boxID","666666","row","3","light",L3Value);
    NetWork::getInstance()->sendData(data);
    //this->update();
}

void Demo::highL4Slot()
{
    QString L4Value=QString::number(hightL4->value());
    QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","highlight","boxID","666666","row","4","light",L4Value);
    NetWork::getInstance()->sendData(data);
    //this->update();
}

void Demo::monotorSlot()
{
    QString dir,len;
    if(monotor->value()-monotorValue>0)
    {
        dir="1";
        len=QString::number(monotor->value()-monotorValue);
    }
    else
    {
        dir="0";
        len=QString::number(monotorValue-monotor->value());
    }
    monotorValue=monotor->value();
    QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","steeper","boxID","666666","steeperdir",dir,"steeperlen",len);
    NetWork::getInstance()->sendData(data);
}

void Demo::warningLightSlot()
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

void Demo::warningqiSlot()
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

void Demo::servoSlot()
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

void Demo::fanSlot()
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

void Demo::relay1Slot()
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

void Demo::relay2Slot()
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

void Demo::lockSlot()
{
    if(lockValue==false)
    {
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","lock","boxID","666666","lock","1");
        lockValue=true;
        NetWork::getInstance()->sendData(data);
    }
    else{
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","lock","boxID","666666","lock","0");
        lockValue=false;
        NetWork::getInstance()->sendData(data);
    }
}







