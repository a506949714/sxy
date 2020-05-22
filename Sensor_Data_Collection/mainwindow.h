#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "db.h"
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QTableWidget>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void update_online();
private slots:
    void on_pbtn_start_clicked();
    void on_pbtn_stop_clicked();
    void new_client();
    void read_client_data();
    void client_dis();
    void displayOnlineClient();

private:
    Ui::MainWindow *ui;
    QList<QTcpSocket*> *socket_list;
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    Db *database;

    QString serverIP;
    int serverPort;

    QString getHostIpAddress();
    void init_tableWidget();
    void init_sensor_tableWidget(QTableWidget *);   
    void onBtnRefresh(QTableWidget *,QString,bool standard=true);
};

#endif // MAINWINDOW_H
