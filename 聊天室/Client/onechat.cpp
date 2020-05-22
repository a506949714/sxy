#include "onechat.h"
#include "ui_onechat.h"

OneChat::OneChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OneChat)
{
    ui->setupUi(this);
    //修改名称
    this->setWindowTitle("聊天");
    //修改图标
    this->setWindowIcon(QIcon(":/icons/ooopic.ico"));
    ui->textEdit->setReadOnly(true);
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(on_pushButton_clicked()));
}

OneChat::~OneChat()
{
    delete ui;
}

//设置页面标题
void OneChat::setWindowInfo(QString info)
{
    ui->label->setText(info);
}

//获取时间
QString OneChat::getTime()
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    return time;
}

//设置接收方ID
void OneChat::setID(QString ID)
{
    this->ID = ID;

}

//显示数据
void OneChat::setWindowData(QString name, QString text, QString time)
{
    ui->textEdit->append(time);
    ui->textEdit->append(name+":"+text);
}

//发送
void OneChat::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    QByteArray data = Protocol::packData("onechat","text",text,"time",getTime(),"id",ID);
    if(NetWork::getInstance()->sendData(data))
    {
        ui->lineEdit->clear();
        ui->textEdit->append(getTime());
        ui->textEdit->append("我:"+text);
    }
}
