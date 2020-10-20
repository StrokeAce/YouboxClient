#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDesktopWidget>

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
    
    int width = QApplication::desktop()->width();
    int height = QApplication::desktop()->height();

    char cmd[1024] = {0};
    sprintf(cmd, "/home/youboxclient/freerdp /u:%s /p:%s /d:src /w:%d /h:%d /v:61.184.241.30:25788 /cert-ignore -sec-nla",
    (char*)userName.toLatin1().data(),(char*)pwd.toLatin1().data(),width,height);
    system(cmd);
}
