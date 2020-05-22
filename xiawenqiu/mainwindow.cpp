#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1300,768);
    hum = 0;
    temp = 0;
    light = 0;
    //修改名称
    this->setWindowTitle("夏雯秋的上位机");
    //修改图标
    this->setWindowIcon(QIcon(":/icons/ooopic.ico"));

    QPixmap pixmap = QPixmap(":/icons/a1.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );

    ui->label->setFont(QFont("幼圆",12,75));
    ui->label_2->setFont(QFont("幼圆",12,75));
    ui->label_3->setFont(QFont("幼圆",12,75));
    ui->label_4->setFont(QFont("幼圆",12,75));
    ui->label->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd  dddd  hh:mm:ss "));
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerSlot()));
    timer->start(1000);

    //子界面
    stack=new QStackedWidget(this);
    stack->setGeometry(350,250,900,500);
    widget1=new TempChart;
    widget2=new HumChart;
    widget3=new LightChart;
    stack->addWidget(widget1);
    stack->addWidget(widget2);
    stack->addWidget(widget3);


   // connect(serial,SIGNAL(readyRead()),this,SLOT(readSlot()));
    connect(NetWork::getInstance(),SIGNAL(receiveData(QByteArray)),this,SLOT(readSlot(QByteArray)));

    //仪表盘
    tempshow=new ShowData(this);
    tempshow->setGeometry(525,50,200,200);
    tempshow->setMaxAndMin(80,-20);
    tempshow->setName("温度","℃");
    tempshow->setFixedSize(200,200);

    humshow=new ShowData(this);
    humshow->setGeometry(800,50,200,200);
    humshow->setMaxAndMin(100,0);
    humshow->setName("湿度","%");
    humshow->setFixedSize(200,200);

    stack->setCurrentIndex(0);


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::readSlot(const QByteArray &data)
{

    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject json = jsonDoc.object();
    light = json.value("light").toDouble();
    temp = json.value("temp").toDouble();
    hum = json.value("hum").toDouble();
    ui->textBrowser->append("湿度为:"+QString::number(hum));
    ui->textBrowser->append("温度为:"+QString::number(temp));
    ui->textBrowser->append("光照为:"+QString::number(light));
    ui->label_2->setText("温度为:"+QString::number(temp)+"℃");
    ui->label_3->setText("湿度为:"+QString::number(hum)+"%");
    ui->label_3->setText("光照为:"+QString::number(light)+"lc");
    //数据换算
    //
    //
    tempshow->setData(temp);
    humshow->setData(hum);
    json_hum.insert(QString::number(QDateTime::currentSecsSinceEpoch()),hum);
    json_tmp.insert(QString::number(QDateTime::currentSecsSinceEpoch()),temp);
    json_light.insert(QString::number(QDateTime::currentSecsSinceEpoch()),light);
    widget1->tempchart->setShowData2(json_tmp);
    widget2->humchart->setShowData2(json_hum);
    widget3->lightchart->setShowData2(json_light);
}

//清空textbrowser
void MainWindow::on_pushButton_3_clicked()
{
    ui->textBrowser->clear();
}


//切换湿度图表
void MainWindow::on_pushButton_5_clicked()
{
    stack->setCurrentIndex(1);
}

//切换温度图表
void MainWindow::on_pushButton_4_clicked()
{
    stack->setCurrentIndex(0);
}

void MainWindow::timerSlot()
{
    ui->label->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd dddd hh:mm:ss "));
}

//光照图表
void MainWindow::on_pushButton_6_clicked()
{
    stack->setCurrentIndex(2);
}
