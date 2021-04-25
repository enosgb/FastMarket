#include "window_gerenciarestoque.h"
#include "ui_window_gerenciarestoque.h"
#include <QMessageBox>
#include <QtSql>
#include "funcoes_globais.h"

window_gerenciarEstoque::window_gerenciarEstoque(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window_gerenciarEstoque)
{
    ui->setupUi(this);

    if(!con.abrir()){
        QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
    }else{
        QSqlQuery query;
        query.prepare("select * from tb_produtos");
        if(query.exec()){

        }else{
            QMessageBox::warning(this,"ERRO","Erro ao listar produtos");
        }
    }
    ui->tw_geProdutos->setColumnCount(2);
    ui->tb_gerenciarProdutos->setCurrentIndex(0);
}

window_gerenciarEstoque::~window_gerenciarEstoque()
{
    delete ui;
    con.fechar();
}


void window_gerenciarEstoque::on_btn_limpar_clicked()
{
    ui->txt_codigoProduto->clear();
    ui->txt_descricaoProduto->clear();
    ui->txt_fornecedor->clear();
    ui->txt_qtdEstoque->clear();
    ui->txt_valorCusto->clear();
    ui->txt_valorVenda->clear();
    ui->txt_codigoProduto->setFocus();
}

void window_gerenciarEstoque::on_btn_gravarProduto_clicked()
{

   QString aux;
   int codigoProduto=ui->txt_codigoProduto->text().toInt();
   QString descricaoProduto=ui->txt_descricaoProduto->text();
   int fornecedor=ui->txt_fornecedor->text().toInt();
   int qtdEstoque=ui->txt_qtdEstoque->text().toInt();

   aux=ui->txt_valorCusto->text();
   std::replace(aux.begin(),aux.end(),',','.');
   double valorCusto=aux.toDouble();

   aux=ui->txt_valorVenda->text();
   std::replace(aux.begin(),aux.end(),',','.');
   double valorVenda=aux.toDouble();

   QSqlQuery query;
   query.prepare("insert into tb_produtos (id_produto,produto,id_fornecedor,qtd_estoque,valor_compra,valor_venda) values"
                "("+QString::number(codigoProduto)+",'"+descricaoProduto+"',"+QString::number(fornecedor)+""
                ","+QString::number(qtdEstoque)+","+QString::number(valorCusto)+","+QString::number(valorVenda)+")");
   if(!query.exec()){
        QMessageBox::warning(this,"ERRO","Erro ao inserir produto!");
   }else{
         QMessageBox::information(this,"AVISO","Produto inserido com sucesso!");
         ui->txt_codigoProduto->clear();
         ui->txt_descricaoProduto->clear();
         ui->txt_fornecedor->clear();
         ui->txt_qtdEstoque->clear();
         ui->txt_valorCusto->clear();
         ui->txt_valorVenda->clear();
         ui->txt_codigoProduto->setFocus();
        }
    }


void window_gerenciarEstoque::on_tb_gerenciarProdutos_currentChanged(int index)
{
    if(index==1){
        funcoes_globais::removerLinhas(ui->tw_geProdutos);
        int linhas=0;
        QSqlQuery query;
        query.prepare("select id_produto,produto from tb_produtos order by id_produto");
        if(query.exec()){
            while (query.next()) {
                ui->tw_geProdutos->insertRow(linhas);
                ui->tw_geProdutos->setItem(linhas,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tw_geProdutos->setItem(linhas,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tw_geProdutos->setRowHeight(linhas,20);
                linhas++;
            }
            ui->tw_geProdutos->setColumnWidth(0,150);
            ui->tw_geProdutos->setColumnWidth(1,230);
            QStringList cabecalhos={"Código","Produto"};
            ui->tw_geProdutos->setHorizontalHeaderLabels(cabecalhos);
            ui->tw_geProdutos->setStyleSheet("QTableView {select-background-color:blue}");
            ui->tw_geProdutos->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_geProdutos->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_geProdutos->verticalHeader()->setVisible(false);
        }else{
            QMessageBox::warning(this,"ERRO","Erro ao listar produtos!");
        }
    }
}

void window_gerenciarEstoque::on_tw_geProdutos_itemSelectionChanged()
{
    int id=ui->tw_geProdutos->item(ui->tw_geProdutos->currentRow(),0)->text().toInt();

    QSqlQuery query;
    query.prepare("select * from tb_produtos where id_produto=+"+QString::number(id));
    if(query.exec()){
        query.first();
        ui->txt_geProduto->setText(query.value(0).toString());
        ui->txt_geDescricaoProduto->setText(query.value(1).toString());
        ui->txt_geFornecedor->setText(query.value(2).toString());
        ui->txt_geQuantidade->setText(query.value(3).toString());
        ui->txt_geValorCusto->setText(query.value(4).toString());
        ui->txt_geValorVenda->setText(query.value(5).toString());
    }
}

void window_gerenciarEstoque::on_btn_geGravar_clicked()
{
    if(ui->txt_geProduto->text()==""){
        QMessageBox::warning(this,"ERRO","É necessario selecionar um item!");
    }else{
        int id=ui->tw_geProdutos->item(ui->tw_geProdutos->currentRow(),0)->text().toInt();
        QString aux;
        QString produto=ui->txt_geDescricaoProduto->text();
        int fornecedor=ui->txt_geFornecedor->text().toInt();
        int quantidade=ui->txt_geQuantidade->text().toInt();

        aux=ui->txt_geValorCusto->text();
        std::replace(aux.begin(),aux.end(),',','.');
        double valorCusto=aux.toDouble();

        aux=ui->txt_geValorVenda->text();
        std::replace(aux.begin(),aux.end(),',','.');
        double valorVenda=aux.toDouble();

        QSqlQuery query;
        query.prepare("update tb_produtos set id_produto="+QString::number(id)+",produto='"+produto+"'"
                      ", id_fornecedor="+QString::number(fornecedor)+",qtd_estoque="+QString::number(quantidade)+""
                      ",valor_compra="+QString::number(valorCusto)+",valor_venda="+QString::number(valorVenda)+""
                      " where id_produto="+QString::number(id));
        if(query.exec()){
            int linha=ui->tw_geProdutos->currentRow();
            ui->tw_geProdutos->item(linha,0)->setText(ui->txt_geProduto->text());
            ui->tw_geProdutos->item(linha,1)->setText(produto);
            QMessageBox::information(this,"Atualizado","Protuto alterado com sucesso.");

       }else{
            QMessageBox::warning(this,"ERRO","Erro ao atualizar produto!");
       }
    }
}

void window_gerenciarEstoque::on_btn_geExcluir_clicked()
{
    if(ui->txt_geProduto->text()==""){
        QMessageBox::warning(this,"ERRO","É necessario selecionar um item!");
    }else{
        QMessageBox::StandardButton opt=QMessageBox::question(this,"Excluir","Dejesa excluir o produto selecionado?",QMessageBox::Yes|QMessageBox::No);
        if(opt==QMessageBox::Yes){
            int linha=ui->tw_geProdutos->currentRow();
            int id=ui->tw_geProdutos->item(linha,0)->text().toInt();
            QSqlQuery query;
            query.prepare("delete from tb_produtos where id_produto="+QString::number(id));
            if(query.exec()){
                ui->tw_geProdutos->removeRow(linha);
                QMessageBox::information(this,"Excluido","Produto excluido com sucesso!");
            }else{
                QMessageBox::warning(this,"ERRO","Erro ao excluir produto!");
        }
       }
    }
}

void window_gerenciarEstoque::on_btn_geBuscar_clicked()
{
    QString pesquisa;
    funcoes_globais::removerLinhas(ui->tw_geProdutos);
    if(ui->txt_gePesquisa->text()=="") {
        if(ui->rb_geCodigo->isChecked()){
            pesquisa="select id_produto,produto from tb_produtos order by id_produto";
        }else{
            pesquisa="select id_produto,produto from tb_produtos order by produto";
        }
    }else{
        if(ui->rb_geCodigo->isChecked()){
            pesquisa="select id_produto,produto from tb_produtos where id_produto="+ui->txt_gePesquisa->text()+" order by id_produto";
        }else{
            pesquisa="select id_produto,produto from tb_produtos where produto like '%"+ui->txt_gePesquisa->text()+"%'order by produto";
        }
    }

    int linhas=0;
    QSqlQuery query;
    query.prepare(pesquisa);
    if(query.exec()){
        while(query.next()){
            ui->tw_geProdutos->insertRow(linhas);
            ui->tw_geProdutos->setItem(linhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_geProdutos->setItem(linhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_geProdutos->setRowHeight(linhas,20);
            linhas++;
        }
    }else{
            QMessageBox::warning(this,"ERRO","Erro ao pesquisar!");
        }
    ui->txt_gePesquisa->clear();
    ui->txt_gePesquisa->setFocus();
}

