#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    //修改名称
    this->setWindowTitle("登录");
    //修改图标
    this->setWindowIcon(QIcon(":/icons/ooopic.ico"));
    QPixmap pixmap = QPixmap(":/icons/aaa.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    window = NULL;
    reg = NULL;
    ui->PasswordLine->setEchoMode(QLineEdit::Password);
    connect(ui->IDLine,SIGNAL(returnPressed()),this,SLOT(on_LoginBtn_clicked()));
    connect(ui->PasswordLine,SIGNAL(returnPressed()),this,SLOT(on_LoginBtn_clicked()));
    connect(NetWork::getInstance(),SIGNAL(receiveData(QByteArray)),this,SLOT(receiveSlot(QByteArray)));

}

login::~login()
{
    delete ui;
}

//登录
void login::on_LoginBtn_clicked()
{
    QString ID,Password;
    ID = ui->IDLine->text();
    Password = ui->PasswordLine->text();
    if(ID.isEmpty()||Password.isEmpty())
    {
        QMessageBox::warning(this,"提示","信息错误！");
    }else{
        bool ok = NetWork::getInstance()->sendData(Protocol::packData("login","id",ID,"password",Password));
        if(!ok)
        {
            QMessageBox::information(this,"提示","网络错误！");
        }
    }
}

void login::receiveSlot(const QByteArray &data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject json = jsonDoc.object();
    QString type = json.value("type").toString();
    if(type == "log-back")
    {
        QString res = json.value("result").toString();
        if(res == "fail")
        {
            QMessageBox::information(this,"提示","帐号或密码错误！");
        }else if(res == "success")
        {
            if(window == NULL)
            {
                window = new Client;
            }
            window->show();
            this->hide();
        }
    }
}


void login::on_RegisterBtn_clicked()
{
    if(reg == NULL)
    {
        reg = new Register;
        connect(reg,SIGNAL(backToLogin()),this,SLOT(showSelfSlot()));
    }
    reg->show();
    this->hide();
}

void login::showSelfSlot()
{
    this->show();
    reg->hide();
}
