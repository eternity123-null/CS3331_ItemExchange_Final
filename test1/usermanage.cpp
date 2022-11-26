#include "usermanage.h"
#include "ui_usermanage.h"

UserManage::UserManage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserManage)
{
    ui->setupUi(this);
    InitialCombox();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

UserManage::~UserManage()
{
    delete ui;
}

void UserManage::on_setAdmin_clicked()
{
    QSqlQuery sql;
    QList<QTableWidgetItem*>items =ui->tableWidget->selectedItems();
    QString cmd;
    QStringList colName=GetColName("user");
    if(items.count()>0){
        QString ID,password;
        ID=items.at(0)->text();

        sql.prepare("select password from user where ID=:id");
        sql.bindValue(":id",ID);
        sql.exec();
        sql.next();
        password=sql.value("password").toString();
        qDebug()<<ID;
        qDebug()<<password;

        cmd="insert into admin values ('"+ID+"','"+password+"')";
        qDebug()<<sql.exec(cmd)<<sql.lastError();

        sql.prepare("select * from user");
        sql.exec();
        ui->tableWidget->clear();
        tableflush(sql,colName);

    }else{
        QMessageBox::warning(this,"提示","请选择要设置为管理员的用户");
    }
}


void UserManage::on_deleteUser_clicked()
{
    QSqlQuery sql;
    QList<QTableWidgetItem*>items =ui->tableWidget->selectedItems();
    QStringList colName=GetColName("user");
    if(items.count()>0){
        QString ID;
        ID=items.at(0)->text();

        QMessageBox::StandardButton box= QMessageBox::question(this,"提示","确定删除 "+ID+" 用户吗?",QMessageBox::Yes|QMessageBox::No);

        if(box == QMessageBox::Yes){

            sql.prepare("delete from user WHERE ID=:id");
            sql.bindValue(":id",ID);
            sql.exec();
            sql.prepare("select * from user");
            sql.exec();
            ui->tableWidget->clear();
            tableflush(sql,colName);
        }
    }else{
        QMessageBox::warning(this,"提示","请选择要删除的用户");
    }
}

void UserManage::InitialCombox(){
    QStringList colName=GetColName("user");
    QSqlQuery sql;
    sql.prepare("SELECT * from user");
    sql.exec();
    tableflush(sql,colName);
}

QStringList UserManage::GetColName(QString tableName)
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

void UserManage::tableflush(QSqlQuery sql,QStringList colName)
{
    ui->tableWidget->setColumnCount(colName.count());
    ui->tableWidget->setHorizontalHeaderLabels(colName);
    QString text;
    ui->tableWidget->setRowCount(0);

    int rowcnt=0;
    while(sql.next()){
        ui->tableWidget->setRowCount(rowcnt+1);
        for(int i=0;i<colName.count();i++){
            text=sql.value(colName[i]).toString();
            ui->tableWidget->setItem(rowcnt,i,new QTableWidgetItem(text));
        }
        rowcnt++;
    }
}
