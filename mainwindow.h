#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QMouseEvent>
#include <QtNetwork/QNetworkReply>
#include "register.h"
#include "agreement.h"
#include "messagebox.h"

struct Info
{
    QString ip;
    QString region;
};

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

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_button_Login_clicked();

    void on_checkBox_Agree_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_mainWindow_Close_clicked();

    void on_button_Turn_Agreement_clicked();

    void on_checkBox_Pwd_stateChanged(int arg1);

    void ReplyFinish(QNetworkReply *reply);

    void TimeOut();

private:
    void ReadConfig();
    void WriteConfig();
    void ReadData();
    void Init();
    void SendUrl(QString userName);
    void ShowBox(int tips);
    QString Encry(QString pwd);
    QString Decip(QString pwd);

private:
    Ui::MainWindow *ui;
    bool                m_canLogin;
    QMap<QString,Info>  m_mapIpList;
    Register            m_reg;
    Agreement           m_agree;
    MessageBox          m_box;
    bool                m_bSavePwd;
    bool                m_bAgree;
    bool                m_move;
    QPoint              m_startPoint;
    QPoint              m_windowPoint;
    bool                m_bInLogin;
};
#endif // MAINWINDOW_H
