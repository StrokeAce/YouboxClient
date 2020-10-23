#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MessageBox; }
QT_END_NAMESPACE

class MessageBox : public QWidget
{
    Q_OBJECT
public:
    MessageBox(QWidget *parent = nullptr);
    ~MessageBox();
    void ChangeTips(int type);

private slots:
    void on_pushButton_clicked();

    void on_mainWindow_Close_clicked();

private:
    Ui::MessageBox *ui;
};

#endif // MESSAGEBOX_H
