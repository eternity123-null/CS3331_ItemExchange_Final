#include "signup.h"
#include "ui_signup.h"
#include "mainwindow.h"

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
    setWindowTitle("新用户注册");
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_SignUpBtn_clicked()
{
    QString usrName;
    QString pwd;
    QString telNum;
    QString addr;
    QString email;
    usrName=ui->userNameEdit->text().trimmed();
    pwd=ui->pwdEdit->text().trimmed();
    telNum=ui->telNumEdit->text().trimmed();
    addr=ui->adressEdit->text().trimmed();
    email=ui->emailEdit->text().trimmed();

    QSqlQuery sql;
    sql.prepare("select * from user where ID = :userInputNumber");
    sql.bindValue(":userInputNumber",usrName);
    sql.exec();
    if(sql.first()){
        QMessageBox::warning(this, tr("警告！"),
                           tr("该用户名已被注册！"),
                           QMessageBox::Yes);
    }else{

        sql.prepare("INSERT INTO userToAccept (ID, password, address,tel,email) VALUES (:ID, :password, :address, :tel, :email);");
        sql.bindValue(":ID",usrName);
        sql.bindValue(":password",pwd);
        sql.bindValue(":address",addr);
        sql.bindValue(":tel",telNum);
        sql.bindValue(":email",email);
        bool sign=sql.exec();
        if(sign){
            QMessageBox::information(this,tr("申请完成!"),("已收到您的注册申请，请等待管理员审批！"));
            this->~SignUp();
        }else{
            qDebug()<<"申请失败,请重试";
        }

    }


}

