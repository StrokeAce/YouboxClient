#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qmap.h>
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
	void Init();

    void on_checkBox_Agree_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_checkBox_Agree_clicked();

private:
    Ui::MainWindow *ui;
    bool m_canLogin;
    QMap<QString,QString> m_mapConfig;
    Register m_reg;
    Agreement m_agree;
};
#endif // MAINWINDOW_H
