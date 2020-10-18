#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_Login_clicked()
{
    QString userName = ui->lineEdit_UserName->text();

    if(userName.isEmpty())
    {
        QMessageBox::critical(0 ,"提示" , "请填写账号", QMessageBox::Ok, 0 );
        return;
    }

    QString pwd = ui->lineEdit_Pwd->text();

    if(pwd.isEmpty())
    {
        QMessageBox::critical(0 ,"提示" , "请填写密码", QMessageBox::Ok,  0 );
        return;
    }

    QString url = "xfreerdp /u:" + userName + " /p:" + pwd + " /d:src /w:1366 /h:768 /v:61.184.241.30:25788 /cert-ignore -sec-nla";
    system((char*)url.toLatin1().data());
}
