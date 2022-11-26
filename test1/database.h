#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class DataBase
{
public:
    DataBase();
    static bool connectDatabase();
    static bool quitConnection();

private:
    static QSqlDatabase db;
    static QSqlQuery *sql;
};

#endif // DATABASE_H
