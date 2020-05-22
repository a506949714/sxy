#include "colorlight.h"

colorLight::colorLight(QWidget *parent) : QWidget(parent)
{
    colorBtn=new QPushButton("炫彩LED",this);
    colorBtn->setGeometry(10,100,120,40);
    connect(colorBtn,SIGNAL(clicked(bool)),this,SLOT(colorBtnSlot()));
    highLightLabel=new QLabel(this);
    highLightLabel->setText("高亮LED");
    highLightLabel->setGeometry(10,0,80,20);
    hightL1=new QSlider(Qt::Horizontal,this);
    hightL1->setGeometry(10,20,255,10);
    hightL1->setFixedWidth(255);
    hightL1->setMaximum(255);//设置最大值
    connect(hightL1,SIGNAL(sliderReleased()),this,SLOT(highL1Slot()));
    hightL2=new QSlider(Qt::Horizontal,this);
    hightL2->setGeometry(10,40,255,10);
    hightL2->setRange(0,255);//设置滑块的取值范围
    connect(hightL2,SIGNAL(sliderReleased()),this,SLOT(highL2Slot()));
    hightL3=new QSlider(Qt::Horizontal,this);
    hightL3->setGeometry(10,60,255,10);
    hightL3->setFixedWidth(255);
    hightL3->setMaximum(255);//设置最大值
    connect(hightL3,SIGNAL(sliderReleased()),this,SLOT(highL3Slot()));
    hightL4=new QSlider(Qt::Horizontal,this);
    hightL4->setGeometry(10,80,255,10);
    hightL4->setFixedWidth(255);
    hightL4->setMaximum(255);//设置最大值
    connect(hightL4,SIGNAL(sliderReleased()),this,SLOT(highL4Slot()));
    NetWork::getInstance();
}

void colorLight::colorBtnSlot()
{
    //弹出颜色对话框
      QColor color=QColorDialog::getColor();
      QString g=QString::number(color.green());
      QString r=QString::number(color.red());
      QString b=QString::number(color.blue());
      QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","lightrgb","boxID","666666","g",g,"r",r,"b",b);
      NetWork::getInstance()->sendData(data);
}
void colorLight::highL1Slot()
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
void colorLight::highL2Slot()
{
    QString L2Value=QString::number(hightL2->value());
    QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","highlight","boxID","666666","row","2","light",L2Value);
    NetWork::getInstance()->sendData(data);
    //this->update();
}

void colorLight::highL3Slot()
{
    QString L3Value=QString::number(hightL3->value());
    QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","highlight","boxID","666666","row","3","light",L3Value);
    NetWork::getInstance()->sendData(data);
    //this->update();
}

void colorLight::highL4Slot()
{
    QString L4Value=QString::number(hightL4->value());
    QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","highlight","boxID","666666","row","4","light",L4Value);
    NetWork::getInstance()->sendData(data);
    //this->update();
}
