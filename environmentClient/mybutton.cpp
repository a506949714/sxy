#include "mybutton.h"

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

//鼠标按下事件
void MyButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
      //凹陷效果
        this->setStyleSheet("QPushButton{font:微软雅黑;"
                            "font-size:25px;"
                            "color:black;"
                            "background:#d3d7d4;"
                            "border:0px;"
                            "border-top:1px solid white;}");
    }
}

void MyButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        //去除凹陷
        this->setStyleSheet("QPushButton{font:微软雅黑;"
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
        emit clicked();
    }
}

void MyButton::mouseMoveEvent(QMouseEvent *e)
{
  Q_UNUSED(e);
}
