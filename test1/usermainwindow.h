#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class UserMainWindow;
}

class UserMainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UserMainWindow(QWidget *parent = nullptr);
    ~UserMainWindow();
    QStringList GetColName(QString tableName);
public slots:
    void tableflush(QSqlQuery sql,QStringList colName);

private slots:
    void on_addItemBtn_clicked();

    void on_searchBtn_clicked();

    void on_TakeBtn_clicked();

    void on_itemclass_currentTextChanged(const QString &arg1);



    void on_tableWidget_cellClicked(int row, int column);

    void on_exitBtn_clicked();

private:
    Ui::UserMainWindow *ui;
    void InitialCombox();
};

#endif // USERMAINWINDOW_H
