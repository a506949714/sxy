#ifndef DEMO_H
#define DEMO_H
/*界面示例*/
#include <QWidget>
#include "network.h"
#include "networkpotocol.h"
#include <QColorDialog>//颜色对话框
#include<QColor>//颜色
#include<QPushButton>
#include<Qslider>    //滑块类

class Demo : public QWidget
{
    Q_OBJECT

public:
    Demo(QWidget *parent = 0);
    ~Demo();
public slots:
    void colorBtnSlot();
    void highL1Slot();
    void highL2Slot();
    void highL3Slot();
    void highL4Slot();
    void monotorSlot();
    void warningLightSlot();
    void warningqiSlot();
    void servoSlot();
    void fanSlot();
    void relay1Slot();
    void relay2Slot();
    void lockSlot();
private:
    QPushButton *colorBtn;
    QSlider     *hightL1;
    QSlider     *hightL2;
    QSlider     *hightL3;
    QSlider     *hightL4;
    int         L1;
    int         L2;
    int         L3;
    int         L4;
    QSlider     *monotor;
    int         monotorValue;
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
    QPushButton *lockBtn;
    bool        lockValue;
};

#endif // DEMO_H
