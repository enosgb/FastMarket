#include "window_gerenciarusuarios.h"
#include "ui_window_gerenciarusuarios.h"

#include <QMessageBox>
#include <QtSql>
#include "funcoes_globais.h"


window_gerenciarUsuarios::window_gerenciarUsuarios(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window_gerenciarUsuarios)
{
    ui->setupUi(this);

    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
        }
    }
    ui->cb_acessoNovoUsuario->addItem("Administrador");
    ui->cb_acessoNovoUsuario->addItem("Comum");
    ui->cb_geAcessoUsuario->addItem("Administrador");
    ui->cb_geAcessoUsuario->addItem("Comum");
    ui->txt_nomeNovoUsuario->setFocus();

    ui->tabWidget->setCurrentIndex(0);

    ui->tw_geUsuarios->setColumnCount(2);
    ui->tw_geUsuarios->setColumnWidth(0,50);
    ui->tw_geUsuarios->setColumnWidth(1,235);
    QStringList cabecalhos={"ID","Nome"};
    ui->tw_geUsuarios->setHorizontalHeaderLabels(cabecalhos);
    ui->tw_geUsuarios->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_geUsuarios->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_geUsuarios->verticalHeader()->setVisible(false);

}

window_gerenciarUsuarios::~window_gerenciarUsuarios()
{
    delete ui;
}

void window_gerenciarUsuarios::on_btn_novoUsuario_clicked()
{
    ui->txt_nomeNovoUsuario->clear();
    ui->txt_senhaNovoUsurio->clear();
    ui->txt_telefoneNovoUsuario->clear();
    ui->txt_usernameNovoUsuario->clear();
    ui->cb_acessoNovoUsuario->setCurrentIndex(0);
    ui->txt_nomeNovoUsuario->setFocus();
}

void window_gerenciarUsuarios::on_btn_gravaNovoUsuario_clicked()
{
    QString nome=ui->txt_nomeNovoUsuario->text();
    QString username=ui->txt_usernameNovoUsuario->text();
    QString senha=ui->txt_senhaNovoUsurio->text();
    QString telefone=ui->txt_telefoneNovoUsuario->text();
    QString acesso=ui->cb_acessoNovoUsuario->currentText();

    QSqlQuery query;
    query.prepare("insert into tb_usuarios (nome_user,username,senha_user,fone_user,acesso_user) values"
                 "('"+nome+"','"+username+"','"+senha+"','"+telefone+"','"+acesso+"')");
    if(!query.exec()){
         QMessageBox::critical(this,"ERRO","Erro ao inserir Novo usuário!");
    }else{
          QMessageBox::information(this,"Gravar","Usuario adicionado com sucesso!");
          ui->txt_nomeNovoUsuario->clear();
          ui->txt_usernameNovoUsuario->clear();
          ui->txt_senhaNovoUsurio->clear();
          ui->txt_telefoneNovoUsuario->clear();
          ui->cb_acessoNovoUsuario->setCurrentIndex(0);
          ui->txt_nomeNovoUsuario->setFocus();
         }
}

void window_gerenciarUsuarios::on_tabWidget_currentChanged(int index)
{
    if(index==1){
        funcoes_globais::removerLinhas(ui->tw_geUsuarios);
        int linhas=0;
        QSqlQuery query;
        query.prepare("select id_usuario,nome_user from tb_usuarios order by id_usuario");
        if(query.exec()){
            while (query.next()) {
                ui->tw_geUsuarios->insertRow(linhas);
                ui->tw_geUsuarios->setItem(linhas,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tw_geUsuarios->setItem(linhas,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tw_geUsuarios->setRowHeight(linhas,20);
                linhas++;
            }
        }else{
            QMessageBox::warning(this,"ERRO","Erro ao listar Usuário!");
        }
    }
}

void window_gerenciarUsuarios::on_tw_geUsuarios_itemSelectionChanged()
{
    int id=ui->tw_geUsuarios->item(ui->tw_geUsuarios->currentRow(),0)->text().toInt();

    QSqlQuery query;
    query.prepare("select * from tb_usuarios where id_usuario=+"+QString::number(id));
    if(query.exec()){
        query.first();
        ui->txt_geNomeUsuario->setText(query.value(1).toString());
        ui->txt_geUserName->setText(query.value(2).toString());
        ui->txt_geSenhaUsuario->setText(query.value(3).toString());
        ui->txt_geTelefoneUsuario->setText(query.value(4).toString());
        ui->cb_geAcessoUsuario->setCurrentText(query.value(5).toString());
    }
}

void window_gerenciarUsuarios::on_btn_geBuscarUsuario_clicked()
{
    QString pesquisa;
    funcoes_globais::removerLinhas(ui->tw_geUsuarios);
    if(ui->txt_gePesquisarUsuario->text()=="") {
        if(ui->rb_geFiltroIdUsuario->isChecked()){
            pesquisa="select id_usuario,nome_user from tb_usuarios order by id_usuario";
        }else{
            pesquisa="select id_usuario,nome_user from tb_usuarios order by nome_user";
        }
    }else{
        if(ui->rb_geFiltroIdUsuario->isChecked()){
            pesquisa="select id_usuario,nome_user from tb_usuarios where id_usuario="+ui->txt_gePesquisarUsuario->text()+" order by id_usuario";
        }else{
            pesquisa="select id_usuario,nome_user from tb_usuarios where nome_user like '%"+ui->txt_gePesquisarUsuario->text()+"%'order by nome_user";
        }
    }

    int linhas=0;
    QSqlQuery query;
    query.prepare(pesquisa);
    if(query.exec()){
        while (query.next()) {
            ui->tw_geUsuarios->insertRow(linhas);
            ui->tw_geUsuarios->setItem(linhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_geUsuarios->setItem(linhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_geUsuarios->setRowHeight(linhas,20);
            linhas++;
        }
    }else{
            QMessageBox::warning(this,"ERRO","Erro ao pesquisar!");
        }
    ui->txt_gePesquisarUsuario->clear();
    ui->txt_gePesquisarUsuario->setFocus();
}

void window_gerenciarUsuarios::on_bnt_geGravarUsuario_clicked()
{
    if(ui->tw_geUsuarios->currentRow()==-1){
        QMessageBox::warning(this,"Erro","É necessário selecionar um usuário!");
        return;
    }

    QString id=ui->tw_geUsuarios->item(ui->tw_geUsuarios->currentRow(),0)->text();
    QSqlQuery query;
    QString nome=ui->txt_geNomeUsuario->text();
    QString username=ui->txt_geUserName->text();
    QString senha=ui->txt_geSenhaUsuario->text();
    QString telefone=ui->txt_geTelefoneUsuario->text();
    QString acesso=ui->cb_geAcessoUsuario->currentText();
    query.prepare("update tb_usuarios set nome_user='"+nome+"', username='"+username+"',senha_user='"+senha+"',fone_user='"+telefone+"',acesso_user='"+acesso+"' where id_usuario="+id);
    if(query.exec()){
        int linha=ui->tw_geUsuarios->currentRow();
        ui->tw_geUsuarios->item(linha,1)->setText(nome);
        QMessageBox::information(this,"Atualizado","Usuário alterado com sucesso.");

   }else{
        QMessageBox::warning(this,"ERRO","Erro ao atualizar Usuárior!");
   }
}

void window_gerenciarUsuarios::on_btn_geExcluirUsuario_clicked()
{

    if(ui->tw_geUsuarios->currentRow()==-1){
        QMessageBox::warning(this,"Erro","É necessário selecionar um usuário!");
        return;
    }else{
        QMessageBox::StandardButton opt=QMessageBox::question(this,"Excluir","Dejesa excluir o usuário selecionado?",QMessageBox::Yes|QMessageBox::No);
        if(opt==QMessageBox::Yes){
            int linha=ui->tw_geUsuarios->currentRow();
            QString id=ui->tw_geUsuarios->item(linha,0)->text();
            QSqlQuery query;
            query.prepare("delete from tb_usuarios where id_usuario="+id);
            if(query.exec()){
                ui->tw_geUsuarios->removeRow(linha);
                QMessageBox::information(this,"Excluido","Usuário excluido com sucesso!");
            }else{
                QMessageBox::warning(this,"ERRO","Erro ao excluir usuário!");
        }
       }
    }
}
