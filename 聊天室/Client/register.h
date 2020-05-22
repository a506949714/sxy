#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include "network.h"

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

signals:
    void backToLogin();

private slots:
    void on_confirmBtn_clicked();
    void receiveSlot(const QByteArray& data);
    void on_backBtn_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
