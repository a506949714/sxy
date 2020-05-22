#include "datebase.h"
#include <QDebug>
/*数据库处理类*/
Datebase::Datebase(QObject *parent) : QObject(parent)
{
    initSqlite();

}


//初始化Sqlite3数据库
void Datebase::initSqlite()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../ServerS/xwq.db");
    if(db.open())
    {
        qDebug()<<"打开Sqlite数据库成功！";
    }else {
        qDebug()<<"打开Sqlite数据库失败："<<db.lastError().text();
    }
}



//插入数据
bool Datebase::insertdata(double t, double h, double l)
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
    //QString cmd = "insert into da values('"+date+"',"+QString::number(t,'f',2)+","+QString::number(h,'f',2)+","+QString::number(l,'f',2)+");";
    QString cmd = "insert into da values('%1','%2','%3','%4');";
    cmd = cmd.arg(date,QString::number(t,'f',2),QString::number(h,'f',2),QString::number(l,'f',2));
    QSqlQuery query;
    if(query.exec(cmd))
    {
        return 1;//成功
    }
    return 0;//注册
}
