#include "mainwindow.h"
#include <QDesktopWidget>
#include <QVariant>
#include <QSettings>
#include <QFile>
#include <QDebug>
#include "ui_mainwindow.h"

#define DEF_GET_STATE(bCheck) (bCheck ? Qt::Checked : Qt::Unchecked)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_canLogin(false)
{
    ui->setupUi(this);
    m_move = false;
    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键点击时.
    if (event->button() == Qt::LeftButton)
    {
        m_move = true;
        //记录鼠标的世界坐标.
        m_startPoint = event->globalPos();
        //记录窗体的世界坐标.
        m_windowPoint = this->frameGeometry().topLeft();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可.
        this->move(m_windowPoint + relativePos );
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
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
    QString user = setting.value("user").toString();
    QString pwd = setting.value("pwd").toString();
    if(m_bSavePwd)
    {
        ui->lineEdit_UserName->setText(Decip(user));
        ui->lineEdit_Pwd->setText(Decip(pwd));
    }
}

void MainWindow::WriteConfig()
{
    QString path = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings setting(path, QSettings::IniFormat);
    setting.setValue("save_pwd", m_bSavePwd);
    setting.setValue("agree", m_bAgree);

    if(m_bSavePwd)
    {
        setting.setValue("user", Encry(ui->lineEdit_UserName->text()));
        setting.setValue("pwd", Encry(ui->lineEdit_Pwd->text()));
    }
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
                Info in;
                in.ip = line.section("=", 1, 1);
                in.region = line.section("=", 2, 2);
                m_mapIpList.insert(name,in);
            }
        }
    }

    for(QMap<QString,Info>::ConstIterator ite=m_mapIpList.constBegin(); ite!=m_mapIpList.constEnd(); ++ite)
                ui->comboBox_ip->addItem(ite.key());
}

QString MainWindow::Encry(QString pwd)
{
    QByteArray baPw = pwd.toUtf8();
    for (int i = 0;i<baPw.size();i++)
    {
        baPw[i] = baPw[i]+66;//加密User1的密码
    }
    return baPw;
}

QString MainWindow::Decip(QString pwd)
{
    QByteArray baPw = pwd.toUtf8();
    for (int i = 0;i<baPw.size();i++)
    {
        baPw[i] = baPw[i]-66;//解密User1的密码
    }
    return baPw;
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
        m_box.move(geometry().x() + 37, geometry().y() + 200);//窗口居中
        m_box.setWindowModality(Qt::ApplicationModal);
        m_box.setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
        m_box.ChangeTips(1);
        m_box.show();
        return;
    }

    QString pwd = ui->lineEdit_Pwd->text();

    if(pwd.isEmpty())
    {
        m_box.move(geometry().x() + 37, geometry().y() + 200);//窗口居中
        m_box.setWindowModality(Qt::ApplicationModal);
        m_box.setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
        m_box.ChangeTips(2);
        m_box.show();
        return;
    }

    QString key = ui->comboBox_ip->currentText();

	if(key.isEmpty())
    {
		return;
	}

	QString ip = "";
    QString region = "";
    QMap<QString,Info>::Iterator iter;
    iter = m_mapIpList.find(key);
    if(iter != m_mapIpList.end())
    {
        ip = iter.value().ip;
        region = iter.value().region;
    }

    if(ip.isEmpty() || region.isEmpty())
	{
		return;
	}
    
    int width = QApplication::desktop()->width();
    int height = QApplication::desktop()->height() - 80;//远程界面的高减少80是为了防止本地任务栏会遮挡远程的任务栏

    QString execPath = QCoreApplication::applicationDirPath();

    QString cmd;
    cmd = execPath + "/freerdp /u:" + userName + " /p:" + pwd + " /d:" + region+ " /w:" + QString::number(width) + " /h:" + QString::number(height) + " /v:" + ip + " /cert-ignore -sec-nla";
    system((char*)(cmd.toLatin1().data()));
}

void MainWindow::on_checkBox_Agree_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->button_Login->setEnabled(true);
        ui->button_Login->setStyleSheet("background-image: url(:/login.png);");
        m_bAgree = true;
    }
    else
    {
         ui->button_Login->setEnabled(false);
         ui->button_Login->setStyleSheet("background-image: url(:/unlogin.png);");
         m_bAgree = false;
    }
}

void MainWindow::on_pushButton_clicked()
{
    m_reg.move(geometry().x() + 40, geometry().y() + 140);//窗口居中
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
    int rightX = geometry().x() - 335 + 1000;
    int leftX = QApplication::desktop()->width() > rightX ? (geometry().x() - 335) : (QApplication::desktop()->width() - 1000);
    m_agree.move(leftX, geometry().y());//窗口居中
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
