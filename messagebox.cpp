#include "messagebox.h"
#include "ui_messagebox.h"


MessageBox::MessageBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MessageBox)
{
    ui->setupUi(this);
}

MessageBox::~MessageBox()
{
    delete ui;
}

void MessageBox::ChangeTips(int type)
{
    if(1 == type)
    {
        ui->widget->setStyleSheet("background-image: url(:/message_user.png);");
    }
    else if(2 == type)
    {
        ui->widget->setStyleSheet("background-image: url(:/message_pwd.png);");

    }
}

void MessageBox::on_pushButton_clicked()
{
    close();
}

void MessageBox::on_mainWindow_Close_clicked()
{
    close();
}
