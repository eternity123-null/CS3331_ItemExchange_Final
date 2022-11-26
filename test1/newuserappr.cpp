#include "newuserappr.h"
#include "ui_newuserappr.h"
#include "database.h"

newUserAppr::newUserAppr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newUserAppr)
{
    ui->setupUi(this);
    setWindowTitle("新用户审批");
    ui->newMemInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    getNewMemInfo();

}

newUserAppr::~newUserAppr()
{
    delete ui;
}

void newUserAppr::getNewMemInfo()
{
    ui->newMemInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->newMemInfo->setColumnCount(4);
    ui->newMemInfo->setHorizontalHeaderLabels(QStringList()<<"用户名"<<"地址"<<"电话"<<"邮箱");
    flushTable();


}

void newUserAppr::flushTable(){
    QSqlQuery sql;
    sql.prepare("select * from userToAccept");
    sql.exec();
    QString id,address,email,tel;
    ui->newMemInfo->setRowCount(0);
    int rowcnt=0;
    while(sql.next()){
        id=sql.value("ID").toString();
        address=sql.value("address").toString();
        email=sql.value("email").toString();
        tel=sql.value("tel").toString();
        ui->newMemInfo->setRowCount(rowcnt+1);
        ui->newMemInfo->setItem(rowcnt,0,new QTableWidgetItem(id));
        ui->newMemInfo->setItem(rowcnt,1,new QTableWidgetItem(address));
        ui->newMemInfo->setItem(rowcnt,2,new QTableWidgetItem(tel));
        ui->newMemInfo->setItem(rowcnt,3,new QTableWidgetItem(email));
        rowcnt++;
    }

}

void newUserAppr::on_agree_clicked()
{
    QSqlQuery sql;
    QList<QTableWidgetItem*>items =ui->newMemInfo->selectedItems();
    if(items.count()>0){
        QString ID;
        while(items.count()>0){
            ID=items.at(0)->text();
            sql.prepare("insert into user select * from userToAccept WHERE ID= :id");
            sql.bindValue(":id",ID);
            sql.exec();

            sql.prepare("delete from userToAccept WHERE ID= :id");
            sql.bindValue(":id",ID);
            sql.exec();
            items.pop_front();
        }
        flushTable();

    }else{
        QMessageBox::warning(this,"提示","请选择要操作的用户");
    }
}


void newUserAppr::on_reject_clicked()
{
    QSqlQuery sql;
    QList<QTableWidgetItem*>items =ui->newMemInfo->selectedItems();
    if(items.count()>0){
        QString ID;
        while(items.count()>0){
            ID=items.at(0)->text();
            sql.prepare("delete from userToAccept WHERE ID= :id");
            sql.bindValue(":id",ID);
            sql.exec();
            items.pop_front();
        }
        flushTable();

    }else{
        QMessageBox::warning(this,"提示","请选择要操作的用户");
    }
}

