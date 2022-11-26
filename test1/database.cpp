#include "database.h"
#include "mainwindow.h"
//数据库在build test1 文件夹下面
QSqlDatabase DataBase :: db = QSqlDatabase::addDatabase("QSQLITE");
QSqlQuery * DataBase:: sql = NULL;
DataBase::DataBase()
{

}

bool DataBase::connectDatabase()
{

    db.setDatabaseName("itemLib.db");

    if (!db.open())
    {
        qDebug() << "Error: Failed to connect database." << db.lastError();
        return false;
    }
    else
    {
        qDebug()<<"database connect success"<<db.databaseName();
        QSqlQuery sql;
        QString cmd;
        cmd="CREATE TABLE IF NOT EXISTS admin (ID CHAR(50)  PRIMARY KEY NOT NULL,password CHAR(50) NOT NULL);";
        qDebug()<<sql.exec(cmd)<<sql.lastError();
        cmd="insert into admin values(\"1\",\"1\")";
        qDebug()<<sql.exec(cmd)<<sql.lastError();
        cmd="CREATE TABLE IF NOT EXISTS user(ID CHAR(50)  PRIMARY KEY NOT NULL,password CHAR(50) NOT NULL,address CHAR(50) NOT NULL,tel TEXT NOT NULL,email TEXT)";
        qDebug()<<sql.exec(cmd)<<sql.lastError();
        cmd="CREATE TABLE IF NOT EXISTS itemmain(ID integer primary key AUTOINCREMENT,NAME text not null,DESCRIPTION text ,ADDRESS text not null,TEL text not null,EMAIL text ,CLASS text not null,OWNERID text not null)";
        qDebug()<<sql.exec(cmd)<<sql.lastError();
        cmd="CREATE TABLE IF NOT EXISTS class(NAME text  PRIMARY KEY NOT NULL,ATTRIBUTE text)";
        qDebug()<<sql.exec(cmd)<<sql.lastError();
        cmd="CREATE TABLE IF NOT EXISTS userToAccept(ID CHAR(50)  PRIMARY KEY NOT NULL,password CHAR(50) NOT NULL,address CHAR(50) NOT NULL,tel TEXT NOT NULL,email TEXT)";
        qDebug()<<sql.exec(cmd)<<sql.lastError();
        return true;
    }




}

bool DataBase::quitConnection()
{
    db.close();
    return true;
}


/* 已有的数据库:
CREATE TABLE IF NOT EXISTS itemmain(ID integer primary key AUTOINCREMENT,NAME text not null,DESCRIPTION text ,ADDRESS text not null,TEL text not null,EMAIL text ,CLASS text not null,OWNERID text not null);

CREATE TABLE IF NOT EXISTS user(
ID CHAR(50)  PRIMARY KEY NOT NULL,
password CHAR(50) NOT NULL,
address CHAR(50) NOT NULL,
tel TEXT NOT NULL,
email TEXT);

CREATE TABLE IF NOT EXISTS "admin"(
ID CHAR(50)  PRIMARY KEY NOT NULL,
password CHAR(50) NOT NULL);

CREATE TABLE IF NOT EXISTS class(
NAME text  PRIMARY KEY NOT NULL,
ATTRIBUTE text);

CREATE TABLE userToAccept(
ID CHAR(50)  PRIMARY KEY NOT NULL,
password CHAR(50) NOT NULL,
address CHAR(50) NOT NULL,
tel TEXT NOT NULL,
email TEXT
);
*/
