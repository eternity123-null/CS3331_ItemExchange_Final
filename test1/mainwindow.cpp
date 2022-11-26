#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDialog>
#include "database.h"


//管理员界面
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("管理员控制面板");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    newUserAppr * nua=new newUserAppr();
    nua->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    ItemClassManage * classmanage=new ItemClassManage();
    classmanage->show();
}

QStringList MainWindow::GetColName(QString tableName)
{
    QString cmd="PRAGMA table_info ("+tableName+" )";
    QSqlQuery sql;
    QStringList colName;

    sql.prepare(cmd);
    if(sql.exec()){

        while(sql.next()){
            colName.append(sql.value(1).toString());
        }

    }else{
        qDebug()<<sql.lastError();

    }
    return colName;
}

void MainWindow::on_exitBtn_clicked()
{
    this->~MainWindow();
    LoginDig *login=new LoginDig();
    login->show();
}





void MainWindow::on_pushButton_clicked()
{
    UserManage *usrman=new UserManage();
    usrman->show();
}

