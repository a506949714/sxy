#ifndef COVERWIDGET_H
#define COVERWIDGET_H
/*子界面1*/
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
#include<QLabel>
#include <QVBoxLayout> //垂直布局管理器类
class coverWidget : public QWidget
{
    Q_OBJECT
public:
    explicit coverWidget(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent*);
signals:

public slots:
private:
    QImage *image;
    QTimer *timer;
    QLabel *welcomelabel;
    QLabel *chanslatelabel;
    QVBoxLayout *v;
};

#endif // COVERWIDGET_H
