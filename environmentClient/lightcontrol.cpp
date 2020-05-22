#include "lightcontrol.h"

lightControl::lightControl(QWidget *parent) : QWidget(parent),flag1(false),flag2(false),monotorValue(0)
{
    image=new QImage;//构造图片加载器
    image->load(":/icons/light.jpg");
    lock=new QLabel(this);
    lock->setGeometry(200,30,50,50);
    lock->setText("电磁锁");
    lock->setFixedSize(50,50);
    lockBtn=new  QPushButton(this);
    lockBtn->setGeometry(260,30,80,50);
    lockBtn->setStyleSheet("border-image:url(:/icons/closebtn.png);"
                                "border:0px;");
    lockBtn->setFixedSize(80,50);
    connect(lockBtn,SIGNAL(clicked(bool)),this,SLOT(lockSlot()));
    colorlight=new QLabel(this);
    colorlight->setGeometry(500,30,50,50);
    colorlight->setText("灯光");
    colorlight->setFixedSize(50,50);
    colorlightBtn=new  QPushButton(this);
    colorlightBtn->setGeometry(560,30,80,50);
    colorlightBtn->setStyleSheet("border-image:url(:/icons/closebtn.png);"
                                 "border:0px;");
    colorlightBtn->setFixedSize(80,50);
    connect(colorlightBtn,SIGNAL(clicked(bool)),this,SLOT(colorlightSlot()));
    monotorLabel=new QLabel(this);
    monotorLabel->setText("步进电机");
    monotor=new QSlider(Qt::Horizontal,this);
    monotor->setGeometry(10,170,200,35);
    monotor->setFixedSize(200,35);
    monotor->setRange(0,380);
    connect(monotor,SIGNAL(sliderReleased()),this,SLOT(monotorSlot()));
    NetWork::getInstance();
    stack=new QStackedWidget(this);
    stack->setGeometry(500,90,200,200);
    stack->setFixedSize(200,200);
    widget1=new colorLight;
    widget2=new colorCoverWidget;
    stack->addWidget(widget2);
    stack->addWidget(widget1);
    h1=new QHBoxLayout;
    h1->setMargin(0);
    h1->setSpacing(0);
    h1->addWidget(colorlight);
    h1->addWidget(colorlightBtn);
    h2=new QHBoxLayout;
    h2->setMargin(0);
    h2->setSpacing(0);
    h2->addWidget(lock);
    h2->addWidget(lockBtn);
    v2=new QVBoxLayout;
    v2->setMargin(0);
    v2->setSpacing(0);
    v2->addLayout(h2);
    v2->addWidget(monotorLabel);
    v2->addWidget(monotor);
    v2->addStretch();
    v1=new QVBoxLayout;
    v1->setMargin(0);
    v1->setSpacing(0);
    v1->addLayout(h1);
    v1->addWidget(stack);
    v1->addStretch();
    h3=new QHBoxLayout;
    h3->setMargin(0);
    h3->setSpacing(0);
    h3->addStretch();
    h3->addLayout(v2);
    h3->addSpacing(240);
    h3->addLayout(v1);
    h3->addStretch();
    this->setLayout(h3);
}

void lightControl::paintEvent(QPaintEvent *)
{
    //画背景
    QPainter p(this);
    QRect   tar(0,0,this->width(),this->height());//指定绘制的具体区域（矩形）
    QRect   src(0,0,image->width(),image->height());//指定所绘图片的区域
    p.drawImage(tar,*image,src);
}

void lightControl::lockSlot()
{
    if(flag1==false)
    {
        lockBtn->setStyleSheet("border-image:url(:/icons/open.png)");
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","lock","boxID","666666","lock","1");
        NetWork::getInstance()->sendData(data);
        flag1=true;
    }
    else
    {
        lockBtn->setStyleSheet("border-image:url(:/icons/closebtn.png)");
        QByteArray data=NetworkPotocol::packCtrlData("ctrldata","name","lock","boxID","666666","lock","0");
        NetWork::getInstance()->sendData(data);
        flag1=false;
    }
}

void lightControl::colorlightSlot()
{
    if(flag2==false)
     {
        colorlightBtn->setStyleSheet("border-image:url(:/icons/open.png)");
        flag2=true;
        stack->setCurrentIndex(1);
     }
    else
    {
        colorlightBtn->setStyleSheet("border-image:url(:/icons/closebtn.png)");
        flag2=false;
        stack->setCurrentIndex(0);
    }
}

void lightControl::monotorSlot()
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



