#ifndef CLIENT_H
#define CLIENT_H
/*主界面*/
#include <QWidget>
#include "network.h"//自定义网络类
#include<QDateTime>
#include<QHash>
#include<QListWidgetItem>
#include "protocol.h"
#include<QPushButton>
#include<QCloseEvent>
#include<QPainter>//画家类
#include<QPaintEvent>//绘制事件
#include<QImage>//图片加载器
#include<QStackedWidget>
#include"environment.h"
#include"coverwidget.h"
#include"warning.h"
#include"lightcontrol.h"
#include <QLabel>   //标签
#include<QTimer> //日期时间
#include"mybutton.h"
#include <QHBoxLayout>  // 水平布局管理器类
#include <QVBoxLayout> //垂直布局管理器类
namespace Ui {
class client;
}

class client : public QWidget
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = 0);
    ~client();
signals:
private slots:
    void envirBtnClicked();
    void warnBtnClick();
    void lightControlBtnClick();
    void closeSlot();
    void backWelcomeBtnSlot();
    void timerSlot();
    void MaxandNormalChangeSlot();
protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    Ui::client *ui;
    QImage *image;
    QImage *image1;
    QPoint point;//点击点坐标和界面坐标的差值
    QPushButton *closeBtn;//关闭按钮
    QPushButton *hideBtn;//最小化按钮
    QPushButton *maxBtn;//最大化按钮
    MyButton *environmentBtn;//环境检测按钮
    MyButton *warningBtn;//火警检测按钮
    MyButton *lightControlBtn;//灯光控制按钮
    MyButton *backBtn;//返回欢迎界面按钮
    QStackedWidget *stack;
    environment *widget1;
    coverWidget *widget;
    warning     *widget2;
    lightControl *widget3;
    QLabel      *label;//显示时间
    QTimer      *timer;
    QLabel      *logolabel;
    QLabel      *logoTextlabel;
    QHBoxLayout *h1;
    QHBoxLayout *h2;
    QHBoxLayout *h3;
    QHBoxLayout *h4;
    QVBoxLayout *v1;
    QVBoxLayout *v2;
    QVBoxLayout *v3;
    bool flag;
};

#endif // CLIENT_H
