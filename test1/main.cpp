#include "mainwindow.h"

#include <QApplication>
#include "logindig.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "database.h"

QString currentUser="";
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath("./plugins");

    DataBase::connectDatabase();
//    MainWindow w;
    LoginDig dig;
    dig.show();
    return a.exec();

}
