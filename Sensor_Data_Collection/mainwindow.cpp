#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    database = new Db;
    database->connectdb();

    this->init_tableWidget();

    serverIP=getHostIpAddress();
    //创建一个存放socket的list容器：
    socket_list = new QList<QTcpSocket *>;

    ui->ld_ip->setText(serverIP);
    ui->ld_port->setText("6506");
    ui->ld_ip->setEnabled(false);
    ui->pbtn_stop->setEnabled(false);

    connect(this,SIGNAL(update_online()),this,SLOT(displayOnlineClient()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//刷新表格数据   默认standard=true表示正常顺序，standard=false表示逆序
void MainWindow::onBtnRefresh(QTableWidget *tablewidget,QString tablename,bool standard)
{
    tablewidget->clearContents();
    tablewidget->setRowCount(0);
    QSqlQuery query;
    int i = 0, j = 0, nColumn, nRow;
    QString sql;
    sql=QString("SELECT * FROM '%0'").arg(tablename);
    query.exec(sql);
    query.last();
    nRow = query.at() + 1;
    tablewidget->setRowCount(8);//nRow);
    nColumn = tablewidget->columnCount();
    if(standard)
    {

        query.first();
        while(j<nRow)
        {
            for (i = 0; i<nColumn; i++)
                tablewidget->setItem(j, i, new QTableWidgetItem(query.value(i).toString()));
            j++;
            query.next();
        }
    }
    else
    {
        while(j<nRow)
        {
            for (i = 0; i<nColumn; i++)
                tablewidget->setItem(j, i, new QTableWidgetItem(query.value(i).toString()));
            j++;
            query.previous();
        }
    }
}

void MainWindow::displayOnlineClient()
{
    qDebug()<<"当前Client端连接数："<<socket_list->size();
    ui->tw_online->clearContents();
    for(int i=0;i<socket_list->size();i++)
    {
        ui->tw_online->setItem(i,0,new QTableWidgetItem(socket_list->at(i)->peerAddress().toString().split(':').last()));
        qDebug()<<socket_list->at(i)->peerAddress().toString().split(':').last()+":"+QString::number(socket_list->at(i)->peerPort());
    }
}

QString MainWindow::getHostIpAddress()
{
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address())
        {
            strIpAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // 如果没有找到，则以本地IP地址为IP
    if (strIpAddress.isEmpty())
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
    return strIpAddress;
}

void MainWindow::init_tableWidget()
{
    QStringList online_header;
    online_header<<tr("IP地址");

    ui->tw_online->setRowCount(10);
    ui->tw_online->setColumnCount(1);
    ui->tw_online->setHorizontalHeaderLabels((online_header));
    ui->tw_online->setColumnWidth(0,150);
    init_sensor_tableWidget(ui->tw_CO2);
    onBtnRefresh(ui->tw_CO2,"CO2",false);
    init_sensor_tableWidget(ui->tw_PM2_5);
    onBtnRefresh(ui->tw_PM2_5,"PM2_5",false);
    init_sensor_tableWidget(ui->tw_body);
    onBtnRefresh(ui->tw_body,"body",false);
    init_sensor_tableWidget(ui->tw_flower);
    onBtnRefresh(ui->tw_flower,"flower",false);
    init_sensor_tableWidget(ui->tw_humidity);
    onBtnRefresh(ui->tw_humidity,"humidity",false);
    init_sensor_tableWidget(ui->tw_illumination);
    onBtnRefresh(ui->tw_illumination,"illumination",false);
    init_sensor_tableWidget(ui->tw_noise);
    onBtnRefresh(ui->tw_noise,"noise",false);
    init_sensor_tableWidget(ui->tw_smoke);
    onBtnRefresh(ui->tw_smoke,"smoke",false);
    init_sensor_tableWidget(ui->tw_temperature);
    onBtnRefresh(ui->tw_temperature,"temperature",false);
    init_sensor_tableWidget(ui->tw_tvoc);
    onBtnRefresh(ui->tw_tvoc,"tvoc",false);
    init_sensor_tableWidget(ui->tw_free_2);
    init_sensor_tableWidget(ui->tw_free_3);
}

void MainWindow::init_sensor_tableWidget(QTableWidget *tw)
{
    QStringList sensor_header;
    sensor_header<<tr("型号")<<tr("数据")<<tr("时间")<<tr("位置")<<tr("责任人");
    tw->setColumnCount(3);
    tw->setHorizontalHeaderLabels((sensor_header));
    tw->setColumnWidth(0,100);
    tw->setColumnWidth(1,100);
    tw->setColumnWidth(2,200);
}

void MainWindow::new_client()
{
    tcpSocket = tcpServer->nextPendingConnection();//与客户端通信的套接字
    socket_list->append(tcpSocket);
    qDebug()<<tcpSocket->peerAddress().toString().split(':').last()+":"+QString::number(tcpSocket->peerPort())<<" connect";
    connect(socket_list->last(),SIGNAL(readyRead()),this,SLOT(read_client_data()));
    connect(socket_list->last(),SIGNAL(disconnected()),this,SLOT(client_dis()));
    emit update_online();
}

void MainWindow::client_dis()
{
    QTcpSocket *obj = (QTcpSocket*)sender();
    qDebug()<<obj->peerAddress().toString().split(':').last()+":"+QString::number(obj->peerPort())<<" disconnect";
    socket_list->removeOne(obj);
    emit update_online();
}

void MainWindow::read_client_data()
{
    QTcpSocket *obj = (QTcpSocket*)sender();
    QString msg = obj->readAll();
    QString dataType=msg.split(':').value(1);
    QString sql;
    QSqlQuery query;
    bool ok;
    QDateTime time1 = QDateTime::currentDateTime();//获取系统现在的时间
    QString time=time1.toString("yyyy-MM-dd hh:mm:ss");
    QString temp,hum,lig,tvoc,co2;
    temp=msg.split(':').value(2);
    hum=msg.split(':').value(5);
    lig=msg.split(':').value(8);
    tvoc=msg.split(':').value(11);
    co2=msg.split(':').value(14);

    qDebug()<<"收到来自："<<obj->peerAddress().toString().split(':').last()+":"+QString::number(obj->peerPort())<<"的"<<dataType<<"数据："<<msg;
    sql=QString("INSERT INTO temperature VALUES('DS18B20','%0','%1')").arg(temp).arg(time);
    ok=query.exec(sql);
    qDebug()<<sql<<ok;
    sql=QString("INSERT INTO humidity VALUES('DHT11','%0','%1')").arg(hum).arg(time);
    ok=query.exec(sql);
    qDebug()<<sql<<ok;
    sql=QString("INSERT INTO illumination VALUES('光敏电阻','%0','%1')").arg(lig).arg(time);
    ok=query.exec(sql);
    qDebug()<<sql<<ok;
//    sql=QString("INSERT INTO PM2_5 VALUES('0003','%0','%1')").arg(msg.split(':').value(2)+"mg/m³").arg(time);
//    ok=query.exec(sql);
    sql=QString("INSERT INTO tvoc VALUES('SGP30','%0','%1')").arg(tvoc).arg(time);
    ok=query.exec(sql);
    qDebug()<<sql<<ok;
    sql=QString("INSERT INTO CO2 VALUES('SGP30','%0','%1')").arg(co2).arg(time);
    ok=query.exec(sql);
    qDebug()<<sql<<ok;
    onBtnRefresh(ui->tw_temperature,"temperature",false);
    onBtnRefresh(ui->tw_humidity,"humidity",false);
    onBtnRefresh(ui->tw_tvoc,"tvoc",false);
    onBtnRefresh(ui->tw_CO2,"CO2",false);
    onBtnRefresh(ui->tw_illumination,"illumination",false);
    onBtnRefresh(ui->tw_PM2_5,"PM2_5",false);
    emit update_online();
}

void MainWindow::on_pbtn_start_clicked()
{
    serverPort=ui->ld_port->text().toInt();
    ui->pbtn_start->setEnabled(false);
    ui->pbtn_stop->setEnabled(true);
    tcpServer=new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(new_client()));
    tcpServer->listen(QHostAddress(serverIP),serverPort);
}

void MainWindow::on_pbtn_stop_clicked()
{
    ui->pbtn_stop->setEnabled(false);
    ui->pbtn_start->setEnabled(true);
}
