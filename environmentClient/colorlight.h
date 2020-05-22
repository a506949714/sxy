#ifndef COLORLIGHT_H
#define COLORLIGHT_H

#include <QWidget>
#include<QLabel>
#include<QHBoxLayout>
#include <QVBoxLayout> //垂直布局管理器类
#include<QPushButton>
#include "network.h"
#include "networkpotocol.h"
#include <QColorDialog>//颜色对话框
#include<QColor>//颜色
#include<QSlider>

class colorLight : public QWidget
{
    Q_OBJECT
public:
    explicit colorLight(QWidget *parent = nullptr);

signals:

public slots:
    void colorBtnSlot();
    void highL1Slot();
    void highL2Slot();
    void highL3Slot();
    void highL4Slot();
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
   QLabel      *highLightLabel;
};

#endif // COLORLIGHT_H
