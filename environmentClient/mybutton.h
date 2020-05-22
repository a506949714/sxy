#ifndef MYBUTTON_H
#define MYBUTTON_H
/*自定义按钮类*/
#include <QObject>
#include<QPushButton>
#include<QMouseEvent>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent);
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
signals:
    void comingChange(QPoint *nextpoint);
public slots:
private:
};

#endif // MYBUTTON_H
