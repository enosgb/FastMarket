#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "window_login.h"
#include "window_novavenda.h"
#include "window_gerenciarusuarios.h"
#include "window_gerenciarestoque.h"
#include "window_gerenciarvenda.h"
#include "variaveis_globais.h"

int variaveis_globais::userId;
QString variaveis_globais::username;
QString variaveis_globais::nome_user;
QString variaveis_globais::acceso_user;
bool variaveis_globais::login;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    variaveis_globais::login=false;
    cadeado_fechado.addFile(":/imagens/imagens/cadeado_fechado.png");
    cadeado_aberto.addFile(":/imagens/imagens/cadeado_aberto.png");

    ui->btn_bloqueio->setText("");
    ui->btn_bloqueio->setIcon(cadeado_fechado);
    ui->statusbar->addWidget(ui->btn_bloqueio);
    ui->statusbar->addWidget(ui->lb_nome);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_bloqueio_clicked()
{
    if(!variaveis_globais::login){
       window_login wlogin;
       wlogin.exec();
       if(variaveis_globais::login){
           ui->btn_bloqueio->setIcon(cadeado_aberto);
           ui->lb_nome->setText(variaveis_globais::nome_user);
       }

    }else{
        variaveis_globais::login=false;
        ui->btn_bloqueio->setIcon(cadeado_fechado);
        ui->lb_nome->setText("Sem usuário.");
    }
}

void MainWindow::on_btn_novaVenda_clicked()
{
    if(variaveis_globais::login){
        window_novaVenda wnovaVenda;
        wnovaVenda.exec();
    }else{
        QMessageBox::warning(this,"Atenção","Você precisa logar primeiro!");
    }

}

void MainWindow::on_actionEstoque_triggered()
{
    if(variaveis_globais::login){
        if(variaveis_globais::acceso_user=="1"){
            window_gerenciarEstoque wgerenciarEstoque;
            wgerenciarEstoque.exec();
        }else {
            QMessageBox::warning(this,"AVISO","Acesso não autorizado para este usuário!");
        }

    }else{
        QMessageBox::warning(this,"Atenção","Você precisa logar primeiro!");
    }


}

void MainWindow::on_actionUsu_rios_triggered()
{
    if(variaveis_globais::login){
        if(variaveis_globais::acceso_user=="1"){
           window_gerenciarUsuarios wgerenciarUsuarios;
           wgerenciarUsuarios.exec();
        }else {
            QMessageBox::warning(this,"AVISO","Acesso não autorizado para este usuário!");
        }

    }else{
        QMessageBox::warning(this,"Atenção","Você precisa logar primeiro!");
    }

}

void MainWindow::on_actionVendas_triggered()
{
    if(variaveis_globais::login){
        if(variaveis_globais::acceso_user=="1"){
            window_gerenciarVenda wgerenciarVenda;
            wgerenciarVenda.exec();
        }else {
            QMessageBox::warning(this,"AVISO","Acesso não autorizado para este usuário!");
        }

    }else{
        QMessageBox::warning(this,"Atenção","Você precisa logar primeiro!");
    }
}
