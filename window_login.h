#ifndef WINDOW_LOGIN_H
#define WINDOW_LOGIN_H

#include <QDialog>
#include "connect.h"

namespace Ui {
class window_login;
}

class window_login : public QDialog
{
    Q_OBJECT

public:
    explicit window_login(QWidget *parent = nullptr);
    ~window_login();
    bool login;
    Conexao con;
    QString nome,acesso;
    int Id;

private slots:
    void on_btn_login_clicked();

    void on_btn_senha_clicked();

private:
    Ui::window_login *ui;
};

#endif // WINDOW_LOGIN_H
