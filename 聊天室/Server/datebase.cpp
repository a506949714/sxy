#include "datebase.h"
#include <QDebug>
/*数据库处理类*/
Datebase::Datebase(QObject *parent) : QObject(parent)
{
    initMySql();
    initSqlite();
    createTable();
}

//MySql初始化
void Datebase::initMySql()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");//MySql服务器所在的IP地址
    db.setPort(3306);//MySql服务程序的端口号
    db.setUserName("");//验证的用户名
    db.setPassword("");//验证的密码
    db.setDatabaseName("");//要访问的数据库名称
    if(db.open())
    {
        qDebug()<<"数据库打开成功！";
    }else{
        qDebug()<<"数据库打开失败："<<db.lastError().text();
    }
}

//初始化Sqlite3数据库
void Datebase::initSqlite()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("info.db");
    if(db.open())
    {
        qDebug()<<"打开Sqlite数据库成功！";
    }else {
        qDebug()<<"打开Sqlite数据库失败："<<db.lastError().text();
    }
}

//建表
void Datebase::createTable()
{
    QString cmd = "create table user("
                  "ID varchar(12) primary key,"
                  "Name varchar(8) not null,"
                  "PassWord varchar(35) not null);";
    QSqlQuery query;
    if(query.exec(cmd))
    {
        qDebug()<<"建立用户表成功！";
    }else{
        qDebug()<<"建立用户表失败："<<query.lastError().text();
    }
}

//验证信息
bool Datebase::checkInfo(QString ID, QString Name)
{
    if(ID.isEmpty()||Name.isEmpty())
    {
        return false;
    }
    QString cmd = "select Name from info where ID = '%1';";
    cmd = cmd.arg(ID);
    QSqlQuery query;
    if(query.exec(cmd))
    {
        if(query.next())//判断有误查询出的值/查询下一行
        {
            if(query.value(0).toString() == Name)
            {
                return true;
            }
        }
    }else{
        qDebug()<<"(77)验证信息失败:"<<query.lastError().text();
    }
    return false;
}

//注册
int Datebase::registerInfo(QString ID, QString Name, QString Password)
{
    //实名验证
    if(!checkInfo(ID,Name))
    {
        return -1;//注册失败
    }
    QString cmd = "insert into user values('%1','%2','%3');";
    cmd = cmd.arg(ID,Name,Password);
    QSqlQuery query;
    if(query.exec(cmd))
    {
        return 1;//注册成功
    }
    return 0;//重复注册
}

//登录验证
bool Datebase::loginCheck(QString ID, QString Password)
{
    if(ID.isEmpty()||Password.isEmpty())
    {
        return false;
    }
    QString cmd = "select Password from user where ID = '%1';";
    cmd = cmd.arg(ID);
    QSqlQuery query;
    if(query.exec(cmd))
    {
        if(query.next())
        {
            if(query.value(0).toString() == Password)
            {
                return true;
            }
        }
    }
    return false;
}

//根据ID查名字
QString Datebase::getName(QString ID)
{
    QString cmd = "select Name from user where ID = '%1';";
    cmd = cmd.arg(ID);
    QSqlQuery query;
    if(query.exec(cmd))
    {
        if(query.next())
        {
            return query.value(0).toString();
        }
    }
    return NULL;
}
