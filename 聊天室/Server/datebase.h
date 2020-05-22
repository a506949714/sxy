#ifndef DATEBASE_H
#define DATEBASE_H
/*数据库处理类*/
#include <QObject>
#include <QSqlDatabase> //数据库基本类
#include <QSqlQuery>    //SQL执行类
#include <QSqlError>    //出错信息类

class Datebase : public QObject
{
    Q_OBJECT
public:
    explicit Datebase(QObject *parent = nullptr);
    void initMySql();
    void initSqlite();
    void createTable();//建标
    bool checkInfo(QString ID,QString Name);//验证信息(注册实名)
    int  registerInfo(QString ID,QString Name,QString Password);//注册操作
    bool loginCheck(QString ID,QString Password);//登录验证
    QString getName(QString ID);

signals:

public slots:
};

#endif // DATEBASE_H
