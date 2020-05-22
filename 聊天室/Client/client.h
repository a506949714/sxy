#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include "network.h"    //自定义网络类
#include "protocol.h"   //自定义协议类
#include <QDateTime>
#include <QJsonArray>
#include "onechat.h"
#include <QHash>
#include <QListWidgetItem>
#include <QSound>       //声音类

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();
    QString getTime();
    void showOneChatData(QString info,QString text,QString time);
    void changeInfoColor(QString info);

private slots:
    void on_pushButton_clicked();
    void receiveSlot(const QByteArray& data);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Client *ui;
   // QTcpSocket *socket;
    QHash<OneChat* ,QString> hash;
};

#endif // CLIENT_H
