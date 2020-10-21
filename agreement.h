#ifndef AGREEMENT_H
#define AGREEMENT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Agreement; }
QT_END_NAMESPACE

class Agreement : public QWidget
{
    Q_OBJECT
public:
    Agreement(QWidget *parent = nullptr);
    ~Agreement();

private:
    Ui::Agreement *ui;
};

#endif // AGREEMENT_H
