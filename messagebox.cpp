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
        ui->label->setText("温馨提示：请填写账号");
    }
    else if(2 == type)
    {
        ui->label->setText("温馨提示：请填写密码");
    }
    else if(3 == type)
    {
       ui->label->setText("温馨提示：登录无响应,请检查网络");
    }
    else if(4 == type)
    {
        ui->label->setText("温馨提示：登录异常");
    }
    else if(5 == type)
    {
        ui->label->setText("温馨提示：账号错误或不存在");
    }
    else if(6 == type)
    {
        ui->label->setText("温馨提示：密码错误");
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
