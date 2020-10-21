#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qmap.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

private:
    Ui::MainWindow *ui;
    bool m_canLogin;
	QMap<QString,QString> m_mapConfig;
};
#endif // MAINWINDOW_H
