#include "database.h"

Database::Database(QObject *parent) : QObject(parent)
{
    initSql();
    createTable();
}

void Database::initSql()
{
  QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("./database.db");
  if(db.open())
  {
      qDebug()<<"database open success...";
  }
  else
  {
      qDebug()<<"database open fail "<<db.lastError().text();
  }
}
//创建表
void Database::createTable()
  {
     QString cmd="create table Temp( "
                 "id integer primary key autoincrement,"
                 "time integer not null,"
                 "data double not null);";
     QSqlQuery query;
     if(query.exec(cmd))
     {
         qDebug()<<"create table success.....";
     }
     else
     {
         qDebug()<<"create table fail "<<query.lastError().text();
     }
}
//插入数据(插入)
void Database::insertTemp(double temp)
{
    QString cmd="insert into Temp(time,data) values(%1,%2);";
    cmd=cmd.arg(QDateTime::currentSecsSinceEpoch()).arg(temp);
    QSqlQuery query;
    if(!query.exec(cmd))
    {
        qDebug()<<"insert Temp fail"<<query.lastError().text();
    }
}

QJsonObject Database::selectData(QString tableName,int hour)
{
    //先计算出具体的时间戳
    int time=QDateTime::currentSecsSinceEpoch()-hour*3600;
    //
    QString cmd="select time,data from '%1' where time "
                ">=%2;";
    cmd=cmd.arg(tableName).arg(time);
    QSqlQuery query;
    if(query.exec(cmd))
    {
        QJsonObject json;
        while (query.next())
        {
           json.insert(query.value(0).toString(),query.value(1).toDouble());
        }
        return json;
    }
    else
    {
        qDebug()<<"select Temp Fail"<<query.lastError().text();
    }
    return QJsonObject();
}

















