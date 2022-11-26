#ifndef ITEMCLASSMANAGE_H
#define ITEMCLASSMANAGE_H

#include <QDialog>
#include <mainwindow.h>
namespace Ui {
class ItemClassManage;
}

class ItemClassManage : public QDialog
{
    Q_OBJECT

public:
    explicit ItemClassManage(QWidget *parent = nullptr);
    ~ItemClassManage();
    void getClassInfo();
public slots:
    void flushTable();
private slots:
    void on_add_class_clicked();

    void on_delete_class_clicked();

private:
    Ui::ItemClassManage *ui;
};

#endif // ITEMCLASSMANAGE_H
