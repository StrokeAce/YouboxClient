#include "agreement.h"
#include "ui_agreement.h"
#include <QFile>

Agreement::Agreement(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Agreement)
{
    ui->setupUi(this);

    ReadData();
}

Agreement::~Agreement()
{
    delete ui;
}

void Agreement::on_agreement_Close_clicked()
{
    close();
}

void Agreement::ReadData()
{
    QString path = QCoreApplication::applicationDirPath() + "/agreement.ini";

    QFile file(path);
    bool isOK = file.open(QIODevice::ReadOnly);
    if(isOK == true)
    {
        while (file.atEnd() == false)
        {
            QString line = file.readLine();
            if(!line.isEmpty())
            {
                ui->textEdit_Agreement->append(line);
            }
        }
    }


    ui->textEdit_Agreement->moveCursor(QTextCursor::Start);
}
