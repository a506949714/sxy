#include "database.h"
#include <QDebug>

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    initSqlite();
    //createTable();
}

void DataBase::initSqlite()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    if(db.open())
    {
        qDebug()<<"打开Sqlite数据库成功！";
    }else {
        qDebug()<<"打开Sqlite数据库失败："<<db.lastError().text();
    }
}

int DataBase::registInfo(QString Name, QString Password)
{
    QString cmd = "insert into login values('%1','%2');";
    cmd = cmd.arg(Name,Password);
    QSqlQuery query;
    if(query.exec(cmd))
    {
        return 1;//注册成功
    }
    return 0;//重复注册
}

bool DataBase::loginCheck(QString ID, QString Password)
{
    if(ID.isEmpty()||Password.isEmpty())
    {
        return false;
        qDebug()<<"帐号密码不能为空！";
    }
    QString cmd = "select pwd from login where user = '%1';";
    cmd = cmd.arg(ID);
    //qDebug()<<cmd;

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
        else{
            qDebug()<<query.lastError();
        }
    }
    else
    {
        qDebug()<<query.lastError();
    }
    return false;
}

void DataBase::createTable()
{
    QString cmd = "create table login("
                  "ID varchar(12) primary key,"
                  "user varchar(35) not null,"
                  "pwd varchar(35) not null);";
    QSqlQuery query;
    if(query.exec(cmd))
    {
        qDebug()<<"建立用户表成功！";
    }else{
        qDebug()<<"建立用户表失败："<<query.lastError().text();
    }
}

QList<QString> DataBase::selectTable(QString ID)
{
    QString cmd = "select * from login where ID = '%0'";
    cmd = cmd.arg(ID);
    QSqlQuery query;
    QList<QString> man;
    if(query.exec(cmd))
    {
        if(query.next())
        {
            man.append(query.value(0).toString());
            man.append(query.value(1).toString());
            man.append(query.value(2).toString());
            return man;
        }
        else{
            qDebug()<<query.lastError();
        }
    }
    else
    {
        qDebug()<<query.lastError();
    }
}

void DataBase::insertTable(QString xuehao,QString name,QString number,QString type)
{
    timeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString cmd = "insert into attendance values('%1','%2','%3','%4','%5')";
    cmd = cmd.arg(xuehao,name,number,timeStr,type);
    QSqlQuery query;

    if(query.exec(cmd))
    {
        qDebug()<<"数据插入成功！";
    }else{
        qDebug()<<"数据插入失败："<<query.lastError().text();
    }
}


