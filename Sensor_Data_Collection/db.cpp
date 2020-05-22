#include "db.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QCoreApplication>

Db::Db()
{
}

//
bool Db::connectdb()  //连接数据库
{
//    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");  //使用sqlite数据库的驱动,连接sqlite数据库
    db.setDatabaseName("../Sensor_Data_Collection/SensorData.db");  //数据库名为数据库文件
    bool ok = db.open();
    if(ok)  //连接数据库成功
    {
        qDebug()<<"数据库打开成功!";

    }
    else  //连接失败
    {
        qDebug()<<"数据库打开失败!";
    }
    return ok;
}

//
QList<QStringList> Db::selectDataFromBase(QString tablename)  //从某个表里面查询数据
{
    QString sql;
    sql=QString("SELECT * FROM '%0'").arg(tablename);
    QSqlQuery query;
    bool ok = query.exec(sql);
    if(ok)
    {
        qDebug()<<"查询"<<tablename<<"成功";
    }
    else
    {
        qDebug()<<"查询"<<tablename<<"失败";

    }

    QList<QStringList> data;
    while(query.next())
    {
        QStringList rowdata;

        QSqlRecord columnrecord = query.record();
        int column =columnrecord.count();  //获取表中数据列数

        for(int c=0;c<column;c++)
        {
            rowdata<<query.value(c).toString();
        }
        data.append(rowdata);
    }
    return data;
}
