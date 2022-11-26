#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "database.h"
#include <QMainWindow>
#include "usermainwindow.h"
#include "newuserappr.h"
#include <QMessageBox>
#include <QDebug>
#include "itemclassmanage.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QTableWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include "additem.h"
#include "signup.h"
#include "logindig.h"
#include "usermanage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    DataBase mydatabase;
    QStringList GetColName(QString tableName);
private slots:

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_exitBtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
