#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    //修改名称
    this->setWindowTitle("聊天");
    //修改图标
    this->setWindowIcon(QIcon(":/icons/ooopic.ico"));
    ui->textEdit->setReadOnly(true);
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(on_pushButton_clicked()));
    connect(NetWork::getInstance(),SIGNAL(receiveData(QByteArray)),this,SLOT(receiveSlot(QByteArray)));
}

Client::~Client()
{
    delete ui;
}

//获取时间
QString Client::getTime()
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    return time;
}

//讲消息显示到对应的 onechat中
void Client::showOneChatData(QString info, QString text, QString time)
{
    int len = info.indexOf(")")-info.indexOf("(")-1;
    QSound::play(":/sound/Audio.wav");
    QString id = info.mid(info.indexOf("(")+1,len);
    QString name = info.mid(0,info.indexOf("("));
    //判断有没有对应的onechat窗口
    if(hash.contains(hash.key(id)) && hash.key(id)->isVisible())
    {
        hash.key(id)->setWindowData(name,text,time);
        //hash.key(id)->show();
    }else if(hash.contains(hash.key(id)) && !hash.key(id)->isVisible())
    {
        hash.key(id)->setWindowData(name,text,time);
        changeInfoColor(info);
    }
    else
    {
        OneChat *one = new OneChat;
        one->setID(id);
        one->setWindowInfo(info);
        one->setWindowData(name,text,time);
        changeInfoColor(info);
        hash.insert(one,id);
    }
}

//新消息条目变色
void Client::changeInfoColor(QString info)
{
    for(int i=0;i<ui->listWidget->count();i++)
    {
        if(ui->listWidget->item(i)->text()==info)
        {
            //先删除原来的
            ui->listWidget->takeItem(i);
            //插入第一行
            ui->listWidget->insertItem(0,info);
            ui->listWidget->item(0)->setBackgroundColor(QColor("#FFFF00"));
        }
    }

}

void Client::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    if(text.isEmpty())
        return ;
    QByteArray data = Protocol::packData("wechat","text",text,"time",getTime());

    //发送数据
    bool ok = NetWork::getInstance()->sendData(data);
    //
    if(!ok)
        return;
    ui->lineEdit->clear();
    ui->textEdit->append(getTime());
    ui->textEdit->append("我："+text);
}

//接收信号
void Client::receiveSlot(const QByteArray &data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject json = jsonDoc.object();
    QString type = json.value("type").toString();
    if(type == "wechat-back")
    {
        QString time,name,text;
        time = json.value("time").toString();
        name = json.value("name").toString();
        text = json.value("text").toString();
        ui->textEdit->append(time);
        ui->textEdit->append(name+":"+text);
    }else if(type == "onlinelist-back")
    {
        QJsonArray array = json.value("array").toArray();
        //循环提取数据
        for(int i=0;i<array.size();i++)
        {
            ui->listWidget->addItem(array.at(i).toString());
        }
    }
    else if(type == "newonline-back")
    {
        QString info = json.value("info").toString();
        for(int i=0; i<ui->listWidget->count();i++)
        {
            if(ui->listWidget->item(i)->text() == info)
                return;
        }
        ui->listWidget->addItem(info);
    }
    else if(type == "offline-back")
    {
        QString info = json.value("info").toString();
        for(int i=0;i<ui->listWidget->count();i++)
        {
            if(ui->listWidget->item(i)->text() == info)
            {
                ui->listWidget->takeItem(i);
                break;
            }
        }
    }
    else if(type == "onechat-back")
    {
        QString text,info,time;
        text = json.value("text").toString();
        info = json.value("info").toString();
        time = json.value("time").toString();
        showOneChatData(info,text,time);
    }
}

//双击产生新的窗口
void Client::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString info = item->text();//获取双击的 学生信息
    item->setBackground(QColor("white"));//颜色复原
    //从info中提取ID
    int len = info.indexOf(")")-info.indexOf("(")-1;
    QString ID = info.mid(info.indexOf("(")+1,len);
    if(hash.contains(hash.key(ID)))
    {
        hash.key(ID)->setWindowFlags(Qt::WindowCloseButtonHint);
        hash.key(ID)->show();
    }else{
        //构造新窗口
        OneChat *one = new OneChat;
        one->setWindowInfo(info);
        one->setID(ID);
        hash.insert(one,ID);
        one->show();
    }
}
