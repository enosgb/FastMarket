#include "window_editar_produto_venda.h"
#include "ui_window_editar_produto_venda.h"
#include "window_novavenda.h"

window_editar_produto_venda::window_editar_produto_venda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window_editar_produto_venda)
{
    ui->setupUi(this);

    ui->txt_veEditarProduto->setText(window_novaVenda::global_descricaoProduto);
    ui->txt_veEditarQuantidade->setText(window_novaVenda::global_quantidade);
    ui->txt_veEditarPrecoUnitario->setText(window_novaVenda::global_valorUnitario);

}

window_editar_produto_venda::~window_editar_produto_venda()
{
    delete ui;
}

void window_editar_produto_venda::on_btn_veEditarOk_clicked()
{
    QString aux;

    window_novaVenda::editar=true;
    window_novaVenda::global_quantidade=ui->txt_veEditarQuantidade->text();

    aux=ui->txt_veEditarPrecoUnitario->text();
    std::replace(aux.begin(),aux.end(),',','.');
    window_novaVenda::global_valorUnitario=aux;

    window_novaVenda::global_valorTotal=QString::number(ui->txt_veEditarQuantidade->text().toDouble()*aux.toDouble());
    close();
}

void window_editar_produto_venda::on_btn_veEditarCancelar_clicked()
{
    window_novaVenda::editar=false;
    close();
}
