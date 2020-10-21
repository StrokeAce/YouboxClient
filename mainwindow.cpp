#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDesktopWidget> 
#include <fstream> 
#include <string>

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

void MainWindow::on_button_Login_clicked()
{
	if(!ui->checkBox_2->isChecked())
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

	QString key = ui->comboBox->currentText();

	if(key.isEmpty())
	{
		QMessageBox::warning(NULL, "提示", "软件异常!",QMessageBox::Ok);
		return;
	}

	QString ip = "";
	QMap<QString,QString>::Iterator iter;
	iter = m_mapConfig.find(key);
	if(iter != m_mapConfig.end())
		ip = iter.value();

	if(ip.isEmpty())
	{
		QMessageBox::warning(NULL, "提示", "软件异常!",QMessageBox::Ok);
		return;
	}
    
    int width = QApplication::desktop()->width() - 80;//远程界面的高减少80是为了防止本地任务栏会遮挡远程的任务栏
    int height = QApplication::desktop()->height();

    QString cmd;
    cmd = "/home/youboxclient/freerdp /u:" + userName + " /p:" + pwd + " /d:src /w:" + QString::number(width) + " /h:" + QString::number(height) + " /v:" + ip + " /cert-ignore -sec-nla";
    
	system((char*)(cmd.toLatin1().data()));
}

void MainWindow::ReadConfig()
{
	std::ifstream file("/home/youboxclient/config.ini");
 
	std::string line = "";
	std::getline( file, line );
  
    while( line.length() > 0 )  
    {
		int delimPos = line.find("=");
		std::string key = line.substr( 0, delimPos );
		line.replace( 0, delimPos+1, "" );
		m_mapConfig.insert(QString::fromStdString(key),QString::fromStdString(line));		
		line = "";
        std::getline( file, line );
	}        
}

void MainWindow::Init()
{
	ReadConfig();

	for(QMap<QString,QString>::ConstIterator ite=m_mapConfig.constBegin(); ite!=m_mapConfig.constEnd(); ++ite)
		ui->comboBox->addItem(ite.key());
}
