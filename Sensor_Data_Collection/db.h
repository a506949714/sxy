#ifndef DB_H
#define DB_H

#include <QList>
#include <QStringList>
#include <QSqlRecord>
#include <QSqlQuery>

class Db
{
public:
    Db();
    bool connectdb();   
    QList<QStringList> selectDataFromBase(QString tablename);
};

#endif // DB_H
