#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H

#include <QWidget>
#include"network.h"
#include<QTimer>
#include<QJsonObject>
#include<QJsonDocument>
#include <QJsonArray>
#include"protocol.h"
#include<QPainter>//画家类
#include<QPaintEvent>//绘制事件
#include<QImage>//图片加载器
#include<QLabel>
#include<QPushButton>
#include <QHBoxLayout>  // 水平布局管理器类
#include <QVBoxLayout> //垂直布局管理器类
#include<QStackedWidget>
#include "colorlight.h"
#include "colorcoverwidget.h"

class lightControl : public QWidget
{
    Q_OBJECT
public:
    explicit lightControl(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
signals:

public slots:
    void lockSlot();
    void colorlightSlot();
    void monotorSlot();
private:
     QImage *image;
     QLabel *lock;
     QPushButton *lockBtn;
     QLabel *colorlight;
     QPushButton *colorlightBtn;
     bool  flag1;
     bool  flag2;
     QHBoxLayout *h1;
     QHBoxLayout *h2;
     QHBoxLayout *h3;
     QVBoxLayout *v1;
      QVBoxLayout *v2;
     QStackedWidget *stack;
     colorLight *widget1;
     colorCoverWidget *widget2;
     QSlider     *monotor;
     int         monotorValue;
     QLabel      *monotorLabel;
};

#endif // LIGHTCONTROL_H
