#ifndef ONECHAT_H
#define ONECHAT_H
/*私聊类*/
#include <QWidget>
#include "network.h"
#include "protocol.h"
#include <QDateTime>


namespace Ui {
class OneChat;
}

class OneChat : public QWidget
{
    Q_OBJECT

public:
    explicit OneChat(QWidget *parent = 0);
    ~OneChat();
    void setWindowInfo(QString info);
    QString getTime();
    void setID(QString ID);
    void setWindowData(QString name,QString text,QString time);

private slots:
    void on_pushButton_clicked();

private:
    Ui::OneChat *ui;
    QString ID;
    QString Name;
};

#endif // ONECHAT_H
