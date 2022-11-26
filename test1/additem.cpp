#include "additem.h"
#include "ui_additem.h"

extern QString currentUser;
AddItem::AddItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItem)
{
    ui->setupUi(this);
    InitialCombox();
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

AddItem::~AddItem()
{
    delete ui;
}

void AddItem::on_classSelect_currentTextChanged(const QString &arg1)
{
    QString classname=ui->classSelect->currentText();

    QStringList colName=GetColName(classname);
    colName.pop_front();
    ui->tableWidget->setColumnCount(colName.count());
    ui->tableWidget->setHorizontalHeaderLabels(colName);
    ui->tableWidget->setRowCount(1);

}

QStringList AddItem::GetColName(QString tableName)
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

void AddItem::on_pushButton_clicked()
{
    QString itemName=ui->itemName->text().trimmed();
    QString itemDescription=ui->itemDescription->text().trimmed();
    QString cmd,ownerid,tel,email,address,classname;
    classname=ui->classSelect->currentText();
    cmd="select * from user where ID='"+currentUser+"'";
    qDebug()<<cmd;
    QSqlQuery sql;
    qDebug()<<sql.exec(cmd);
    while(sql.next()){
        ownerid=currentUser;
        tel=sql.value("ID").toString();
        email=sql.value("email").toString();
        address=sql.value("address").toString();
    }
    cmd="INSERT INTO ITEMMAIN VALUES (NULL,\""+itemName+"\",\""+itemDescription+"\",\""+address+"\",\""+tel+"\",\""+email+"\",\""+classname+"\",\""+ownerid+"\")";
    qDebug()<<cmd;
    qDebug()<<sql.exec(cmd)<<sql.lastError();
    QString ID=sql.lastInsertId().toString();
    qDebug()<<ID;
    QStringList colName=GetColName(classname);
    colName.pop_front();
    qDebug()<<colName;
    cmd="INSERT INTO "+classname+" VALUES("+ID;
    for(int i=0;i<colName.count();i++){
        qDebug()<<ui->tableWidget->item(0,i)->text();
        cmd+=(",\""+ui->tableWidget->item(0,i)->text()+"\"");
    }
    cmd+=")";
    qDebug()<<cmd;
    qDebug()<<sql.exec(cmd)<<sql.lastError();
    QMessageBox::information(this,tr("添加成功!"),("物品已经添加！"));

}

void AddItem::InitialCombox(){
    QSqlQuery sql;
    sql.exec("SELECT NAME FROM class");
    if(!sql.exec()){
        qDebug() << "Error: Fail to query table. " << sql.lastError();
    }else{
        while(sql.next())
        {
            QString name = sql.value(0).toString();
            ui->classSelect->addItem(name);
        }
    }

}
