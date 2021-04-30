#include "window_novavenda.h"
#include "ui_window_novavenda.h"
#include <QMessageBox>
#include "window_editar_produto_venda.h"
#include "mainwindow.h"
#include "variaveis_globais.h"
#include "funcoes_globais.h"


QString window_pesquisaVenda::retIdVenda;


QString window_novaVenda::global_idProduto;
QString window_novaVenda::global_descricaoProduto;
QString window_novaVenda::global_quantidade;
QString window_novaVenda::global_valorUnitario;
QString window_novaVenda::global_valorTotal;
bool window_novaVenda::editar;
bool variaveis_globais::statusPagamento;

window_novaVenda::window_novaVenda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window_novaVenda)
{
    ui->setupUi(this);

    //security
    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
        }
    }

    ui->tw_veProdutos->setColumnCount(5);
    ui->tw_veProdutos->setColumnWidth(0,100);
    ui->tw_veProdutos->setColumnWidth(1,290);
    ui->tw_veProdutos->setColumnWidth(2,100);
    ui->tw_veProdutos->setColumnWidth(3,100);
    ui->tw_veProdutos->setColumnWidth(4,100);
    QStringList cabecalhos={"Código","Produto","Valor Un.","Qtd","Total"};
    ui->tw_veProdutos->setHorizontalHeaderLabels(cabecalhos);
    ui->tw_veProdutos->setStyleSheet("QTableView{selection-background-color:blue;}");
    ui->tw_veProdutos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_veProdutos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_veProdutos->verticalHeader()->setVisible(false);


    ui->txt_veCodigo->setFocus();
    linhas = 0;
}

window_novaVenda::~window_novaVenda()
{
    delete ui;
}

void window_novaVenda::on_txt_veCodigo_returnPressed()
{
    window_pesquisaVenda::retIdVenda = ui->txt_veCodigo->text();
    QSqlQuery query;
    QString id=window_pesquisaVenda::retIdVenda;
    double valorTotal;
    query.prepare("select id_produto,produto,valor_venda from tb_produtos where id_produto="+id);
    if(query.exec()){
        query.first();
        if(query.value(0).toString()!=""){
            ui->tw_veProdutos->insertRow(linhas);
            ui->tw_veProdutos->setItem(linhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_veProdutos->setItem(linhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_veProdutos->setItem(linhas,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tw_veProdutos->setItem(linhas,3,new QTableWidgetItem(ui->txt_veQuantidade->text()));
            valorTotal = ui->txt_veQuantidade->text().toDouble()*query.value(2).toDouble();
            ui->tw_veProdutos->setItem(linhas,4,new QTableWidgetItem(QString::number(valorTotal)));
            ui->tw_veProdutos->setRowHeight(linhas,20);
            linhas++;
            ui->lb_veTotalVenda->setText("R$ "+QString::number(calcularTotal(ui->tw_veProdutos,4)));
        }else{
            QMessageBox::warning(this,"ERRO","Produto não encontrado!");
        }
        resetCampo();
    }else{
        QMessageBox::warning(this,"ERRO","Erro ao inserir novo produto!");
    }

}

void window_novaVenda::resetCampo()
{
    ui->txt_veCodigo->clear();
    ui->txt_veQuantidade->setText("1");
    ui->txt_veCodigo->setFocus();
}

void window_novaVenda::removerLinhas(QTableWidget *tw)
{
    while(tw->rowCount()>0){
        tw->removeRow(0);
    }
}

double window_novaVenda::calcularTotal(QTableWidget *tw, int coluna){
    int totalLinhas;
    double total = 0;

    totalLinhas=tw->rowCount();
    for(int i=0;i<totalLinhas;i++){
        total+=tw->item(i,coluna)->text().toDouble();
    }
    return total;
}


void window_novaVenda::on_btn_veExcluirProduto_clicked()
{
   if(ui->tw_veProdutos->currentColumn()!=-1){
       QMessageBox::StandardButton opt=QMessageBox::question(this,"Excluir","Deseja excluir o produto selecionado?",QMessageBox::Yes|QMessageBox::No);
       if(opt==QMessageBox::Yes){
           ui->tw_veProdutos->removeRow(ui->tw_veProdutos->currentRow());
           ui->lb_veTotalVenda->setText("R$ "+QString::number(calcularTotal(ui->tw_veProdutos,4)));
           linhas--;
       }
   }else{
       QMessageBox::warning(this,"ERROR","Selecione um produto primeiro");
   }
}

void window_novaVenda::on_btn_veEditarProduto_clicked()
{
    if(ui->tw_veProdutos->currentColumn()!=-1){
        int linha=ui->tw_veProdutos->currentRow();

        global_idProduto=ui->tw_veProdutos->item(linha,0)->text();
        global_descricaoProduto=ui->tw_veProdutos->item(linha,1)->text();
        global_valorUnitario=ui->tw_veProdutos->item(linha,2)->text();
        global_quantidade=ui->tw_veProdutos->item(linha,3)->text();


        window_editar_produto_venda weditarProdutoVenda;
        weditarProdutoVenda.exec();

        if(editar){
            ui->tw_veProdutos->item(linha,2)->setText(global_valorUnitario);
            ui->tw_veProdutos->item(linha,3)->setText(global_quantidade);
            ui->tw_veProdutos->item(linha,4)->setText(global_valorTotal);
            ui->lb_veTotalVenda->setText("R$ "+QString::number(calcularTotal(ui->tw_veProdutos,4)));
        }

    }
}

void window_novaVenda::on_btn_veFinalizarVenda_clicked()
{
    if(ui->tw_veProdutos->rowCount()>0){
       int idVenda;
       QString mensagemVenda;
       double total=calcularTotal(ui->tw_veProdutos,4);
       QString data=QDate::currentDate().toString("yyyy-MM-dd");
       QString hora=QTime::currentTime().toString("hh:mm:ss");
       QSqlQuery query;
       query.prepare("insert into tb_vendas (data_venda,hora_venda,id_usuario,valor_total,id_tipoPagamento) values('"+data+"','"+hora+"'"
                     ","+QString::number(variaveis_globais::userId)+","+QString::number(total)+",1)");
       if(!query.exec()){
          QMessageBox::warning(this,"ERRO","Erro ao registrar venda!");
       }else{
          query.prepare("select id_venda from tb_vendas order by id_venda desc limit 1 ");
          query.exec();
          query.first();
          idVenda=query.value(0).toInt();
          mensagemVenda="ID venda: "+QString::number(idVenda)+"\nValor total: R$"+QString::number(total);
          int totalLinhas=ui->tw_veProdutos->rowCount();
          int linha=0;
          while(linha<totalLinhas){
               QString produto=ui->tw_veProdutos->item(linha,1)->text();
               QString quantidade=ui->tw_veProdutos->item(linha,3)->text();
               QString valorUnitario=ui->tw_veProdutos->item(linha,2)->text();
               QString valorTotal=ui->tw_veProdutos->item(linha,4)->text();
               query.prepare("insert into tb_produtosVendidos (id_venda,produto,quantidade,valor_unitario,valor_total) values("+QString::number(idVenda)+""
                             ",'"+produto+"',"+quantidade+","+valorUnitario+","+valorTotal+")");
               query.exec();
               linha++;
               }
               QMessageBox::information(this,"Venda Concluída",mensagemVenda);
               resetCampo();
               removerLinhas(ui->tw_veProdutos);
               ui->lb_veTotalVenda->setText("R$ 0.00");
               close();
               window_novaVenda wnovaVenda;
               wnovaVenda.exec();
       }
      }else{
             QMessageBox::warning(this,"Atenção","É necessário adicionar algum produto!");
      }
}
void window_novaVenda::on_btn_vePesquisar_clicked()
{
    window_pesquisaVenda wpesquisaVenda;
    wpesquisaVenda.exec();
    QSqlQuery query;
    QString id=window_pesquisaVenda::retIdVenda;
    double valorTotal;
    query.prepare("select id_produto,produto,valor_venda from tb_produtos where id_produto="+id);
    if(query.exec()){
        query.first();
        if(query.value(0).toString()!=""){
            ui->tw_veProdutos->insertRow(linhas);
            ui->tw_veProdutos->setItem(linhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_veProdutos->setItem(linhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_veProdutos->setItem(linhas,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tw_veProdutos->setItem(linhas,3,new QTableWidgetItem(ui->txt_veQuantidade->text()));
            valorTotal = ui->txt_veQuantidade->text().toDouble()*query.value(2).toDouble();
            ui->tw_veProdutos->setItem(linhas,4,new QTableWidgetItem(QString::number(valorTotal)));
            ui->tw_veProdutos->setRowHeight(linhas,20);
            linhas++;
            ui->lb_veTotalVenda->setText("R$ "+QString::number(calcularTotal(ui->tw_veProdutos,4)));
        }else{
            QMessageBox::warning(this,"ERRO","Produto não encontrado!");
        }
        resetCampo();
    }else{
        QMessageBox::warning(this,"ERRO","Erro ao inserir novo produto!");
    }
}
