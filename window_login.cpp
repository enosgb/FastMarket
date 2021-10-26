#include "window_login.h"
#include "ui_window_login.h"
#include "QMessageBox"
#include "mainwindow.h"
#include "variaveis_globais.h"

window_login::window_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window_login)
{
    ui->setupUi(this);

    login=false;
}

window_login::~window_login()
{
    delete ui;
}

void window_login::on_btn_login_clicked()
{
    if(!con.abrir()){
        QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados");
    }else{
        QString username,senha;
        username=ui->txt_username->text();
        senha=ui->txt_senha->text();
        QSqlQuery query;
        query.prepare("select * from tb_usuarios where username='"+username+"' and senha_user='"+senha+"'");
        if(query.exec()){
            query.first();
            if(query.value(2).toString()!=""){
                variaveis_globais::login=true;
                variaveis_globais::username=query.value(2).toString();
                variaveis_globais::nome_user=query.value(1).toString();
                variaveis_globais::userId=query.value(0).toInt();
                variaveis_globais::acceso_user=query.value(5).toString();
                con.fechar();
                close();
            }else{
                QMessageBox::warning(this,"ERRO","Usuário ou senha INCORRETOS!");
            }
        }else{
            QMessageBox::warning(this,"ERRO","Falha no login!");
        }
    }
    con.fechar();
}

void window_login::on_btn_senha_clicked()
{
    login=false;
    close();
}

