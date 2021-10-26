#ifndef WINDOW_NOVAVENDA_H
#define WINDOW_NOVAVENDA_H

#include <QDialog>
#include<connect.h>
#include <QTableWidget>
#include "window_pesquisavenda.h"
#include "window_pagamento.h"


namespace Ui {
class window_novaVenda;
}

class window_novaVenda : public QDialog
{
    Q_OBJECT

public:
    explicit window_novaVenda(QWidget *parent = nullptr);
    ~window_novaVenda();

    Conexao con;
    int linhas;
    void resetCampo();
    double calcularTotal(QTableWidget *tw, int coluna);
    static QString global_idProduto,global_descricaoProduto,global_quantidade,global_valorUnitario,global_valorTotal;
    static bool editar;
    void removerLinhas(QTableWidget *tw);




private slots:
    void on_txt_veCodigo_returnPressed();


    void on_btn_veExcluirProduto_clicked();

    void on_btn_veEditarProduto_clicked();

    void on_btn_veFinalizarVenda_clicked();

    void on_btn_vePesquisar_clicked();

    void on_txt_veQuantidade_returnPressed();

private:
    Ui::window_novaVenda *ui;
};

#endif // WINDOW_NOVAVENDA_H
