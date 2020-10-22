#include "agreement.h"
#include "ui_agreement.h"

Agreement::Agreement(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Agreement)
{
    ui->setupUi(this);
    //ui->textEdit_Agreement->setText("法律声明 \n兴和云提醒您：本网站（singlecloud.cc）由兴和云网科技股份有限公司（简称“兴和云”）建设、运营和维护。在进入本网站阅读任何内容、进行用户注册、下载或使用本网站提供的任何资料及使用本网站提供的各项服务前，请您务必仔细阅读并透彻理解本声明。您的使用行为将被视为对本声明全部内容的认可。");
}

Agreement::~Agreement()
{
    delete ui;
}

void Agreement::on_agreement_Close_clicked()
{
    close();
}
