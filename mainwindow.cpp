#include "mainwindow.h"
#include <QMessageBox>
#include <QDesktopWidget>
#include <QVariant>
#include <QSettings>
#include <QFile>
#include "ui_mainwindow.h"

#define DEF_GET_STATE(bCheck) (bCheck ? Qt::Checked : Qt::Unchecked)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_canLogin(false)
{
    ui->setupUi(this);
    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    ReadConfig();
    ReadData();

    ui->checkBox_Pwd->setCheckState(DEF_GET_STATE(m_bSavePwd));
    ui->checkBox_Agree->setCheckState(DEF_GET_STATE(m_bAgree));
}

void MainWindow::ReadConfig()
{
    QString path = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings setting(path, QSettings::IniFormat);
    m_bSavePwd = setting.value("save_pwd", false).toBool();
    m_bAgree = setting.value("agree", false).toBool();
}

void MainWindow::WriteConfig()
{
    QString path = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings setting(path, QSettings::IniFormat);
    setting.setValue("save_pwd", m_bSavePwd);
    setting.setValue("agree", m_bAgree);
}

void MainWindow::ReadData()
{
    QString path = QCoreApplication::applicationDirPath() + "/data.ini";

    QFile file(path);
    bool isOK = file.open(QIODevice::ReadOnly);
    if(isOK == true)
    {
        while (file.atEnd() == false)
        {
            QString line = file.readLine();
            if(!line.isEmpty())
            {
                QString name = line.section("=", 0, 0);
                QString ip = line.section("=", 1, 1);
                m_mapIpList.insert(name,ip);
                printf("%s,%s\n",name.toStdString().c_str(),ip.toStdString().c_str());
            }

        }
    }

    for(QMap<QString,QString>::ConstIterator ite=m_mapIpList.constBegin(); ite!=m_mapIpList.constEnd(); ++ite)
                ui->comboBox_ip->addItem(ite.key());
}

void MainWindow::on_button_Login_clicked()
{
    if(!ui->checkBox_Agree->isChecked())
    {
    	return;
    }
	
    QString userName = ui->lineEdit_UserName->text();

    if(userName.isEmpty())
    {
        QMessageBox::warning(NULL, "提示", "请填写账号!",QMessageBox::Ok);
        return;
    }

    QString pwd = ui->lineEdit_Pwd->text();

    if(pwd.isEmpty())
    {
        QMessageBox::warning(NULL, "提示", "请填写密码!",QMessageBox::Ok);
        return;
    }

        QString key = ui->comboBox_ip->currentText();

	if(key.isEmpty())
	{
		QMessageBox::warning(NULL, "提示", "软件异常!",QMessageBox::Ok);
		return;
	}

	QString ip = "";
	QMap<QString,QString>::Iterator iter;
    iter = m_mapIpList.find(key);
    if(iter != m_mapIpList.end())
		ip = iter.value();

	if(ip.isEmpty())
	{
		QMessageBox::warning(NULL, "提示", "软件异常!",QMessageBox::Ok);
		return;
	}
    
    int width = QApplication::desktop()->width() - 80;//远程界面的高减少80是为了防止本地任务栏会遮挡远程的任务栏
    int height = QApplication::desktop()->height();

    QString execPath = QCoreApplication::applicationDirPath();

    QString cmd;
    cmd = execPath + "/freerdp /u:" + userName + " /p:" + pwd + " /d:src /w:" + QString::number(width) + " /h:" + QString::number(height) + " /v:" + ip + " /cert-ignore -sec-nla";
    
	system((char*)(cmd.toLatin1().data()));
}

void MainWindow::on_checkBox_Agree_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->button_Login->setEnabled(true);
        m_bAgree = true;
    }
    else
    {
         ui->button_Login->setEnabled(false);
         m_bAgree = false;
    }
}

void MainWindow::on_pushButton_clicked()
{
    m_reg.move ((QApplication::desktop()->width() - m_reg.width())/2,(QApplication::desktop()->height() - m_reg.height())/2);//窗口居中
    m_reg.setWindowModality(Qt::ApplicationModal);
    m_reg.setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    m_reg.show();
}

void MainWindow::on_mainWindow_Close_clicked()
{
    WriteConfig();
    close();
}

void MainWindow::on_button_Turn_Agreement_clicked()
{
    m_agree.move ((QApplication::desktop()->width() - m_agree.width())/2,(QApplication::desktop()->height() - m_agree.height())/2);//窗口居中
    m_agree.setWindowModality(Qt::ApplicationModal);
    m_agree.setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    m_agree.show();
}

void MainWindow::on_checkBox_Pwd_stateChanged(int arg1)
{
    if(arg1)
    {
        m_bSavePwd = true;
    }
    else
    {
        m_bSavePwd = false;
    }
}
