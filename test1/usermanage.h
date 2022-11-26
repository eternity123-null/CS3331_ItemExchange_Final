#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class UserManage;
}

class UserManage : public QDialog
{
    Q_OBJECT

public:
    explicit UserManage(QWidget *parent = nullptr);
    ~UserManage();
    QStringList GetColName(QString tableName);

public slots:
    void tableflush(QSqlQuery sql,QStringList colName);

private slots:
    void on_setAdmin_clicked();

    void on_deleteUser_clicked();

private:
    Ui::UserManage *ui;
    void InitialCombox();
};

#endif // USERMANAGE_H
