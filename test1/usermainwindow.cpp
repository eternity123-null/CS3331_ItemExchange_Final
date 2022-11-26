#include "usermainwindow.h"
#include "ui_usermainwindow.h"
extern QString currentUser;

UserMainWindow::UserMainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    InitialCombox();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}

void UserMainWindow::InitialCombox(){
    QSqlQuery sql;
    sql.exec("SELECT NAME FROM class");
    if(!sql.exec()){
        qDebug() << "Error: Fail to query table. " << sql.lastError();
    }else{
        while(sql.next())
        {
            QString name = sql.value(0).toString();
            ui->itemclass->addItem(name);
        }
    }

}

void UserMainWindow::on_addItemBtn_clicked()
{
    AddItem *add=new AddItem();
    add->show();
}


void UserMainWindow::on_searchBtn_clicked()
{
    QString token=ui->keyword->text();
    QSqlQuery sql;
    QString classname=ui->itemclass->currentText();

    QString cmd="SELECT * from itemmain WHERE CLASS=\""+classname+ "\" AND (NAME LIKE '%"+token+"%' OR DESCRIPTION LIKE '%"+token+"%')";
    qDebug()<<cmd;
    sql.exec(cmd);
    QStringList colName=GetColName("itemmain");
    tableflush(sql,colName);

}


void UserMainWindow::on_TakeBtn_clicked()
{
    QSqlQuery sql;
    QList<QTableWidgetItem*>items =ui->tableWidget->selectedItems();
    QString cmd;
    if(items.count()>0){
        QString ID,className;
        className=ui->tableWidget->selectedItems().value(6)->text();
        QStringList colName=GetColName(className);

        ID=items.at(0)->text();

        qDebug()<<ID;
        sql.prepare("delete from itemmain WHERE ID=:id");
        sql.bindValue(":id",ID);
        sql.exec();
        qDebug()<<className;

        cmd="delete from "+className+" WHERE ID="+ID;

        qDebug()<<sql.exec(cmd);


        sql.prepare("select * from itemmain where CLASS=:clanm");
        sql.bindValue(":clanm",className);
        sql.exec();
        colName=GetColName("itemmain");
        ui->tableWidget->clear();
        tableflush(sql,colName);

    }else{
        QMessageBox::warning(this,"提示","请选择要取用的物品");
    }

}

QStringList UserMainWindow::GetColName(QString tableName)
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

void UserMainWindow::on_itemclass_currentTextChanged(const QString &arg1)
{
    QString classname=ui->itemclass->currentText();
    qDebug()<<ui->itemclass->currentText();


    QSqlQuery sql;
    QStringList colName=GetColName("itemmain");

    sql.prepare("select * from itemmain where CLASS= :clanm");
    sql.bindValue(":clanm",classname);
    sql.exec();
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableflush(sql,colName);
}

void UserMainWindow::tableflush(QSqlQuery sql,QStringList colName)
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

// INSERT INTO ITEMMAIN VALUES (NULL,"CSAPP","深入理解计算机系统","sjtu","122","cdz@163.com","书籍","1")
// INSERT INTO 书籍 VALUES(2,"1","David","机械工业出版社")
//INSERT INTO food VALUES(5,"2kg","bad")
//INSERT INTO ITEMMAIN VALUES (NULL,"CSAPP","深入理解计算机系统","sjtu","122","cdz@163.com","书籍","1")
//INSERT INTO ITEMMAIN VALUES (NULL,"chicken","只因","sjtu","23422","cfvevvb@163.com","food","1")

void UserMainWindow::on_tableWidget_cellClicked(int row, int column)
{
    QString id=ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text();
    QString Class=ui->tableWidget->item(ui->tableWidget->currentRow(),6)->text();
    QSqlQuery sql;
    QStringList colName=GetColName(Class);
    QString cmd="select * from "+Class+" where ID="+id;
    ui->listWidget->clear();
    if(sql.exec(cmd)){
        while(sql.next()){
            for(int i=0;i<colName.count();i++){
                ui->listWidget->addItem(colName[i]+": "+sql.value(colName[i]).toString());
            }
        }
    }else{
        qDebug()<<"false"<<sql.lastError();
    }
}


void UserMainWindow::on_exitBtn_clicked()
{
    this->~UserMainWindow();

    LoginDig *login=new LoginDig();
    login->show();
}

