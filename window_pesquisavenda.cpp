#include "window_pesquisavenda.h"
#include "ui_window_pesquisavenda.h"

//QString window_pesquisaVenda::retIdVenda; exibe erro na copolação após descomentar.
//bool window_pesquisaVenda::statusPesquisa; exibe erro na copolação após descomentar.

window_pesquisaVenda::window_pesquisaVenda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window_pesquisaVenda)
{
    ui->setupUi(this);

    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
        }
    }
    ui->tw_PeProdutos->setColumnCount(2);
    ui->tw_PeProdutos->setColumnWidth(0,150);
    ui->tw_PeProdutos->setColumnWidth(1,250);
    QStringList cabecalho={"ID","Produto"};
    ui->tw_PeProdutos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_PeProdutos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_PeProdutos->setHorizontalHeaderLabels(cabecalho);
    ui->tw_PeProdutos->verticalHeader()->setVisible(false);

}

window_pesquisaVenda::~window_pesquisaVenda()
{
    delete ui;
}

void window_pesquisaVenda::on_btn_PeBuscar_clicked()
{
    QString pesquisa;
    funcoes_globais::removerLinhas(ui->tw_PeProdutos);
    if(ui->txt_PePesquisa->text()=="") {
        if(ui->rb_PeCodigo->isChecked()){
            pesquisa="select id_produto,produto from tb_produtos order by id_produto";
        }else{
            pesquisa="select id_produto,produto from tb_produtos order by produto";
        }
    }else{
        if(ui->rb_PeCodigo->isChecked()){
            pesquisa="select id_produto,produto from tb_produtos where id_produto="+ui->txt_PePesquisa->text()+" order by id_produto";
        }else{
            pesquisa="select id_produto,produto from tb_produtos where produto like '%"+ui->txt_PePesquisa->text()+"%'order by produto";
        }
    }

    int linhas=0;
    QSqlQuery query;
    query.prepare(pesquisa);
    if(query.exec()){
        while(query.next()){
            ui->tw_PeProdutos->insertRow(linhas);
            ui->tw_PeProdutos->setItem(linhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_PeProdutos->setItem(linhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_PeProdutos->setRowHeight(linhas,20);
            linhas++;
        }
    }else{
            QMessageBox::warning(this,"ERRO","Erro ao pesquisar!");
        }
    ui->txt_PePesquisa->clear();
    ui->txt_PePesquisa->setFocus();
}

void window_pesquisaVenda::on_tw_PeProdutos_itemSelectionChanged()
{
    window_pesquisaVenda::retIdVenda=ui->tw_PeProdutos->item(ui->tw_PeProdutos->currentRow(),0)->text();
}

void window_pesquisaVenda::on_btn_PeSelecionarItem_clicked()
{
  window_pesquisaVenda::retIdVenda=ui->tw_PeProdutos->item(ui->tw_PeProdutos->currentRow(),0)->text();
  close();
}
