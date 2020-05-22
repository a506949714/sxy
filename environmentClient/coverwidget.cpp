#include "coverwidget.h"

coverWidget::coverWidget(QWidget *parent) : QWidget(parent)
{
    image=new QImage;//构造图片加载器
    image->load(":/icons/u1.jpg");
    welcomelabel=new QLabel(this);
    welcomelabel->setGeometry(50,80,780,80);
    welcomelabel->setText("  Welcome to Environment Monitoring System");
    welcomelabel->setStyleSheet("font:微软雅黑;"
                                "font-size:35px;"
                                "color:white;"
                                "font-style:italic;"
                                "font-weight:bold;");
    chanslatelabel=new QLabel(this);
    chanslatelabel->setGeometry(50,350,780,400);
    chanslatelabel->setText("功能简介\n\n    ❶环境检测功能\n\n    ❷火警检测功能\n\n    ❸灯光控制功能\n\n");
    chanslatelabel->setStyleSheet("font:微软雅黑;"
                                  "font-size:25px;"
                                  "font-style:italic;"
                                  "font-weight:bold;");
    v=new QVBoxLayout;
    v->setMargin(0);
    v->setSpacing(0);
    v->addStretch();
    v->addWidget(welcomelabel);
    v->addStretch();
    v->addSpacing(50);
    v->addStretch();
    v->addWidget(chanslatelabel);
    v->addStretch();
    this->setLayout(v);
}

void coverWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QRect   tar(0,0,this->width(),this->height());//指定绘制的具体区域（矩形）
    QRect   src(0,0,image->width(),image->height());//指定所绘图片的区域
    p.drawImage(tar,*image,src);
}

