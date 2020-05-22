#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase> //数据库基本类
#include <QSqlQuery>    //SQL执行类
#include <QSqlError>    //出错信息类
#include <QList>
#include <QDateTime>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    void initSqlite();
    int  registInfo(QString Name,QString Password);//注册操作
    bool loginCheck(QString ID,QString Password);//登录验证
    void createTable();//
    QList<QString> selectTable(QString ID);//
    void insertTable(QString xuehao, QString name, QString number, QString type);
    void currentTime();

signals:

public slots:

private:
    QString timeStr;
};

#endif // DATABASE_H
