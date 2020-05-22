#ifndef DATEBASE_H
#define DATEBASE_H
/*数据库处理类*/
#include <QObject>
#include <QSqlDatabase> //数据库基本类
#include <QSqlQuery>    //SQL执行类
#include <QSqlError>    //出错信息类
#include <QDateTime>

class Datebase : public QObject
{
    Q_OBJECT
public:
    explicit Datebase(QObject *parent = nullptr);
    void initSqlite();
    bool insertdata(double t,double h,double l);

signals:

public slots:
};

#endif // DATEBASE_H
