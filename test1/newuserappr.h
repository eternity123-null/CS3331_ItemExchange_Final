#ifndef NEWUSERAPPR_H
#define NEWUSERAPPR_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class newUserAppr;
}

class newUserAppr : public QDialog
{
    Q_OBJECT

public:
    explicit newUserAppr(QWidget *parent = nullptr);
    ~newUserAppr();
    void getNewMemInfo();


public slots:
    void flushTable();
private slots:
    void on_agree_clicked();

    void on_reject_clicked();

private:
    Ui::newUserAppr *ui;
};

#endif // NEWUSERAPPR_H
