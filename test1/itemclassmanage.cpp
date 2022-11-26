#include "itemclassmanage.h"
#include "ui_itemclassmanage.h"

ItemClassManage::ItemClassManage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemClassManage)
{
    ui->setupUi(this);
    setWindowTitle("物品类别管理");
    ui->classTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->classTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->classTable->setSelectionMode(QAbstractItemView::SingleSelection);
    getClassInfo();
}

ItemClassManage::~ItemClassManage()
{
    delete ui;
}

void ItemClassManage::getClassInfo()
{
    ui->classTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->classTable->setColumnCount(2);
    ui->classTable->setHorizontalHeaderLabels(QStringList()<<"物品类名"<<"属性");
    flushTable();


}

void ItemClassManage::flushTable(){
    QSqlQuery sql;
    sql.prepare("select * from class");
    sql.exec();
    QString name,attribute;
    ui->classTable->setRowCount(0);
    int rowcnt=0;
    while(sql.next()){
        name=sql.value("name").toString();
        attribute=sql.value("attribute").toString();
        ui->classTable->setRowCount(rowcnt+1);
        ui->classTable->setItem(rowcnt,0,new QTableWidgetItem(name));
        ui->classTable->setItem(rowcnt,1,new QTableWidgetItem(attribute));
        rowcnt++;
    }

}

void ItemClassManage::on_add_class_clicked()
{
    QString name,attribute,cmd;
    name=ui->className->text().trimmed();
    attribute=ui->classAttr->text().trimmed();
    attribute.replace(QRegExp("[\\s]+"), " ");
    if(name!=NULL){
        QSqlQuery sql;
        sql.prepare("insert into class values(:name, :attr)");
        sql.bindValue(":name",name);
        sql.bindValue(":attr",attribute);
        sql.exec();

        cmd="CREATE table ";
        cmd+=name;
        cmd+="(ID integer primary key not null";

        QStringList attrlist=attribute.split(" ");
        while(!attrlist.isEmpty()){
            cmd+=",";
            cmd+=attrlist[0];
            cmd+=" text ";
            attrlist.pop_front();
        }
        cmd+=")";
        qDebug()<<cmd;
        sql.prepare(cmd);
        sql.exec();

        flushTable();
    }


}


void ItemClassManage::on_delete_class_clicked()
{
    QSqlQuery sql;
    QList<QTableWidgetItem*>items =ui->classTable->selectedItems();
    if(items.count()>0){
            QString name,cmd;
            name=items.at(0)->text();
            //删除class表中的类别项
            sql.prepare("delete from class WHERE NAME= :name");
            sql.bindValue(":name",name);
            sql.exec();
            //在主表中删除该类别所有项
            sql.prepare("delete from itemmain WHERE NAME= :name");
            sql.bindValue(":name",name);
            sql.exec();
            //删除该类的属性表
            cmd="DROP TABLE ";
            cmd+=name;
            sql.prepare(cmd);
            qDebug()<<cmd;
            qDebug()<<sql.exec();

        flushTable();


    }else{
        QMessageBox::warning(this,"提示","请选择要操作的类别");
    }
}

