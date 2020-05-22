#include "register.h"
#include "ui_register.h"
#include <QMessageBox>
#include "protocol.h"

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    //修改名称
    this->setWindowTitle("注册");
    //修改图标
    this->setWindowIcon(QIcon(":/icons/ooopic.ico"));
    ui->PsdLine->setEchoMode(QLineEdit::Password);//隐藏字符
    connect(NetWork::getInstance(),SIGNAL(receiveData(QByteArray)),this,SLOT(receiveSlot(QByteArray)));
}

Register::~Register()
{
    delete ui;
}

//确认注册
void Register::on_confirmBtn_clicked()
{
    QString ID,Name,Password;
    ID = ui->IDLine->text();
    Name = ui->NameLine->text();
    Password = ui->PsdLine->text();
    if(ID.isEmpty()||Name.isEmpty()||Password.isEmpty())
    {
        QMessageBox::warning(this,"警告","信息格式错误！");
    }else{
        QByteArray data =Protocol::packData("register","id",ID,"name",Name,"password",Password);
        //发送数据
        NetWork::getInstance()->sendData(data);
    }
}

//接收网络类转发来的数据
void Register::receiveSlot(const QByteArray &data)
{
    //格式转换
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject json = jsonDoc.object();
    //提取数据标识
    QString type = json.value("type").toString();
    if(type == "reg-back")
    {
        QString res = json.value("result").toString();
        if(res == "success")
        {
            QMessageBox::information(this,"提示","注册成功！");
        }else if(res == "have")
        {
            QMessageBox::information(this,"提示","该学号已注册！");
        }
        else if(res == "fail")
        {
            QMessageBox::information(this,"提示","注册失败");
        }
    }
}

//跳转到登录页面
void Register::on_backBtn_clicked()
{
    emit backToLogin();
}
