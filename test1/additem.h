#ifndef ADDITEM_H
#define ADDITEM_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class AddItem;
}

class AddItem : public QDialog
{
    Q_OBJECT

public:
    explicit AddItem(QWidget *parent = nullptr);
    QStringList GetColName(QString tableName);
    ~AddItem();

private slots:
    void on_classSelect_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::AddItem *ui;
    void InitialCombox();
};

#endif // ADDITEM_H
