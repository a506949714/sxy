#include "client.h"
#include "ui_client.h"
#include<QDebug>

client::client(QWidget *parent) :
    QWidget(parent),flag(false),
    ui(new Ui::client)
{
    ui->setupUi(this);
    this->resize(1224,768);
    image=new QImage;//构造图片加载器
    image->load(":/icons/black.png");
    image1=new QImage;
    image1->load(":/icons/u2.jpg");
    //隐藏系统默认的标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //logo
    logolabel=new QLabel(this);
    logolabel->setGeometry(0,0,60,60);//设置位置和宽高
    logolabel->setFixedSize(60,60);
     //设置样式表
     logolabel->setStyleSheet("-moz-border-radius:50px;"
                              "border-image:url(:/icons/newlogo.gif);");
     logoTextlabel=new QLabel(this);
     logoTextlabel->setGeometry(70,30,200,60);
     logoTextlabel->setFixedSize(200,80);
     logoTextlabel->setText("环境检测系统");
     logoTextlabel->setStyleSheet("font-size:30px;"
                                  "color:white;"
                                  "font:楷体;"
                                  "text-decoration:none;");
    //显示时间
    label=new QLabel(this);
    label->setGeometry(50,420,290,60);
    label->setFont(QFont("幼圆",12,75));
    label->setFixedSize(290,60);
    label->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd  dddd  hh:mm:ss "));
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerSlot()));
    timer->start(1000);
    //环境检测按钮
    environmentBtn=new MyButton(this);
    environmentBtn->setGeometry(50,490,280,60);
    environmentBtn->setFixedSize(280,60);
    environmentBtn->setText("环境检测");
    environmentBtn->setStyleSheet("QPushButton{font:微软雅黑;"
                                  "font-size:30px;"
                                  "color:gray;"
                                  "border:0px;"
                                  "border-top:1px solid white;}"
                                  "QPushButton:hover{color:black;"
                                                   "font:微软雅黑;"
                                                   "font-size:35px;"
                                                   "border:0px;"
                                                   "border-top:1px solid white;"
                                                   "background:#eee;}");
    connect(environmentBtn,SIGNAL(clicked(bool)),this,SLOT(envirBtnClicked()));
    //火警检测按钮
    warningBtn=new MyButton(this);
    warningBtn->setGeometry(50,560,280,60);
    warningBtn->setFixedSize(280,60);
    warningBtn->setText("火警检测");
    warningBtn->setStyleSheet("QPushButton{font:微软雅黑;"
                              "font-size:30px;"
                              "color:gray;"
                              "border:0px;"
                              "border-top:1px solid white;}"
                              "QPushButton:hover{color:black;"
                                               "font:微软雅黑;"
                                               "font-size:35px;"
                                               "border:0px;"
                                               "border-top:1px solid white;"
                                               "background:#eee;}");
    connect(warningBtn,SIGNAL(clicked(bool)),this,SLOT(warnBtnClick()));
    //灯光控制按钮
    lightControlBtn=new MyButton(this);
    lightControlBtn->setGeometry(50,630,280,60);
    lightControlBtn->setFixedSize(280,60);
    lightControlBtn->setText("灯光控制");
    lightControlBtn->setStyleSheet("QPushButton{font:微软雅黑;"
                                   "font-size:30px;"
                                   "color:gray;"
                                   "border:0px;"
                                   "border-top:1px solid white;}"
                                   "QPushButton:hover{color:black;"
                                                    "font:微软雅黑;"
                                                    "font-size:35px;"
                                                    "border:0px;"
                                                    "border-top:1px solid white;"
                                                    "background:#eee;}");
    connect(lightControlBtn,SIGNAL(clicked(bool)),this,SLOT(lightControlBtnClick()));
    //返回欢迎界面按钮
    backBtn=new MyButton(this);
    backBtn->setGeometry(50,700,280,60);
    backBtn->setFixedSize(280,60);
    backBtn->setText("返回主页面");
    backBtn->setStyleSheet("QPushButton{font:微软雅黑;"
                           "font-size:30px;"
                           "color:gray;"
                           "border:0px;"
                           "border-top:1px solid white;}"
                           "QPushButton:hover{color:black;"
                                            "font:微软雅黑;"
                                            "font-size:35px;"
                                            "border:0px;"
                                            "border-top:1px solid white;"
                                            "background:#eee;}");
    connect(backBtn,SIGNAL(clicked(bool)),this,SLOT(backWelcomeBtnSlot()));
    //子界面
    stack=new QStackedWidget(this);
    stack->setGeometry(this->width()*0.3,30,this->width()-this->width()*0.285,this->height());
    widget=new coverWidget;
    widget1=new environment;
    widget2=new warning;
    widget3=new lightControl;
    stack->addWidget(widget);
    stack->addWidget(widget1);
    stack->addWidget(widget2);
    stack->addWidget(widget3);
    //关闭按钮
    closeBtn=new QPushButton(this);
    closeBtn->setIcon(QIcon(":/icons/quit.gif"));
    closeBtn->setIconSize(QSize(30,30));
    closeBtn->setFixedSize(30,30);
    closeBtn->setFlat(true);//按钮扁平化
    closeBtn->setGeometry(1195,0,30,30);//设置控件的位置和宽高
    connect(closeBtn,SIGNAL(clicked(bool)),this,SLOT(closeSlot()));
    //最小化
    hideBtn=new QPushButton(this);
    hideBtn->setIcon(QIcon(":/icons/h.gif"));
    hideBtn->setFlat(true);
    hideBtn->setIconSize(QSize(30,30));
    hideBtn->setFixedSize(30,30);
    hideBtn->setGeometry(1115,0,30,30);
    connect(hideBtn,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    //最大化
    maxBtn=new QPushButton(this);
    maxBtn->setIcon(QIcon(":/icons/fang.gif"));
    maxBtn->setFlat(true);
    maxBtn->setIconSize(QSize(30,30));
    maxBtn->setFixedSize(30,30);
    maxBtn->setGeometry(1155,0,30,30);
    connect(maxBtn,SIGNAL(clicked(bool)),this,SLOT(MaxandNormalChangeSlot()));
    h1=new QHBoxLayout;
    h1->addStretch();//弹簧效果
    h1->addWidget(hideBtn);//添加组件
    h1->addWidget(maxBtn);
    h1->addWidget(closeBtn);
    h3=new QHBoxLayout;
    h3->setMargin(0);
    h3->setSpacing(0);
    h3->addWidget(logolabel);
    h3->addWidget(logoTextlabel);
    v1=new QVBoxLayout;
    v1->setMargin(0);
    v1->setSpacing(0);
    v1->addSpacing(250);
    v1->addStretch();
    v1->addStretch();
    v1->addWidget(label);
    v1->addWidget(environmentBtn);
    v1->addWidget(warningBtn);
    v1->addWidget(lightControlBtn);
    v1->addWidget(backBtn);
    v1->addStretch();
    h4=new QHBoxLayout;
    h4->setMargin(0);
    h4->setSpacing(0);
    h4->addSpacing(55);
    h4->addLayout(v1);
    v3=new QVBoxLayout;
    v3->setMargin(0);
    v3->setSpacing(0);
    v3->addLayout(h3);
    v3->addLayout(h4);
    h2=new QHBoxLayout;
    h2->addLayout(v3);
    h2->addSpacing(6);
    h2->addWidget(stack);
    v2=new QVBoxLayout;
    v2->setSpacing(0);
    v2->addLayout(h1);
    v2->addLayout(h2);
    v2->setMargin(0);
    this->setLayout(v2);
}

client::~client()
{
    delete ui;
}

void client::envirBtnClicked()
{
    stack->setCurrentIndex(1);
}

void client::warnBtnClick()
{

    stack->setCurrentIndex(2);
}

void client::lightControlBtnClick()
{
    stack->setCurrentIndex(3);
}
void client::closeSlot()
{
    this->close();
}

void client::backWelcomeBtnSlot()
{
    stack->setCurrentIndex(0);
}

void client::timerSlot()
{
    label->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd dddd hh:mm:ss "));
}

void client::MaxandNormalChangeSlot()
{
    if(flag==false)
    {
        showMaximized();
        flag=true;
    }
    else
    {
        showNormal();
        flag=false;
    }
}
void client::paintEvent(QPaintEvent *)
{
    //画背景
    QPainter p(this);
    QRect   tar(0,0,this->width(),this->height());//指定绘制的具体区域（矩形）
    QRect   src(0,0,image->width(),image->height());//指定所绘图片的区域
    p.drawImage(tar,*image,src);
    QRect   tar1(0,30,350,this->height()+30);
    QRect   src1(0,30,image1->width(),image1->height());
    p.drawImage(tar1,*image1,src1);
    //划线
    QPen pen;
    pen.setWidth(20);
    pen.setColor(QColor("#ffffff"));
    p.setPen(pen);
    p.setPen(QColor("white"));
    p.drawLine(350,30,350,this->height());
}

void client::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        QPoint mousePoint =event->globalPos();
        QPoint windowPoint=this->pos();
        point=mousePoint-windowPoint;
    }

}

void client::mouseMoveEvent(QMouseEvent *event)
{

    QPoint windowPoint=event->globalPos()-point;
    this->move(windowPoint);
}


