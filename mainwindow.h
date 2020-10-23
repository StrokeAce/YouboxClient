#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "register.h"
#include "agreement.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Register;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_Login_clicked();
    void ReadConfig();
    void WriteConfig();
    void ReadData();
	void Init(); 

    void on_checkBox_Agree_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_mainWindow_Close_clicked();

    void on_button_Turn_Agreement_clicked();

    void on_checkBox_Pwd_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    bool m_canLogin;
    QMap<QString,QString> m_mapIpList;
    Register m_reg;
    Agreement m_agree;
    bool m_bSavePwd;
    bool m_bAgree;
};
#endif // MAINWINDOW_H
