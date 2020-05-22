#ifndef DATABASE_H
#define DATABASE_H
/*数据库类*/
#include <QObject>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>
#include<QDateTime>
#include<QJsonObject>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    void initSql();
    void createTable();
    void insertTemp(double temp);
    QJsonObject selectData(QString tableName,int hour);
signals:

public slots:
};

#endif // DATABASE_H
