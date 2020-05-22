#ifndef WARNING_H
#define WARNING_H
/*火警警告界面*/
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
#include"networkpotocol.h"

class warning : public QWidget
{
    Q_OBJECT
public:
    explicit warning(QWidget *parent = nullptr);
    void pictureCheck(double smoke,double fire,double CH4,double bodyred);
protected:
    void paintEvent(QPaintEvent*);
signals:

public slots:
    void receiveSlot(const QByteArray &data);
    void sendNeedWarningSlot();
    void warningLightSlot();
    void warningqiSlot();
    void servoSlot();
    void fanSlot();
    void relay1Slot();
    void relay2Slot();
private:
     QImage *image;
     QTimer *timer;
     QLabel *smokelabel;
     QLabel *smokepicture;
     QLabel *firelabel;
     QLabel *firepicture;
     QLabel *CH4label;
     QLabel *CH4picture;
     QLabel *bodyredlabel;
     QLabel *bodyredpicture;
     QHBoxLayout *h1;
     QHBoxLayout *h2;
     QVBoxLayout *v1;
     QPushButton *warningLight;
     QPushButton *warningqi;
     bool        warninglightValue;
     bool        warningqiValue;
     QPushButton *servoBtn;
     bool        servoValue;
     QPushButton *fanBtn;
     bool        fanValue;
     QPushButton *relay1Btn;
     bool        relay1Value;
     QPushButton *relay2Btn;
     bool        relay2Value;
};

#endif // WARNING_H
