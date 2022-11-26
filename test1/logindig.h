#ifndef LOGINDIG_H
#define LOGINDIG_H

#include <QDialog>
#include "signup.h"
#include <QCheckBox>
namespace Ui {
class LoginDig;
}

class LoginDig : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDig(QWidget *parent = nullptr);
    ~LoginDig();

private slots:
    void on_loginBtn_clicked();


    void on_SignUpBtn_clicked();

private:
    Ui::LoginDig *ui;
};

#endif // LOGINDIG_H
