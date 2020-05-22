#ifndef LOGIN_H
#define LOGIN_H
/*登录类*/
#include <QWidget>
#include "protocol.h"
#include <QPainter>
#include "network.h"
#include <QMessageBox>
#include "client.h"     //主页面
#include "register.h"   //注册页面

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    void on_LoginBtn_clicked();
    void receiveSlot(const QByteArray& data);
    void on_RegisterBtn_clicked();
    void showSelfSlot();

private:
    Ui::login *ui;
    Client  *window;
    Register *reg;
};

#endif // LOGIN_H
