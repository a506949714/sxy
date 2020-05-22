#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
/*环境检测界面*/
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
#include"showdata.h"
#include <QHBoxLayout>  // 水平布局管理器类
#include <QVBoxLayout> //垂直布局管理器类
#include"chart.h"

class environment : public QWidget
{
    Q_OBJECT
public:
    explicit environment(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
signals:

public slots:
     void receiveSlot(const QByteArray &data);
     void sendNeedEnvironmentSlot();
     void sendEnvironmentTableSlot();
private:
     QImage *image;
     QTimer *timer;
     QTimer *timer2;
     ShowData *tempshow;
     ShowData *humshow;
     ShowData *lightshow;
     ShowData *pm25show;
     ShowData *co2show;
     ShowData *ultshow;
     QHBoxLayout *h1;
     QHBoxLayout *h2;
     QHBoxLayout *h3;
     QVBoxLayout *v1;
     Chart    *tempchart;
     Chart    *humchart;
};

#endif // ENVIRONMENT_H
