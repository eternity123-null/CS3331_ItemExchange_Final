#include "logindig.h"
#include "ui_logindig.h"
#include <QMessageBox>
#include "mainwindow.h"

extern QString currentUser;
LoginDig::LoginDig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDig)
{

    ui->setupUi(this);
    setWindowTitle("\"你帮我助\"物品交换系统 --登陆");
    ui->userLineEdit->setPlaceholderText("请输入用户名");
    ui->pwdLineEdit->setPlaceholderText("请输入密码");

}

LoginDig::~LoginDig()
{
    delete ui;
}

void LoginDig::on_loginBtn_clicked()
{
    QString username;
    QString password;
    username=ui->userLineEdit->text().trimmed();
    password=ui->pwdLineEdit->text().trimmed();
    QString userType;
    if(ui->radioButton->isChecked()){
        userType="adimin";
    }else{
        userType="normal";
    }

    if(userType=="adimin"){
        QSqlQuery sql;
        sql.prepare("select * from admin where ID = :userInputNumber");
        sql.bindValue(":userInputNumber",username);
        sql.exec();
        QString userNumber;
        QString userPassword;
        while(sql.next()){
            userNumber=sql.value("ID").toString();
            userPassword=sql.value("password").toString();
        }

        qDebug() << "数据库找到的账号是"+userNumber;
        qDebug() << "数据库找到的密码是"+userPassword;
        if (password == userPassword && username == userNumber)
        {
            qDebug() << "登录成功!";
            currentUser=userNumber;
            qDebug()<<"currentUser:"<<currentUser;
            this->~LoginDig();
            MainWindow * w = new MainWindow();
            w->show();
        }
        else
        {
            QMessageBox::warning(this, tr("警告！"),
                               tr("用户名或密码错误！"),
                               QMessageBox::Yes);
        }
    }
    if(userType=="normal"){
        QSqlQuery sql;
        sql.prepare("select * from user where ID = :userInputNumber");
        sql.bindValue(":userInputNumber",username);
        sql.exec();
        QString userNumber;
        QString userPassword;
        while(sql.next()){
            userNumber=sql.value("ID").toString();
            userPassword=sql.value("password").toString();
        }

        qDebug() << "数据库找到的账号是"+userNumber;
        qDebug() << "数据库找到的密码是"+userPassword;
        if (password == userPassword && username == userNumber)
        {
            qDebug() << "登录成功!";
            currentUser=userNumber;
            qDebug()<<"currentUser:"<<currentUser;
            this->~LoginDig();
            UserMainWindow * w = new UserMainWindow();
            w->show();
        }
        else
        {
            QMessageBox::warning(this, tr("警告！"),
                               tr("用户名或密码错误！"),
                               QMessageBox::Yes);
        }
    }
}

void LoginDig::on_SignUpBtn_clicked()
{
    SignUp *signup=new SignUp(this);
    signup->show();
}

